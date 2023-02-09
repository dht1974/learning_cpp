#include <type_traits>
#include <iostream>

/*
Converts any type T to a reference type, making it possible to use member functions in the operand of the decltype specifier without the need to go through constructors.
std::declval is commonly used in templates where acceptable template parameters may have no constructor in common, but have the same member function whose return type is needed.

将任意类型 T 转换成引用类型，令在 decltype 表达式中不必经过构造函数就能使用成员函数。
通常在模板中使用 declval ，模板接受的模板实参通常可能无构造函数，但有同一成员函数，均返回所需类型。
*/

struct AAA
{
    AAA () = delete;
    int foo (int a, int b)
    {
        return a + b;
    }

    double bar ();
};

int
main ()
{
    decltype(std::declval<AAA> ().foo (1, 1)) a = 10;
    std::cout << a << std::endl;

    /// 注意 bar () 并没有函数体，也不影响
    decltype(std::declval<AAA> ().bar ()) b = 100;
    static_assert (std::is_floating_point_v<decltype(std::declval<AAA> ().bar ())>);
    std::cout << b << std::endl;
}
