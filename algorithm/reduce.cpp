#include <numeric>
#include <iostream>

int
main ()
{
    int a[] {1, 2, 3, 4, 5, 6};
    auto ret = std::reduce (a, a + std::size (a), 0);
    std::cout << ret << std::endl;

    auto ret2 = std::reduce (a, a + std::size (a), 1, [](int i, int j) { return i * j;});
    std::cout << ret2 << std::endl;
}
