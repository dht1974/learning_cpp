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

    auto odd_view = v | std::views::filter ([=](int a) {return a % 2 != 0;});
    /// std::ranges::sort (odd_view); /// 不能对view进行sort，编译会出错
    /// materialize to vector
    std::vector<int> odd_vec;
    std::cout << "----------" << std::endl;
    std::ranges::copy (odd_view, std::ostream_iterator<int> (std::cout, "\n"));
    std::cout << "----------" << std::endl;
    std::ranges::copy (odd_view, std::back_inserter (odd_vec));
    auto iter = std::ranges::sort (odd_vec);

    std::ranges::copy (odd_vec, std::ostream_iterator<int> (std::cout, "\n"));
}
