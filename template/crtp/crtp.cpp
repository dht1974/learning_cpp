#include <iostream>

/// curiously recurring template pattern CRTP 实现静态多态
/*
可以将原来需要依赖虚表来完成的多态特性，转变为纯粹的静态调用，明显性能更高。
另一方面，基类可以无成本的访问子类的功能和实现，这肯定比标准的多态自由多了

应用：
enable_shared_from_this
c++20:ranges::view_interface
*/

template <class T> 
struct Base
{
    void interface ()
    {
        static_cast<T*>(this)->implementation ();
    }

    static void static_func ()
    {
        T::static_sub_func ();
    }
};

struct Derived : Base<Derived>
{
    void implementation ()
    {
        std::cout << "Derived::implementation" << std::endl;
    }

    static void static_sub_func ()
    {
        std::cout << "Derived::static_sub_func" << std::endl;
    }
};

struct Derived2 : Base<Derived2>
{
    void implementation ()
    {
        std::cout << "Derived2::implementation" << std::endl;
    }

    static void static_sub_func ()
    {
        std::cout << "Derived2::static_sub_func" << std::endl;
    }
};

int
main ()
{
    Base<Derived> b;
    b.interface ();

    Base<Derived2> b2;
    b2.interface ();
}
