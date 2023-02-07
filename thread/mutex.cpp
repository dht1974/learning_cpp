#include <mutex>
#include <thread>

/// 简单的测试程序，单步跟踪到glibc nptl线程库

int
main ()
{
    std::mutex mux;

    mux.lock ();
    mux.unlock ();
}
