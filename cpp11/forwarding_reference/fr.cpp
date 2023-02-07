#include <iostream>
#include <string>

/// 展示 auto&& -- forwarding reference的使用(也叫 universal reference)
///      auto& -- mutable reference 可修改引用
///      const auto& -- const reference 不可修改引用
int
main ()
{
    int a = 3;
    auto& ra = a;

    std::cout << "reference of a: " << ra << std::endl;
    ra = 5;
    std::cout << "reference of a: " << ra << std::endl;

    const auto cra = a;
    std::cout << "const reference of a: " << cra << std::endl;
    /// cra = 6; /// build err:  错误：向只读变量‘cra’赋值

    auto&& fra = a;
    std::cout << "forwarding reference of a: " << fra << std::endl;
    /// forwarding reference 可以被修改
    fra = 8;
    std::cout << "forwarding reference of a: " << fra << std::endl;

    
    /// auto& 不能引用一个临时对象
    /// auto& rs = std::string ("abc") + std::string ("def");

    /// const auto& 能引用一个临时对象
    const auto& crs = std::string ("abc") + std::string ("def");
    std::cout << "const auto reference string: " << crs << std::endl;
    /// const 引用不能被修改，编译出错
    /// crs = std::string ("ABC");

    auto&& frs = std::string ("abc") + std::string ("def");
    std::cout << "forwarding reference string: " << frs << std::endl;
    frs = std::string ("ABC");
    std::cout << "forwarding reference string: " << frs << std::endl;
}
