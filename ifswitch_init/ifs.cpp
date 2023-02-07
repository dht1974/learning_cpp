#include <iostream>

int get_result ()
{
    return 3;
}

int
main ()
{
    if (auto i {5}; i > 0) {
        std::cout << "ok" << i << std::endl;;
    } 

    if (auto i = get_result (); i > 0) {
        std::cout << "ok" << i << std::endl;;
    } 

    switch (auto i = get_result (); i)
    {
        case 2:
            std::cout << "switch ok" << i << std::endl;
            break;
        case 3:
            [[fallthrough]];
        default:
            std::cout << "switch defult ok" << i << std::endl;
    }
}
