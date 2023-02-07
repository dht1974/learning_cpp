#include <iostream>
#include <limits>

int
main ()
{
    std::cout << "int max: " << std::numeric_limits<int>::max () << std::endl;
    std::cout << "int min: " << std::numeric_limits<int>::min () << std::endl;
    std::cout << "int lowest: " << std::numeric_limits<int>::lowest () << std::endl;

    /// XXX XXX XXX 注意double的 min不是负值，需要用lowest
    std::cout << "double max: " << std::numeric_limits<double>::max () << std::endl;
    std::cout << "double min: " << std::numeric_limits<double>::min () << std::endl;
    std::cout << "double lowest: " << std::numeric_limits<double>::lowest () << std::endl;

    std::cout << "double epsilon: " << std::numeric_limits<double>::epsilon () << std::endl;
    std::cout << "double round_error: " << std::numeric_limits<double>::round_error() << std::endl;
    std::cout << "double infinity: " << std::numeric_limits<double>::infinity () << std::endl;
    std::cout << "double quiet_NaN: " << std::numeric_limits<double>::quiet_NaN () << std::endl;
    /// std::cout << "double : " << std::numeric_limits<double>:: () << std::endl;
    std::cout << "double signaling_NaN: " << std::numeric_limits<double>::signaling_NaN () << std::endl;
    std::cout << "double denorm_min: " << std::numeric_limits<double>::denorm_min () << std::endl;
}
