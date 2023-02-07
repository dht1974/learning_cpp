#include <iostream>

/// const lvalue 可以使用右值
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
	/// 编译错误，左值引用不能用右值赋值
	/// int& la = 1;

	/// 但是，{ const 左值引用能用右值赋值 }
	const int& clb = 10;
	const int& clc = 20;

	std::cout << clb << std::endl;
	std::cout << clc << std::endl;

}
