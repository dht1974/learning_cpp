#include <type_traits>
#include <iostream>

/// 此程序待完善，请忽略

struct AAA
{
    int a;
};

int
main ()
{
    AAA aaa;
    aaa.a = 100;
    auto *pp = &aaa;
    auto p = std::to_address (pp);

    std::cout << p->a << std::endl;
}
