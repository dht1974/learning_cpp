#include <numeric>
#include <iostream>

int
main ()
{
#if 0
    int a[] {1, 2, 3, 4, 5, 6};
    auto r1 = std::reduce (a, a + std::size (a), 0);
    std::cout << r1 << std::endl;

    auto r2 = std::reduce (a, a + std::size (a), 1, [](int i, int j) { return i * j;});
    std::cout << r2 << std::endl;
#endif
    ///auto r3 = std::gcd (12125, 1235);
     auto r3 = std::gcd (1233, 27);
    // std::cout << r3 << std::end;
    /// auto r3 = std::gcd (12125, 1235);
    std::cout << r3 << std::endl;
}
