#include <ranges>
#include <algorithm>
#include <vector>
#include <iostream>

int
main ()
{
    std::vector v {3, 2, 1, 5, -1, 32, -100};
    std::ranges::sort (v);
    std::cout << "----- v -----" << std::endl;
    std::copy (v.begin (), v.end (), std::ostream_iterator<int> (std::cout, "\n"));

    std::cout << "----- views::take (3) -----" << std::endl;
    auto ret = v | std::views::take (3);
    std::copy (ret.begin (), ret.end (), std::ostream_iterator<int> (std::cout, "\n"));
}
