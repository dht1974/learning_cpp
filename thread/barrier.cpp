#include <barrier>
#include <iostream>
#include <thread>
#include <chrono>

/// 代码还未完成，请忽略

/// barrier 也是依靠futex来实现，linux提供futex

std::chrono::steady_clock sclock;
std::chrono::steady_clock::time_point notify_time;

void thread_test1_1_fun ()
{
    /// std::cout << "t1 " << a << std::endl;
    std::this_thread::sleep_for (std::chrono::seconds (5));
    std::cout << "t1 exit" << std::endl;
}

void thread_test1_2_fun ()
{
    /// std::cout << "origin t2 b: " << b << std::endl;
    std::this_thread::sleep_for (std::chrono::seconds (2));
    std::cout << "t2 exit" << std::endl;
}

void thread_test1_3_fun ()
{
    std::this_thread::sleep_for (std::chrono::seconds (3));
    std::cout << "t3 exit" << std::endl;
}

void test1 ()
{
    std::thread t1 {thread_test1_1_fun};
    std::thread t2 {thread_test1_2_fun};
    std::thread t3 {thread_test1_3_fun};

    auto now = std::chrono::steady_clock::now ();

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
    test1 ();
}
