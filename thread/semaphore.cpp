#include <semaphore>
#include <thread>
#include <iostream>

std::binary_semaphore bsema (0);

/// 还有问题，10是最大
std::counting_semaphore<10> sema (3);

void thread_test1_1_fun ()
{
    std::this_thread::sleep_for (std::chrono::seconds (3));
    bsema.release ();
    std::cout << "t1 exit" << std::endl;
}

void thread_test1_2_fun ()
{
    std::this_thread::sleep_for (std::chrono::seconds (1));
    bsema.acquire ();
    std::cout << "t2 exit" << std::endl;
}

void test1 ()
{
    std::thread t1 {thread_test1_1_fun};
    std::thread t2 {thread_test1_2_fun};

    if (t1.joinable () == true) {
        t1.join ();
    }

    if (t2.joinable () == true) {
        t2.join ();
    }
}

void thread_test2_1_fun ()
{
    std::this_thread::sleep_for (std::chrono::seconds (3));
    for (int i = 0; i < 11; ++i) {
        sema.release ();
        std::this_thread::sleep_for (std::chrono::seconds (1));
    }
    std::cout << "t1 exit" << std::endl;
}

void thread_test2_2_fun ()
{
    std::this_thread::sleep_for (std::chrono::seconds (1));
    for (int i = 0; i < 11; ++i) {
        std::cout << "acquire " << std::endl;
        sema.acquire ();
        std::cout << "acquire ok" << std::endl;
    }
    std::cout << "t2 exit" << std::endl;
}

void test2 ()
{
    std::thread t1 {thread_test2_1_fun};
    std::thread t2 {thread_test2_2_fun};

    if (t1.joinable () == true) {
        t1.join ();
    }

    if (t2.joinable () == true) {
        t2.join ();
    }
}

int
main ()
{
 ///   test1 ();
    test2 ();
}
