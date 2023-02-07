#include <iostream>
#include <cassert>
#include <vector>

/// 如果移动构造函数没有noexcept的话，在stl容器不会调用，move失效

/// 关于noexcept的使用，从网上给出的建议是：
/// 1. 只在move constructor中使用，因为会对性能有比较大的影响
/// 2. move assignment
/// 3. swap

struct AAA
{
    int *int_ptr {nullptr};

    AAA ()
    {
        std::cout << "AAA constructor" << std::endl;

        int_ptr = new int[8];
        for (int i = 1; i <= 8; ++i) {
            *(int_ptr + (i - 1)) = i;
        }
    }

    ~AAA ()
    {
        std::cout << "~AAA " << int_ptr << std::endl;
        delete [] int_ptr;
    }

    AAA (AAA& aaa)
    {
        std::cout << "AAA& " << std::endl;

        if (int_ptr != nullptr) {
            delete [] int_ptr;
        }

        int_ptr = new int[8];
        for (int i = 1; i <= 8; ++i) {
            *(int_ptr + (i - 1)) = *(aaa.int_ptr + (i - 1));
        }
    }

    AAA & operator = (AAA& aaa) 
    {
        std::cout << " = AAA& " << std::endl;
        if (int_ptr != nullptr) {
            delete [] int_ptr;
        }

        int_ptr = new int[8];
        for (int i = 1; i <= 8; ++i) {
            *(int_ptr + (i - 1)) = *(aaa.int_ptr + (i - 1));
        }

        return *this;
    }

    /// 建议将noexcept去掉，再单步调试看看，vector的resize是如何不使用
    /// move constructor，而使用copy constructor
    AAA (AAA&& aaa) noexcept 
    {
        std::cout << "AAA (AAA&& aaa)" << std::endl;
        int_ptr = aaa.int_ptr;
        aaa.int_ptr = nullptr;
    }

    AAA & operator = (AAA&& aaa) /// noexcept
    {
        std::cout << "operator = (AAA&& aaa)" << std::endl;
        aaa.int_ptr = int_ptr;
        int_ptr = nullptr;
        return *this;
    }
};

int
main ()
{
    std::vector<AAA> v;
    v.reserve (2);
    /// 临时变量也是rvalue
    v.push_back (AAA ());
    v.push_back (AAA ());

    /// 可以将move construct中的noexcept去掉，看看运行效果，会调用拷贝构造函数
    /// 原因：resize后需要将之前放入的两个AAA对象，移动到新空间中，如果采用移动中发生了
    /// 异常，那么原始对象数据可能因为异常而丢失，而在拷贝构造函数中，由于进行的是资源拷贝操作，
    /// 原始数据不会被更改，因此即使抛出异常也不会影响数据最终的正确性。
    v.resize (8);
}
