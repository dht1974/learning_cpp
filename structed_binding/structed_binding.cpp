#include <iostream>

struct AAA 
{
    int a {};
    int b {};
    int c {};
};

int
main ()
{
    AAA aaa {1, 2, 3};
    auto [a, b, c] = aaa;
    std::cout << a << " : " << b << " : " << c << std::endl;

    auto& [aa, bb, cc] = aaa;
    bb = 22;
    std::cout << aa << " : " << bb << " : " << cc << std::endl;
}
