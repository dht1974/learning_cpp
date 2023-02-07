#include <iostream>

template<int... Args>
struct AAA
{
    AAA ()
    {
        std::cout << sizeof... (Args) << std::endl;
    }
};

int
main ()
{
    AAA<int, int, int, int, int> a ();
}
