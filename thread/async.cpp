#include <future>
#include <chrono>
#include <iostream>

void f ()
{
    std::this_thread::sleep_for (std::chrono::seconds (3));
    std::cout << "finish f ()" << std::endl;
}

void g ()
{
    std::this_thread::sleep_for (std::chrono::seconds (3));
    std::cout << "finish g ()" << std::endl;
}

int
main ()
{
    /// 下面两个async并不会并行执行，原因是 std::async([]{ f(); }); 返回的是一个 
    /// std::future<void>类型的临时变量，在执行第2个async前要析构这个临时变量，而
    /// 析构会等待async完成。

    /*a temp std::future<void> is constructed*/
    std::async([]{ f(); }); 

    /* blocked by the destructor of std::future<void> */
    std::async([]{ g(); });
}
