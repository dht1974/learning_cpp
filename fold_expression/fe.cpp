#include <iostream>

template<typename... Args>
auto foo (Args&&... args)
{
    /// 注意，要加括号

    /// 下面几种方式都可以
    return (args + ... );   
    /// return (... + args);
    /// return (0 + ... + args);
    /// return (args + ... + 0);
}

template<typename... Args>
auto bar (Args&&... args)
{
    /// 注意，要加括号

    /// 下面几种方式都可以
    /// return (args + ... );   
    /// return (... + args);
    return ("" + ... + args);
    /// return (args + ... + "");
}

/// 支持T的类型即可以是int也可以是std::string
/// 从这个例子可以看出 if constexpr 功能强大，本来需要像上面一样写两个函数
/// 但采用constexpr后，一个函数就可以了
template<typename ... Args>
auto foobar (Args&& ... args)
{
    /// 注意：这里的&&不是右值引用，而是逻辑&&
    if constexpr ((std::is_integral_v<Args>&&...) == true) {
        return (args + ...);
    } else {
        return (args + ... + "");
    }
}

template<typename T>
void helper (T&& a)
{
    (void) a;
    static_assert (std::is_integral_v<T>, "not a integral");
}

template<typename... Args>
void helper2 (Args&&... args)
{
    /// TODO 这个变参void如何写？
    /// (((void)args)...);
    static_assert ((std::is_integral_v<Args>&&...), "not a integral");
}

template<typename... Args>
void show_args (Args&& ... args)
{
    (std::cout << ... << args) << std::endl;
}

int
main ()
{
    int a = foo (1, 2, 3);
    int b = foo (1, 2, 3, 4, 5);
    std::cout << a << " : " << b << std::endl;

    std::cout << bar (std::string ("abc"), std::string ("def"), std::string ("ghi")) << std::endl;

    std::cout << foobar (1, 2, 3, 4, 5, 6, 7) << std::endl;
    std::cout << foobar (std::string ("abc"), std::string ("def"), std::string ("ghi")) << std::endl;

    helper (1);
    helper2 (1, 2, 3, 4, 5);
    /// helper2 ("1"); /// 编译错误，不是整形

    show_args (1, 2.0, "hello", std::string ("world"), 'c');
}
