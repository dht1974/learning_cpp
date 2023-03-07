#include <bit>
#include <iostream>
#include <string>

bool is_power_of_2 (unsigned int d)
{
    return std::has_single_bit<unsigned int> (d);
}

int
main (int argc, char *argv[])
{
    if (argc == 1) {
        return -1;
    }

    /// is_power_of_2
    auto ret = is_power_of_2 (std::stoul (argv[1]));
    if (ret == true) {
        std::cout << argv[1] << " is power of 2" << std::endl;
    } else {
        std::cout << argv[1] << " is not power of 2" << std::endl;
    }

    return 0;
}
