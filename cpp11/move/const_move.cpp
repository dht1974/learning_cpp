#include <iostream>
#include <cassert>

/// const 不能用于move语义，因为const是不容许修改的，而move本质上是steal，需要修改

struct AAA
{
    int *int_ptr {nullptr};

    AAA ()
    {
        std::cout << "AAA constructor" << std::endl;
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

    /// 不能加const，编译不过
    AAA (AAA&& aaa) noexcept /// const
    {
        std::cout << "AAA (AAA&& aaa)" << std::endl;
        int_ptr = aaa.int_ptr;
        aaa.int_ptr = nullptr;
    }

    AAA & operator = (AAA&& aaa) noexcept
    {
        std::cout << "operator = (AAA&& aaa)" << std::endl;
        aaa.int_ptr = int_ptr;
        int_ptr = nullptr;
        return *this;
    }
};

void foo ()
{
    /// 加上const会编译出错
    /// const AAA aaa;   
    AAA aaa;
    auto ccc = std::move (aaa);
}

int
main ()
{
    AAA aaa;

    aaa.int_ptr = new int[8];
    for (int i = 1; i <= 8; ++i) {
        *(aaa.int_ptr + (i - 1)) = i;
    }

    std::cout << "auto bbb = std::move (aaa)" << std::endl;
    auto bbb = std::move (aaa);
    
    foo ();
}
