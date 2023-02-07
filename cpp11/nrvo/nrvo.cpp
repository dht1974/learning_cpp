#include <iostream>

/// 编译了3个版本，进行对比，参考Makefile
/// C++17 强制编译器实现RVO即便禁止了移动构造函数，对象也能具有URVO能力
/// C++17 Guaranteed copy elision

struct AAA
{
    int *int_ptr {nullptr};

    AAA ()
    {
        std::cout << "AAA constructor" << std::endl;
        std::cout << "new int[8]" << std::endl;
        int_ptr = new int[8];
        for (int i = 1; i <= 8; ++i) {
            *(int_ptr + i - 1) = i;
        }
    }

    ~AAA ()
    {
        std::cout << "~AAA " << int_ptr << std::endl;
        delete [] int_ptr;
    }

    AAA (AAA& aaa) 
    {
        std::cout << "AAA (AAA& aaa)" << std::endl;
        if (int_ptr != nullptr) {
            delete [] int_ptr;
        }
        std::cout << "new int[8]" << std::endl;
        int_ptr = new int[8];
        for (int i = 0; i < 8; ++i) {
            *(int_ptr + i) = *(aaa.int_ptr + i);
        }
    }

    AAA & operator = (AAA& aaa) 
    {
        std::cout << "operator = (AAA&& aaa)" << std::endl;
        if (int_ptr != nullptr) {
            delete [] int_ptr;
        }
        std::cout << "new int[8]" << std::endl;
        int_ptr = new int[8];
        for (int i = 0; i < 8; ++i) {
            *(int_ptr + i) = *(aaa.int_ptr + i);
        }
        return *this;
    }

/// 可以打开这个开关，看看禁止nrvo的情况
#if 1 
    AAA (AAA&& aaa) noexcept
    {
        std::cout << "AAA (AAA&& aaa)" << std::endl;
        int_ptr = aaa.int_ptr;
        aaa.int_ptr = nullptr;
    }

    AAA & operator = (AAA&& aaa) 
    {
        std::cout << "operator = (AAA&& aaa)" << std::endl;
        aaa.int_ptr = int_ptr;
        int_ptr = nullptr;
        return *this;
    }
#endif
};

/// nrvo 
static AAA foo () 
{
    AAA aaa;
    return aaa;
}

/// rvo
static AAA bar () 
{
    return AAA ();
}

int
main ()
{
    auto ref_foo = foo ();
    for (int i = 0; i < 8; ++i) {
        std::cout << *(ref_foo.int_ptr + i) << std::endl;
    }

    auto ref_bar = bar ();
    for (int i = 0; i < 8; ++i) {
        std::cout << *(ref_bar.int_ptr + i) << std::endl;
    }
}
