#include <iostream>
#include <type_traits>

int
main ()
{
    std::cout << std::is_scalar_v<bool> << std::endl;
    std::cout << std::is_scalar_v<int *> << std::endl;
    std::cout << std::is_scalar_v<const int *> << std::endl;
    std::cout << std::is_scalar_v<std::byte> << std::endl;
}
