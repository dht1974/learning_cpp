#include <type_traits>
#include <iostream>

/// 从type_traits摘取出的例子，典型的变参模板例子
/// std::__or_  -->  OR

/// 变参模板类OR声明
template<typename...>
struct OR;

/// 特化
template<>
struct OR<> : public std::false_type
{};

/// 偏特化
template<typename _B1>
struct OR<_B1> : public _B1
{};

/// 偏特化
template<typename _B1, typename _B2>
struct OR<_B1, _B2> : 
    public std::conditional_t<_B1::value, _B1, _B2>
{};

/// 编译期递归调用，前面特化和偏特化是递归结束的终点
template<typename _B1, typename _B2, typename _B3, typename... _Bn>
struct OR<_B1, _B2, _B3, _Bn...> : 
    public std::conditional_t<_B1::value, _B1, OR<_B2, _B3, _Bn...>>
{};

int
main ()
{
    int a = 1;
    float b = 2.0f;

    if (OR<>::value == true) {
        std::cout << "null typename: true" << std::endl;
    } else {
        std::cout << "null typename: false" << std::endl;
    }

    if (OR<std::is_integral<decltype (a)>>::value == true) {
        std::cout << "one typename: true" << std::endl;
    } else {
        std::cout << "one typename: false" << std::endl;
    }

    if (OR<std::is_integral<decltype (a)>, std::__is_unsigned_integer<decltype (a)>>::value == true) {
        std::cout << "two typename int: true" << std::endl;
    } else {
        std::cout << "two typename int: false" << std::endl;
    }

    if (OR<std::is_integral<decltype (b)>, std::__is_unsigned_integer<decltype (b)>>::value == true) {
        std::cout << "two typename float: true" << std::endl;
    } else {
        std::cout << "two typename float: false" << std::endl;
    }

    /// 编译器递归调用
    using b_type_t = decltype (b);
    if (OR <
            std::is_integral<b_type_t>, 
            std::__is_unsigned_integer<b_type_t>, 
            std::is_void <b_type_t>,
            std::is_pointer <b_type_t>,
            std::is_floating_point<b_type_t>
        >::value == true) {
        std::cout << "five typename float: true" << std::endl;
    } else {
        std::cout << "five typename float: false" << std::endl;
    }
}
