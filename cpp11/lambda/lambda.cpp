#include <iostream>
#include <algorithm>
#include <ranges>
#include <vector>
#include <functional>

void foo ()
{
    return;
}

/// 在lambda表达式用*this捕获对象副本
struct AAA
{
    int a {5};
        
    AAA () = default;

    AAA (const AAA& aaa)
    {
        std::cout << "const AAA& aaa" << std::endl;
        a = aaa.a;
    }

    int foo ()
    {
        /// 注意这两种形式的输出结果是不一样的，[*this]会调用拷贝构造函数
        auto f = [*this] () {
        /// auto f = [this] () {
            return a * a;
        };
    
        return f ();    
    }
};

int
main ()
{
    std::vector v {1, 2, 3, 4, 5, 6};

    /// 不用再采用remove_erase idiom了，直接用erase就可以了
    /// c++17 lamba可以支持auto，参数和返回值都可以用auto
    std::erase_if (v, [] (auto i) -> auto {
        return i % 2 == 0;
    });

    std::cout << "v.size: " << v.size () << std::endl;
    std::copy (v.begin (), v.end (), std::ostream_iterator<int> (std::cout, "\n"));

    /// lambda + constexpr
    /// auto f = [] (auto i) constexpr -> auto { return i % 2 == 0; };
    static_assert (std::is_function_v<decltype(foo)> == true, "is not function");

    /// TODO lambda 为什么通过不了下面的static_assert
    auto f = [] (int i) -> bool { return i % 2 == 0; };
    static_assert (std::is_function_v<decltype(f)> == false, "is not function");

    std::function<bool (int i)> fun {
        [] (int i) -> bool { return i % 2 == 0; }
        };
    static_assert (std::is_function_v<decltype(fun)> == false, "is not function");

    /// constexpr lambda表达式
    constexpr auto lamb = [] (int n) { return n * n; };
    static_assert (lamb (3) == 9);

    auto lamb2 = [] (int n) constexpr { return n * n; };
    static_assert (lamb2 (3) == 9);

    // 在lambda表达式用*this捕获对象副本
    AAA *ptr = new AAA;
    std::cout << ptr->foo () << std::endl;
    ptr->a = 3;
    std::cout << ptr->foo () << std::endl;
}
