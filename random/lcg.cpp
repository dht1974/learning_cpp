#include <random>
#include <iostream>

/// 线性同余发生器
/// 公式： Xn+1 = (AXn + C) % M
int
main ()
{
    size_t seed = 5;
    std::linear_congruential_engine<size_t, 5, 8, 1133721> lce (seed);

    std::cout << "min: " << lce.min () << '\n';
    std::cout << "max: " << lce.max () << '\n';
    std::cout << '\n';
    for (int i = 0; i < 10; ++i) {
        std::cout << lce () << '\n';
    }
}
