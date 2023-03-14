#include <iostream>
#include <numeric>

int
main ()
{
    const int N = 32;
    int arange[N];

    /// 两种写法都可以
    /// std::iota (arange, arange + N, 1);
    std::iota (std::begin (arange), std::end (arange), 1);

    for (int i = 0; i < N; ++i) {
        std::cout << arange[i] << std::endl;
    }
}
