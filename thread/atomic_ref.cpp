#include <atomic>
#include <iostream>
#include <thread>

size_t a {0};
std::atomic_ref<size_t> atom_aaa (a);

void thread_test1_1_fun ()
{
    std::cout << "t1: " << std::endl;
    /// std::this_thread::sleep_for (std::chrono::seconds (5));
    for (size_t i = 0; i < 100000000llu; ++i) {
#if 0
        ++a;
#else
        ++atom_aaa;
#endif
    }
    std::cout << "t1 exit" << std::endl;
}

void thread_test1_2_fun ()
{
    std::cout << "t2: " << std::endl;
    /// std::this_thread::sleep_for (std::chrono::seconds (2));
    for (size_t i = 0; i < 100000000llu; ++i) {
#if 0
        ++a;
#else
        ++atom_aaa;
#endif
    }
    std::cout << "t2 exit" << std::endl;
}

void thread_test1_3_fun ()
{
    std::cout << "t3: " << std::endl;
    /// std::this_thread::sleep_for (std::chrono::seconds (3));
    for (size_t i = 0; i < 100000000llu; ++i) {
#if 0
        ++a;
#else
        ++atom_aaa;
#endif
    }
    std::cout << "t3 exit" << std::endl;
}

void test1 ()
{
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

    /// 不使用atom_ref的a，结果是错的，使用了，结果正确
    std::cout << a << std::endl;
}

int
main ()
{
    test1 ();
}
