#include <atomic>
#include <chrono>
#include <cstddef>
#include <iomanip>
#include <iostream>
#include <mutex>
#include <new>
#include <thread>
 
/// https://en.cppreference.com/w/cpp/thread/hardware_destructive_interference_size
/// 此程序演示了cache thresh，以及如何避免

/*
        thread_1                       thread_2
           |                              |
           V                              V
       +--------+                     +--------+
       | core 1 |                     | core 2 |
       +--------+                     +--------+
           |                              |
      +----------+     硬件同步      +----------+
      | l1 cache |  <------------->  | l1 cache |
      +----------+                   +----------+

    两个原子变量在一个
    l1 cache line, 64Bytes
    +----------------+              +----------------+
    | atom_x, atom_y |              | atom_x, atom_y |
    +----------------+              +----------------+

    thread_1修改atom_x导致整个cacheline变成invalid状态，硬件会把core1的这个cahceline同步
    给core2的对应cacheline，相反当thread_2修改atom_y时，也需要硬件将状态同步到core1

    整个过程造成core1和core2直接存在大量的同步操作，严重影响性能


    第二个例子中，两个原子变量在不同的cacheline中，修改一个不影响另一个，因此两个core之间
    没有同步消息，性能更优
*/

#ifdef __cpp_lib_hardware_interference_size
    using std::hardware_constructive_interference_size;
    using std::hardware_destructive_interference_size;
#else
    // 64 bytes on x86-64 │ L1_CACHE_BYTES │ L1_CACHE_SHIFT │ __cacheline_aligned │ ...
    constexpr std::size_t hardware_constructive_interference_size = 64;
    constexpr std::size_t hardware_destructive_interference_size = 64;
#endif
 
std::mutex cout_mutex;
 
constexpr int max_write_iterations{10'000'000}; // the benchmark time tuning
 
struct alignas(hardware_constructive_interference_size)
OneCacheLiner { // occupies one cache line
    std::atomic_uint64_t x{};
    std::atomic_uint64_t y{};
} oneCacheLiner;
 
struct TwoCacheLiner { // occupies two cache lines
    alignas(hardware_destructive_interference_size) std::atomic_uint64_t x{};
    alignas(hardware_destructive_interference_size) std::atomic_uint64_t y{};
} twoCacheLiner;
 
inline auto now() noexcept { return std::chrono::high_resolution_clock::now(); }
 
template<bool xy>
void oneCacheLinerThread() {
    const auto start { now() };
 
    for (uint64_t count{}; count != max_write_iterations; ++count)
        if constexpr (xy)
             oneCacheLiner.x.fetch_add(1, std::memory_order_relaxed);
        else oneCacheLiner.y.fetch_add(1, std::memory_order_relaxed);
 
    const std::chrono::duration<double, std::milli> elapsed { now() - start };
    std::lock_guard lk{cout_mutex};
    std::cout << "oneCacheLinerThread() spent " << elapsed.count() << " ms\n";
    if constexpr (xy)
         oneCacheLiner.x = elapsed.count();
    else oneCacheLiner.y = elapsed.count();
}
 
template<bool xy>
void twoCacheLinerThread() {
    const auto start { now() };
 
    for (uint64_t count{}; count != max_write_iterations; ++count)
        if constexpr (xy)
             twoCacheLiner.x.fetch_add(1, std::memory_order_relaxed);
        else twoCacheLiner.y.fetch_add(1, std::memory_order_relaxed);
 
    const std::chrono::duration<double, std::milli> elapsed { now() - start };
    std::lock_guard lk{cout_mutex};
    std::cout << "twoCacheLinerThread() spent " << elapsed.count() << " ms\n";
    if constexpr (xy)
         twoCacheLiner.x = elapsed.count();
    else twoCacheLiner.y = elapsed.count();
}
 
int main() {
    std::cout << "__cpp_lib_hardware_interference_size "
#   ifdef __cpp_lib_hardware_interference_size
        " = " << __cpp_lib_hardware_interference_size << '\n';
#   else
        "is not defined, use " << hardware_destructive_interference_size << " as fallback\n";
#   endif
 
    std::cout
        << "hardware_destructive_interference_size == "
        << hardware_destructive_interference_size << '\n'
        << "hardware_constructive_interference_size == "
        << hardware_constructive_interference_size << "\n\n";
 
    std::cout
        << std::fixed << std::setprecision(2)
        << "sizeof( OneCacheLiner ) == " << sizeof( OneCacheLiner ) << '\n'
        << "sizeof( TwoCacheLiner ) == " << sizeof( TwoCacheLiner ) << "\n\n";
 
    constexpr int max_runs{4};
 
    int oneCacheLiner_average{0};
    for (auto i{0}; i != max_runs; ++i) {
        std::thread th1{oneCacheLinerThread<0>};
        std::thread th2{oneCacheLinerThread<1>};
        th1.join(); th2.join();
        oneCacheLiner_average += oneCacheLiner.x + oneCacheLiner.y;
    }
    std::cout << "Average T1 time: " << (oneCacheLiner_average / max_runs / 2) << " ms\n\n";
 
    int twoCacheLiner_average{0};
    for (auto i{0}; i != max_runs; ++i) {
        std::thread th1{twoCacheLinerThread<0>};
        std::thread th2{twoCacheLinerThread<1>};
        th1.join(); th2.join();
        twoCacheLiner_average += twoCacheLiner.x + twoCacheLiner.y;
    }
    std::cout << "Average T2 time: " << (twoCacheLiner_average / max_runs / 2) << " ms\n\n";
 
    std::cout << "Ratio T1/T2:~ " << 1.*oneCacheLiner_average/twoCacheLiner_average << '\n';
}
