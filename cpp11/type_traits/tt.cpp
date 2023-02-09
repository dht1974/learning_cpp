#include <iostream>
#include <type_traits>

struct AAA 
{
};

struct BBB
{
    BBB () = delete;
};

int
main ()
{
    std::cout << std::is_scalar_v<bool> << std::endl;
    std::cout << std::is_scalar_v<int *> << std::endl;
    std::cout << std::is_scalar_v<const int *> << std::endl;
    std::cout << std::is_scalar_v<std::byte> << std::endl;

    std::cout << std::is_constructible_v<AAA> << std::endl;
    std::cout << std::is_constructible_v<BBB> << std::endl;
}
