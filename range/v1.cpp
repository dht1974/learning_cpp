#include <ranges>
#include <iostream>
#include <algorithm>
#include <string>
#include <iomanip>
#include <iterator>
#include <sstream>
#include <vector>
#include <numeric>

void iota_view ()
{
    for (int i : std::ranges::iota_view {1, 10}) {
        std::cout << i << ' ';
    }
    std::cout << '\n';

    for (int i : std::views::iota (1, 10)) {
        std::cout << i << ' ';
    }
    std::cout << '\n';

    struct Bound
    {
        int bound;
        bool operator==(int x) const { return x == bound; }
    };
    for (int i : std::views::iota (1, Bound {10})) {
        std::cout << i << ' ';
    }
    std::cout << '\n';

    for (int i : std::views::iota (1) | std::views::take (9))
        std::cout << i << ' ';
    std::cout << '\n';

    std::ranges::for_each (std::views::iota (1, 10), [](int i) {
            std::cout << i << ' ';
            });
    std::cout << '\n';
}

/// https://en.cppreference.com/w/cpp/ranges/basic_istream_view
void istream_view ()
{
    auto words = std::istringstream {"today is yesterday’s tomorrow"};
    for (const auto& s: std::ranges::istream_view<std::string> (words)) {
        /// std::cout << std::quoted (s, '/') << ' ';
        std::cout << s << ' ';
    }
    std::cout << '\n';
 
    auto floats = std::istringstream {"1.1  2.2\t3.3\v4.4\f55\n66\r7.7 8.8"};
    /// auto floats = std::istringstream {"1.1, 2.2, 3.3, 4.4, 55, 66, 7.7, 8.8, rb2311"};
    std::ranges::copy (
        std::ranges::istream_view<float> (floats),
        std::ostream_iterator<float> {std::cout, ", "});
    std::cout << '\n';
}

void ref_view ()
{
    const std::string s {"cosmos"};
    const std::ranges::take_view tv {s, 3};
    const std::ranges::ref_view rv {tv};

    std::cout
        << std::boolalpha
        << "call empty () : " << rv.empty () << '\n'
        << "call size ()  : " << rv.size () << '\n'
        << "call begin () : " << *rv.begin () << '\n'
        << "call end ()   : " << *(rv.end () - 1) << '\n'
        << "call data ()  : " << rv.data () << '\n'
        << "call base ()  : " << rv.base ().size () << '\n' // ~> tv.size()
        << "range-for    : ";

    for (const auto c: rv) { std::cout << c; }
    std::cout << '\n';
}

void owning_view ()
{
    std::vector<int> v = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    std::ranges::owning_view<std::vector<int>> ov {std::move (v)};
    std::copy (ov.begin (), ov.end (), std::ostream_iterator<int> (std::cout, "\n"));
}

void split_view ()
{
    std::vector<int> rg { 1, 2, 3, 1, 2, 3, 4, 5, 6 };

    for (const auto& subrange : rg | std::views::split (',')) {
        for (const auto& elem : subrange) {
            std::cout << elem << ' ';
        }
        std::cout << '\n';
    }

    std::string s {"a1,a2,a3,a4,a5,10,20,30,40,50"};
    for (const auto& subrange : s | std::views::split (',')) {
#if 1
        for (const auto& elem : subrange) {
            std::cout << "\n";
            std::cout << elem;
        }
        std::cout << '\n';
#endif
    }
}

int 
main ()
{
    iota_view ();
    istream_view ();
    ref_view ();
    owning_view ();

    split_view ();
}
