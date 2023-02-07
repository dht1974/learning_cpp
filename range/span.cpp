#include <iostream>
#include <span>
#include <vector>
/// #include <format> 目前还不支持

/*
std::span是指向一组连续的对象的对象, 是一个视图view, 不是一个拥有者owner

一组连续的对象可以是 C 数组, 带着大小的指针, std::array, 或者std::string

std::span可以有两种范围:

静态范围static extend: 编译期就可以确定大小
动态范围dynamic extend: 由指向第一个对象的指针和连续对象的大小组成
*/

int
main ()
{
    std::vector v1 {1, 2, 3, 4, 5};
    std::span<int> sv1 (v1);

    std::vector v2 {11, 22, 33, 44, 55};
    std::span<int, 5> sv2 (v2);
    
    /// std::cout << sv1.size () << std::endl;
    /// std::cout << sv2.size () << std::endl;

    std::cout << "------------------" << std::endl;
    for (auto v : sv2) {
        std::cout << v << std::endl;
    }

    /// push_back导致span失效，打印值错误
#if 0 
    v1.push_back (6);
    v2.push_back (6);
    
    std::cout << "------------------" << std::endl;
    for (auto v : sv2) {
        std::cout << v << std::endl;
    }
#endif

    std::vector v3 {111, 222, 333, 444, 555};
    std::span<int> sv3 (v3.begin () + 1, v3.end ());

    std::cout << "------------------" << std::endl;
    for (auto v : sv3) {
        std::cout << v << std::endl;
    }

    int a1[] = {1, 2, 3, 4, 5};
    /// std::span<int> sv4 {a1, a1 + std::size (a1)};
    /// span 不会丢失数值长度信息
    std::span<int> sv4 {a1};
    std::cout << "------------------" << std::endl;
    for (auto v : sv4) {
        std::cout << v << std::endl;
    }
    std::cout << "array size: " << sv4.size () << std::endl;

    /// std::span<int> sv5 (sv4.subspan (2, 3));
    std::span<int> sv5 (sv4.subspan (1, 3));
    std::cout << "sv5 size: " << sv5.size () << std::endl;
    std::cout << "------------------" << std::endl;
    for (auto v : sv5) {
        std::cout << v << std::endl;
    }
}
