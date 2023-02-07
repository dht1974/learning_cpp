#include <latch>
#include <iostream>
#include <thread>
#include <chrono>

/// latch 也是依靠futex来实现，linux提供futex

/*

#ifdef _GLIBCXX_HAVE_LINUX_FUTEX
#define _GLIBCXX_HAVE_PLATFORM_WAIT 1
    using __platform_wait_t = int;
    static constexpr size_t __platform_wait_alignment = 4;
#else
// define _GLIBCX_HAVE_PLATFORM_WAIT and implement __platform_wait()
// and __platform_notify() if there is a more efficient primitive supported
// by the platform (e.g. __ulock_wait()/__ulock_wake()) which is better than
// a mutex/condvar based wait.
    using __platform_wait_t = uint64_t;
    static constexpr size_t __platform_wait_alignment
      = __alignof__(__platform_wait_t);
#endif

*/

std::chrono::steady_clock sclock;
std::chrono::steady_clock::time_point notify_time;
std::latch l {5};

void thread_test1_1_fun ()
{
    /// std::cout << "t1 " << a << std::endl;
    std::this_thread::sleep_for (std::chrono::seconds (5));
    l.count_down ();
    std::cout << "t1 exit" << std::endl;
}

void thread_test1_2_fun ()
{
    /// std::cout << "origin t2 b: " << b << std::endl;
    std::this_thread::sleep_for (std::chrono::seconds (2));
    l.count_down ();
    std::cout << "t2 exit" << std::endl;
}

void thread_test1_3_fun ()
{
    std::this_thread::sleep_for (std::chrono::seconds (3));
    l.count_down ();
    std::cout << "t3 exit" << std::endl;
}

void test1 ()
{
    std::thread t1 {thread_test1_1_fun};
    std::thread t2 {thread_test1_2_fun};
    std::thread t3 {thread_test1_3_fun};

    auto now = std::chrono::steady_clock::now ();
    /// count_down 默认减1,可以多减
    l.count_down (2);
    l.wait ();
    std::cout << std::chrono::duration_cast <std::chrono::nanoseconds> (
        std::chrono::steady_clock::now () - now).count () << " ns" << std::endl;

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
    std::cout << l.max () << std::endl;
    
    test1 ();
}
