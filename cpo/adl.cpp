#include <iostream>

/// ADL (argument dependent lookup) 规则。即调用函数时，会参考参数类型的namespace。

/// 从这个例子可以看到，随便引入using namespace std还是有隐患的，尽量每个函数调用
/// 都写命名空间进行明确限定

using namespace std;

namespace n1 
{
    class AAA
    {
    public:
        int a {};
        int *p {};
    };
}

/// 定制swap 只交换数字，不交换指针
void swap (n1::AAA& a, n1::AAA& b)
{
    int tmp = a.a;
    a.a = b.a;
    b.a = tmp;
}

int 
main ()
{
    int a {1};
    int b {2};

    std::cout << "before a/b swap: " << a << " : " << b << std::endl;
    swap (a, b); /// 调用的是std::swap
    std::cout << "after a/b swap: " << a << " : " << b << std::endl;

    n1::AAA aaa;
    aaa.a = 10;
    aaa.p = &a;

    n1::AAA bbb;
    bbb.a = 100;
    bbb.p = &b;

#if 1
    std::cout << "before aaa/bbb swap: " << aaa.a << " : " << bbb.a << std::endl;
    std::cout << "before aaa/bbb swap pointer: " << aaa.p << " : " << bbb.p << std::endl;
    swap (aaa, bbb);  /// 根据ADL原则，会定位到定制的swap
    std::cout << "after aaa/bbb swap: " << aaa.a << " : " << bbb.a << std::endl;
    std::cout << "after aaa/bbb swap pointer: " << aaa.p << " : " << bbb.p << std::endl;
#else 
    std::cout << "before aaa/bbb swap: " << aaa.a << " : " << bbb.a << std::endl;
    std::cout << "before aaa/bbb swap pointer: " << aaa.p << " : " << bbb.p << std::endl;
    std::swap (aaa, bbb);  /// 根据ADL原则，指定调用std::swap，那么就会调用std::swap
    std::cout << "after aaa/bbb swap: " << aaa.a << " : " << bbb.a << std::endl;
    std::cout << "after aaa/bbb swap pointer: " << aaa.p << " : " << bbb.p << std::endl;
#endif
}
