#include <set>
#include <iostream>
#include <ranges>

int
main ()
{
    /// 下面两种写法等效
    /// std::set<int, decltype([](int i, int j) {return i > j;})> s;
    std::set<int, std::ranges::greater> s;
    
    for (int i = 0; i < 32; ++i) {
        s.insert (std::rand () % 100);    
    }

    for (auto d : s) {
        std::cout << d << ' ';
    }
    std::cout << std::endl;
}
