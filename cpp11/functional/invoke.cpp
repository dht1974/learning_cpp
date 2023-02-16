#include <iostream>
#include <functional>

struct f1
{
    template<typename T, typename U = decltype (T ()), typename P = decltype (T ())>
    decltype (auto) operator ()(T&& a, U&& b, P&& c) const noexcept
    {
        auto ret = std::forward<T>(a) + std::forward<U>(b) * std::forward<P>(c);
        std::cout << "call f1 () = " << ret << std::endl;
        return ret;
    }
};

#if 0
/// TODO
template<typename T, typename U = decltype (T ()), typename P = decltype (T ())>
decltype (auto) f2 (T&& a, U&& b, P&& c) noexcept
{
    auto ret = std::forward<T>(a) + std::forward<U>(b) * std::forward<P>(c);
    std::cout << "call f2 () = " << ret << std::endl;
    return ret;
}
#endif

int
main ()
{
    f1 () (1, 2, 3);
    /// return std::invoke_result_t <decltype (f1 ()), 1, 2, 3);
    auto ret = std::invoke (f1 (), 1, 2, 3.3);
    std::cout << ret << std::endl;

    /// auto ret2 = std::invoke ((f2), 2, 3, 5.5);
    /// std::cout << ret2 << std::endl;
}
