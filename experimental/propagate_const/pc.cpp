#include <experimental/propagate_const>
#include <iostream>

/// 使用propagate_const防止在一个const函数中对一个指针指向变量的修改

class AAA 
{
public:
    AAA (int *ptr) {
        this->ptr = ptr;
    }

    void set_ptr_val (int a) const
    {
#if 0
        int b {3};
        ptr = &b; /// 会编译出错
#endif
        /// 在const函数里进行值修改不会报错，因为不是修改ptr的指向，而是
        /// 修改ptr指向变量的值
        *ptr = a;
    }
private:
    int *ptr {nullptr};
};


class BBB
{
public:
    BBB (int *ptr) {
        this->ptr = ptr;
    }

    void set_ptr_val (int a) const
    {
        /// 编译错误：向只读位置‘((const BBB*)this)->BBB::ptr.std::experimental::fundamentals_v2::propagate_const<int*>::operator*()’赋值
        /// 如果将const去掉，可以编译
#if 0
        *ptr = a;
#else 
        (void)a; /// avoid build warning
#endif
    }
private:
    std::experimental::propagate_const <int*> ptr {nullptr};
};

int
main ()
{
    int a = 10;
    AAA aaa (&a);
    std::cout << "a: " << a << std::endl;
    aaa.set_ptr_val (100);
    std::cout << "a: " << a << std::endl;

    /// 下面需要把BBB::set_ptr_val 的const去掉才可以编译运行
#if 0
    BBB bbb (&a);
    std::cout << "bbb a: " << a << std::endl;
    bbb.set_ptr_val (10000);
    std::cout << "bbb a: " << a << std::endl;
#endif
}


