#include <concepts>
#include <cmath>
#include <iostream>

struct AAA 
{
    int a;
/// 下面的模板函数，需要typename T要满足 std::movable<T> 这个concept
/// 打开这个注释，将把AAA的移动构造函数禁止，不满足concept，会编译错误
    /// AAA (AAA&&) = delete;
    
    AAA () {}
    /// AAA (AAA&) = delete;
};

template<typename T>
requires std::movable<T> /// && (! std::copyable<T>)
void foo ()
{}

int
main ()
{
    /// foo<double> ();
    foo<AAA> ();
}
