#include <mutex>
#include <iostream>
#include <thread>
#include <atomic>
#include <chrono>

std::atomic_int a {0};
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

void thread_test1_1_fun ()
{
    /// std::cout << "t1 " << a << std::endl;
    std::this_thread::sleep_for (std::chrono::seconds (1));
    b = 1;
    a.store (1, MEMORY_ORDER_STORE);
}

void thread_test1_2_fun ()
{
    std::cout << "t2 b: " << b << std::endl;
    /// 忙等共享变量数值改变
    for (;;) {
        if (a.load (MEMORY_ORDER_LOAD) == 1) {
            /// std::cout << "t2 while break " << std::endl;
            break;
        }
    }
    std::cout << b << std::endl;
}

void test1 ()
{
    thread_test1_1_fun ();
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
    /// std::cout << "t1 " << a << std::endl;
    std::this_thread::sleep_for (std::chrono::seconds (1));
    b = 1;
    a.store (1, MEMORY_ORDER_STORE);
}

void thread_test2_2_fun ()
{
    std::cout << "t2 b: " << b << std::endl;
    /// 忙等共享变量数值改变
    for (;;) {
        if (a.load (MEMORY_ORDER_LOAD) == 1) {
            /// std::cout << "t2 while break " << std::endl;
            break;
        }
    }
    std::cout << b << std::endl;
}

void thread_test2_3_fun ()
{

}

void test2 ()
{
    std::thread t1 {thread_test2_1_fun};
    std::thread t2 {thread_test2_2_fun};
    std::thread t3 {thread_test2_3_fun};

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
    /// 双线程，一个线程更新一个变量，另一个线程等待更新
    /// 验证 memory_order_seq_cst 和 memory_order_release/acquire
    test1 ();

    /// 三线程
    /// test2 ();
}
