#include <iostream>
#include <memory>

struct AAA
{
    int *int_ptr {nullptr};
    int a {0};
    int b {0};

    AAA (int a, int b)
    {
        std::cout << "AAA constructor" << std::endl;
        std::cout << "new int[8]" << std::endl;
        int_ptr = new int[8];
        for (int i = 1; i <= 8; ++i) {
            *(int_ptr + i - 1) = i;
        }

        this->a = a;
        this->b = b;
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

        a = aaa.a;
        b = aaa.b;
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
        a = aaa.a;
        b = aaa.b;
        return *this;
    }

    AAA (AAA&& aaa) noexcept
    {
        std::cout << "AAA (AAA&& aaa)" << std::endl;
        int_ptr = aaa.int_ptr;
        aaa.int_ptr = nullptr;
        a = aaa.a;
        b = aaa.b;
    }

    AAA & operator = (AAA&& aaa) noexcept
    {
        std::cout << "operator = (AAA&& aaa)" << std::endl;
        aaa.int_ptr = int_ptr;
        int_ptr = nullptr;
        a = aaa.a;
        b = aaa.b;
        return *this;
    }
};

auto foo ()
{
    auto uptr = std::make_unique<AAA> (1, 2);

    /// unique_ptr(const unique_ptr&) = delete; 不能使用赋值构造
    /// auto uptr2 = uptr;
    /// auto uptr2 (uptr);
    return uptr;
}

auto bar (std::unique_ptr<AAA>& ptr)
{
    std::cout << "& " << ptr->a << " : " << ptr->b << '\n';
}

auto bar (std::unique_ptr<AAA>&& ptr)
{
    std::cout << "&& " << ptr->a << " : " << ptr->b << '\n';
    return ptr;
}

int
main ()
{
    auto ptr = foo ();
    bar (ptr);

    auto ptr2 = std::move (ptr);

    auto ptr3 = bar (std::move (ptr2));

    /// ptr2已经move过了，不应该再使用，需要使用ptr3
    auto release_ptr = ptr3.release ();
    std::cout << release_ptr->a << " # " << release_ptr->b << '\n';
    /// 被release后的指针，需要自己释放
    delete release_ptr;

    auto ptr4 = std::make_unique<AAA> (10, 20);
    std::cout << "ptr4 " << ptr4->a << " : " << ptr4->b << '\n';
    auto release_ptr4 = ptr4.release ();

    auto ptr5 = std::make_unique<AAA> (100, 200);
    std::cout << "ptr5 " << ptr5->a << " : " << ptr5->b << '\n';
    ptr5.reset (release_ptr4);
    std::cout << "ptr5 reset release_ptr4 " << ptr5->a << " : " << ptr5->b << '\n';
}
