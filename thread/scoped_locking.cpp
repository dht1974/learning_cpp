#include <iostream>
#include <thread>
#include <chrono>
#include <mutex>

/// std::scoped_lock可以对多个不同类型的mutex进行Scoped Locking (c++17)
/*
<mutex>
 739   template<typename... _MutexTypes>
 740     class scoped_lock
 741     {
 742     public:
 743       explicit scoped_lock(_MutexTypes&... __m) : _M_devices(std::tie(__m...))
 744       { std::lock(__m...); }
 745
 746       explicit scoped_lock(adopt_lock_t, _MutexTypes&... __m) noexcept
 747       : _M_devices(std::tie(__m...))
 748       { } // calling thread owns mutex
 749       /// 析构中，会将参数传入的每一个锁按照参数顺序释放掉
 750       ~scoped_lock()
 751       { std::apply([](auto&... __m) { (__m.unlock(), ...); }, _M_devices); }
 752
 753       scoped_lock(const scoped_lock&) = delete;
 754       scoped_lock& operator=(const scoped_lock&) = delete;
 755
 756     private:
 757       tuple<_MutexTypes&...> _M_devices;
 758     };
*/


/// 演示ABBA问题

std::mutex mux_a;
std::mutex mux_b;
uint64_t i {0};

void t1_deadlock_100_run ()
{
    /// 按照A、B这个顺序持锁
    mux_a.lock ();
    std::cout << "t1 acquire A" << std::endl;
    /// sleep 增加死锁概率
    std::this_thread::sleep_for (std::chrono::seconds (3));
    std::cout << "t1 before acquire B" << std::endl;
    mux_b.lock ();
    std::cout << "t1_deadlock_run hold A/B lock ok" << std::endl;
    mux_b.unlock ();
    mux_a.unlock ();
}

void t2_deadlock_100_run ()
{
    /// 按照B、A这个顺序持锁
    mux_b.lock ();
    std::cout << "t2 acquire B" << std::endl;
    /// sleep 增加死锁概率
    std::this_thread::sleep_for (std::chrono::seconds (3));
    std::cout << "t2 before acquire A" << std::endl;
    mux_a.lock ();
    std::cout << "t2_deadlock_run hold B/A lock ok" << std::endl;
    mux_a.unlock ();
    mux_b.unlock ();
}

/// 100% 死锁
void dead_lock_100_test ()
{
    std::thread t1 (t1_deadlock_100_run);
    std::thread t2 (t2_deadlock_100_run);

    t1.join ();
    t2.join ();
}

void t1_deadlock_rand_run ()
{
    for (;;) {
        /// 按照A、B这个顺序持锁
        mux_a.lock ();
        mux_b.lock ();
        ++i;
        /// std::cout << "t1_deadlock_run hold A/B lock ok" << std::endl;
        mux_b.unlock ();
        mux_a.unlock ();
    }
}

void t2_deadlock_rand_run ()
{
    for (;;) {
        /// 按照B、A这个顺序持锁
        mux_b.lock ();
        mux_a.lock ();
        --i;
        mux_a.unlock ();
        mux_b.unlock ();
    }
}

/// 随机死锁
void dead_lock_rand_test ()
{
    std::thread t1 (t1_deadlock_rand_run);
    std::thread t2 (t2_deadlock_rand_run);

    t1.join ();
    t2.join ();
}

void t1_livelock_run ()
{
    for (;;) {
        /// 按照A、B这个顺序持锁
        std::scoped_lock (mux_a, mux_b);
        ++i;
    }
}

void t2_livelock_run ()
{
    for (;;) {
        std::scoped_lock (mux_b, mux_a);
        --i;
    }
}

/// 死锁避免
void live_lock_test ()
{
    std::thread t1 (t1_livelock_run);
    std::thread t2 (t2_livelock_run);

    t1.join ();
    t2.join ();
}

void t1_livelock_seq_run ()
{
    for (;;) {
        /// 按照A、B这个顺序持锁
        mux_a.lock ();
        mux_b.lock ();
        ++i;
        /// std::cout << "t1_deadlock_run hold A/B lock ok" << std::endl;
        mux_b.unlock ();
        mux_a.unlock ();
    }
}

void t2_livelock_seq_run ()
{
    for (;;) {
        /// 按照B,A这个顺序持锁
        mux_a.lock ();
        mux_b.lock ();
        --i;
        mux_b.unlock ();
        mux_a.unlock ();
    }
}

/// 随机死锁
void live_lock_seq_test ()
{
    std::thread t1 (t1_livelock_seq_run);
    std::thread t2 (t2_livelock_seq_run);

    t1.join ();
    t2.join ();
}

int
main ()
{
    /// 测试通过，不会死锁
    /// 注意：这个测试cpu可以达到170%，线程被调度出去的机率较大，即不能立即获得锁，
    ///       线程被挂起
    /// live_lock_test ();

    /// 测试通过，启动立即会死锁
    /// dead_lock_rand_test ();

    /// 测试通过，100%死锁，这个测试没必要，上面已经证明了
    /// dead_lock_test_100 ();

    /// 顺序加锁也可以死锁避免，但不是ABBA问题了
    /// 注意：这个测试cpu可以达到200%，线程被调度出去的机率较少
    live_lock_seq_test ();
}
