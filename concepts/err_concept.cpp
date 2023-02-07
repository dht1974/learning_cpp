#include <iostream>
#include <concepts>
#include <type_traits>

template<typename T> 
requires std::integral<T> && std::is_signed_v<T>
T inc (T a)
{
    return ++a;
}

template<typename T>
T dec (T a)
{
    return --a;
}

int 
main ()
{
    int a = 0;
    std::cout << inc (a) << std::endl;

    /// 编译期无法检查出错误
    std::cout << "错误没有在编译期检查出来: " << dec (&a) << std::endl;
    /// 采用concepts后编译期可以检查出错误
    /// std::cout << inc(&a) << std::endl;
    return 0;
}
