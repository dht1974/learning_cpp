#include <thread>
#include <memory>
#include <iostream>
#include <chrono>
#include <shared_mutex>

/// C++17引入了shared_mutex，可以实现读写锁
/// 本质上就是对pthread_rwlock_xxx系列函数进行了一次包装

/*  注意: lock_shared ()，即获取读锁，有可能会busy-waiting
220     void
221     lock_shared()
222     {
223       int __ret;
224       // We retry if we exceeded the maximum number of read locks supported by
225       // the POSIX implementation; this can result in busy-waiting, but this
226       // is okay based on the current specification of forward progress
227       // guarantees by the standard.
228       do
229     __ret = __glibcxx_rwlock_rdlock(&_M_rwlock);
230       while (__ret == EAGAIN);
231       if (__ret == EDEADLK)
232     __throw_system_error(int(errc::resource_deadlock_would_occur));
233       // Errors not handled: EINVAL
234       __glibcxx_assert(__ret == 0);
235     }
*/


std::shared_mutex sl;
int val {0};
bool fin {false};

/// 防止输出混乱
std::mutex cout_mux;

void thread_test1_1_fun ()
{
    /// std::cout << "t1 " << a << std::endl;
    std::this_thread::sleep_for (std::chrono::seconds (5));
    for (int i = 0; i < 1000000; ++i) {
#if 0
        sl.lock ();
        ++val;
        sl.unlock ();
#else
        std::shared_lock<std::shared_mutex> l (sl);
        ++val;
#endif
    }
    sl.lock ();
    fin = true;
    sl.unlock ();

    std::lock_guard<std::mutex> lk (cout_mux);
    std::cout << "t1 exit" << std::endl;
}

void thread_test1_2_fun ()
{
    /// std::cout << "origin t2 b: " << b << std::endl;
    std::this_thread::sleep_for (std::chrono::seconds (2));
    for (;;) {
#if 0
        sl.lock_shared ();
        if (fin == true) {
            sl.unlock_shared ();
            break;
        }
        sl.unlock_shared ();
#else
        std::shared_lock<std::shared_mutex> l (sl);
        if (fin == true) {
            break;
        }
#endif
    }

    int myval {};
    sl.lock_shared ();
    myval = val;
    sl.unlock_shared ();
    std::lock_guard<std::mutex> lk (cout_mux);
    std::cout << "t2 exit: " << myval << std::endl;
}

void thread_test1_3_fun ()
{
    std::this_thread::sleep_for (std::chrono::seconds (2));
    for (;;) {
#if 0
        sl.lock_shared ();
        if (fin == true) {
            sl.unlock_shared ();
            break;
        }
        sl.unlock_shared ();
#else
        std::shared_lock<std::shared_mutex> l (sl);
        if (fin == true) {
            break;
        }
#endif
    }

    int myval {};
    sl.lock_shared ();
    myval = val;
    sl.unlock_shared ();
    std::lock_guard<std::mutex> lk (cout_mux);
    std::cout << "t3 exit: " << myval << std::endl;
}

void test1 ()
{
    /// thread1 负责写，thread2、3负责读
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
    test1 ();
}

