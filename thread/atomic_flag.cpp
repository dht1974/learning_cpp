#include <mutex>
#include <iostream>
#include <thread>
#include <atomic>
#include <chrono>
#include <unistd.h>

/// 注意输出是两个线程同时输出，结果有可能是11，其实是两个1
/// 通过getpid()输出的pid，top观察，wait操作不是忙等
/*
pid: 5680
origin t3 b: 0
origin t2 b: 0
now t3 b: 1 time: 84482
now t2 b: 1 time: 98071

pid: 5864
origin t3 b: 0
origin t2 b: 0
now t3 b: 1 time: 12501
now t2 b: 1 time: 138106

notify到wait线程收到并调度处理，时间长达微秒级，在笔记本上测试，线程由
挂起状态调度为运行状态，时间不可控
*/

std::atomic_flag a {ATOMIC_FLAG_INIT};
int b {0};

/// sequence consistent 
#if 0
/// full barrier
#define MEMORY_ORDER_LOAD std::memory_order_seq_cst
#define MEMORY_ORDER_STORE std::memory_order_seq_cst
#endif 

/// acqure/release
#if 0
/// read barrier
#define MEMORY_ORDER_LOAD std::memory_order_acquire
/// write barrier
#define MEMORY_ORDER_STORE std::memory_order_release
#endif

#if 1
/// no barrier
#define MEMORY_ORDER_LOAD std::memory_order_relaxed
#define MEMORY_ORDER_STORE std::memory_order_relaxed

#endif

std::chrono::steady_clock sclock;
std::chrono::steady_clock::time_point notify_time;

void thread_test1_1_fun ()
{
    /// std::cout << "t1 " << a << std::endl;
    std::this_thread::sleep_for (std::chrono::seconds (15));
    /// a.test_and_set (MEMORY_ORDER_STORE);
    b = 1;
    a.test_and_set ();
    notify_time = sclock.now ();

    /// c++20 提供的新接口
    a.notify_all ();
    /// a.notify_one (); /// one 和 all效果相同，原因待查
    std::cout << "t1 exit" << std::endl;
}

void thread_test1_2_fun ()
{
    std::cout << "origin t2 b: " << b << std::endl;
    std::this_thread::sleep_for (std::chrono::seconds (5));
    bool old {true};
    a.wait (old);
    std::chrono::steady_clock::time_point wait_time = sclock.now ();
    auto time_diff = wait_time - notify_time;
    std::cout << "now t2 b: " << b << " time: " << 
        std::chrono::duration_cast<std::chrono::nanoseconds> (time_diff).count () << 
        " old: " << old << std::endl;
    std::this_thread::sleep_for (std::chrono::seconds (5));
    std::cout << "t2 exit" << std::endl;
}

void thread_test1_3_fun ()
{
    std::cout << "origin t3 b: " << b << std::endl;
    std::this_thread::sleep_for (std::chrono::seconds (5));
    bool old {true};
    a.wait (old);
    std::chrono::steady_clock::time_point wait_time = sclock.now ();
    auto time_diff = wait_time - notify_time;
    std::cout << "now t3 b: " << b << " time: " << 
        std::chrono::duration_cast<std::chrono::nanoseconds> (time_diff).count () << 
        " old: " << old << std::endl;
    std::cout << "t3 exit" << std::endl;
}

void test1 ()
{
    std::atomic_int c;
    std::cout << "atomic_int is lock free: " << c.is_lock_free () << std::endl;

    std::thread t1 {thread_test1_1_fun};
    std::thread t2 {thread_test1_2_fun};
    std::thread t3 {thread_test1_3_fun};

    if (t1.joinable () == true) {
        t1.join ();
    }

    if (t2.joinable () == true) {
        t2.join ();
    }

    if (t3.joinable () == true) {
        t3.join ();
    }
}

int
main ()
{
    std::cout << "pid: " << getpid () << std::endl;
    test1 ();
}


/*  wait 实现原理
 
atomic_base.h:

 245行 是bool类型的
 246行 __GCC_ATOMIC_TEST_AND_SET_TRUEVAL 是1

 241     _GLIBCXX_ALWAYS_INLINE void
 242     wait(bool __old,
 243     memory_order __m = memory_order_seq_cst) const noexcept
 244     {
 245       const __atomic_flag_data_type __v
 246     = __old ? __GCC_ATOMIC_TEST_AND_SET_TRUEVAL : 0;
 247 
 248       std::__atomic_wait_address_v(&_M_i, __v,
 249       [__m, this] { return __atomic_load_n(&_M_i, int(__m)); });
 250     }
 251 
                      
                        |
                        V

415   template<typename _Tp, typename _ValFn>
416     void
417     __atomic_wait_address_v(const _Tp* __addr, _Tp __old,
418                 _ValFn __vfn) noexcept
419     {
420       __detail::__enters_wait __w(__addr);
421       __w._M_do_wait_v(__old, __vfn);
422     }
                      
                        |
                        V

在一个循环里，首先做一个spin操作，这个spin操作是执行16次循环，尝试是否满足条件
然后391行执行真正的wait操作，393行由于wait有可能被sputious notify唤醒，所以需要
进行进一步检查，如果是伪唤醒，重复上面步骤

wait前做spin自旋检查目的是：认为其他线程占用这个原子操作的时间很短，等一下可能其他
线程就释放了，本线程尽量不进入wait状态（线程被操作系统挂起），因为线程一旦被挂起
再次被调度执行就是一个漫长的过程了

atomic_wait.h:

382     template<typename _Tp, typename _ValFn>
383       void
384       _M_do_wait_v(_Tp __old, _ValFn __vfn)
385       {         
386         do
387           {
388         __platform_wait_t __val;
389         if (__base_type::_M_do_spin_v(__old, __vfn, __val))
390           return;
391         __base_type::_M_w._M_do_wait(__base_type::_M_addr, __val);
392           }
393         while (__detail::__atomic_compare(__old, __vfn()));
394       }
                      
                        |
                        V

335     template<typename _Up, typename _ValFn,
336          typename _Spin = __default_spin_policy>
337       bool
338       _M_do_spin_v(const _Up& __old, _ValFn __vfn,
339                __platform_wait_t& __val,
340                _Spin __spin = _Spin{ })
341       { return _S_do_spin_v(_M_addr, __old, __vfn, __val, __spin); }


324行是false， 330行原子读出一个内存地址的值（这个内存地址是存放futex word）放入__val中

313     template<typename _Up, typename _ValFn,
314          typename _Spin = __default_spin_policy>
315       static bool
316       _S_do_spin_v(__platform_wait_t* __addr,
317                const _Up& __old, _ValFn __vfn,
318                __platform_wait_t& __val,
319                _Spin __spin = _Spin{ })
320       {
321         auto const __pred = [=]
322           { return !__detail::__atomic_compare(__old, __vfn()); };
323 
324         if constexpr (__platform_wait_uses_type<_Up>)
325           {
326         __builtin_memcpy(&__val, &__old, sizeof(__val));
327           }
328         else
329           {
330         __atomic_load(__addr, &__val, __ATOMIC_ACQUIRE);
331           }
332         return __atomic_spin(__pred, __spin);
333       }
 
                        |
                        V

155~169行执行16次，前12次执行thread_relax () 既 PAUSE指令，后4次执行sched_yield ()
162行检查一下条件是否满足，如果满足结束spin

171~175 __default_spin_policy () 返回false，实际上不执行，如果不采用__default_spin_policy
而是其他spin策略的话，比如真正的自旋锁那么全部返回true，会一直自旋下去，一直到__pred ()
满足条件才退出

155     template<typename _Pred,
156          typename _Spin = __default_spin_policy>
157       bool
158       __atomic_spin(_Pred& __pred, _Spin __spin = _Spin{ }) noexcept
159       {
160     for (auto __i = 0; __i < __atomic_spin_count; ++__i)
161       {
162         if (__pred())
163           return true;
164 
165         if (__i < __atomic_spin_count_relax)
166           __detail::__thread_relax();
167         else
168           __detail::__thread_yield();
169       }
170 
171     while (__spin())
172       {
173         if (__pred())
174           return true;
175       }
176 
177     return false;
178       }
                      
                        |
                        V

前面分析了spin实现，如果spin阶段不满足条件，就需要将本线程挂起了
linxu平台有相应的futex机制支持wait操作，执行262行

256     struct __waiter_pool : __waiter_pool_base
257     {
258       void
259       _M_do_wait(const __platform_wait_t* __addr, __platform_wait_t __old) noexcept
260       {
261 #ifdef _GLIBCXX_HAVE_PLATFORM_WAIT
262     __platform_wait(__addr, __old);
263 #else
264     __platform_wait_t __val;
265     __atomic_load(__addr, &__val, __ATOMIC_SEQ_CST);
266     if (__val == __old)
267       {
268         lock_guard<mutex> __l(_M_mtx);
269         __atomic_load(__addr, &__val, __ATOMIC_RELAXED);
270         if (__val == __old)
271           _M_cv.wait(_M_mtx);
272       }
273 #endif // __GLIBCXX_HAVE_PLATFORM_WAIT
274       }
275     };
                      
                        |
                        V

108行执行系统调用futex，进行wait，指导有人notify后，此线程才有可能被唤醒
114行在futex出错的时候，系统是要抛出异常的

104     template<typename _Tp>
105       void
106       __platform_wait(const _Tp* __addr, __platform_wait_t __val) noexcept
107       {
108     auto __e = syscall (SYS_futex, static_cast<const void*>(__addr),
109                 static_cast<int>(__futex_wait_flags::__wait_private),
110                 __val, nullptr);
111     if (!__e || errno == EAGAIN)
112       return;
113     if (errno != EINTR)
114       __throw_system_error(errno);
115       }

futex 不再分析，参考man futex

*/
