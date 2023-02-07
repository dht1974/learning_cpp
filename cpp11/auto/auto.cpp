#include <iostream>

class Base 
{
public:
    virtual void foo ()
    {
        std::cout << "Base foo ()" << std::endl;
    }
};

class Derive : public Base
{
public:
    virtual void foo ()
    {
        std::cout << "Derive foo ()" << std::endl;
    }
};

int
main ()
{
    Base *ptr = new Derive;
    
    ptr->foo ();
    /// 由于是按值赋值的，auto被推导到Base
    auto b = *ptr;
    b.foo ();

    /// 引用本质是指针，指向derive
    auto& c = *ptr;
    c.foo ();
}
