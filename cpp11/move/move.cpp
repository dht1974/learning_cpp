#include <iostream>
#include <cassert>

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
};

int
main ()
{
    AAA aaa;

    aaa.int_ptr = new int[8];
    for (int i = 1; i <= 8; ++i) {
        *(aaa.int_ptr + (i - 1)) = i;
    }

    /// 注意这是个 forwarding_reference，不是rvalue reference
    /// 下面两行效果一样，没有新对象产生，bbb和aaa的int_ptr指向相同位置
    /// AAA&& bbb = std::move (aaa);
    /// AAA&& bbb = aaa;

    /// bbb是一个rvalue reference，会创建一个新的AAA对象，并进行move操作
    /// 
    ///   move之前
    ///   +-------------+      +-----------------+     +-------------+
    ///   | aaa.int_ptr | -->  | 1 | 2 | ... | 8 |     | bbb.int_ptr | --> nullptr
    ///   +-------------+      +-----------------+     +-------------+
    ///
    ///                          o---------------------------------------o
    ///   move之后               |                                       |
    ///                          V                                       |
    ///   +-------------+      +-----------------+     +-------------+   |
    ///   | aaa.int_ptr | -o   | 1 | 2 | ... | 8 |     | bbb.int_ptr | --o
    ///   +-------------+  |   +-----------------+     +-------------+
    ///                    |
    ///                    V
    ///                nullptr （需要AAA在move构造函数中或move赋值构造函数中设置，否则在析构时会释放两次）
    ///
    auto bbb = std::move (aaa);

#if 0
    for (int i = 1; i <= 8; ++i) {
        std::cout << (aaa.int_ptr + (i - 1)) << ": "<< *(aaa.int_ptr + (i - 1)) << '\n';
    }
#endif

    std::cout << "---------------------\n";
    for (int i = 1; i <= 8; ++i) {
        std::cout << (bbb.int_ptr + (i - 1)) << ": "<< *(bbb.int_ptr + (i - 1)) << '\n';
    }

    assert (aaa.int_ptr == nullptr);
}
