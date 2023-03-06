#include <iostream>
#include <string>
#include <thread>
#include <mutex>
 
/// https://en.cppreference.com/w/cpp/language/storage_duration

/// thread_local 就是把 gcc __thread 进行了标准化，thread_local的变量只在本线程中
/// 可见，正常情况下，线程是共享内存空间的

/// 下面两句效果相同
/// __thread unsigned int rage = 1; 
thread_local unsigned int rage = 1; 
std::mutex cout_mutex;
 
struct AAA 
{
    char buf[4096];
};

thread_local AAA aaa;

void increase_rage(const std::string& thread_name)
{
    for (int i = 0; i < 100000000; ++i) {
        ++rage; // modifying outside a lock is okay; this is a thread-local variable
        aaa.buf[1] = 'c';
    }
    std::lock_guard<std::mutex> lock(cout_mutex);
    std::cout << "Rage counter for " << thread_name << ": " << rage << '\n';
}
 
int main()
{
    std::thread a(increase_rage, "a"), b(increase_rage, "b");
 
    {
        std::lock_guard<std::mutex> lock(cout_mutex);
        std::cout << "Rage counter for main: " << rage << '\n';
    }
 
    a.join();
    b.join();
}
