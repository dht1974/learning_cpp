#include <vector>
#include <iomanip>
#include <iostream>
#include <ranges>
#include <string_view>

int
main ()
{
    /// reverse，并且可以不用写成std::vector<int>，编译器可以自己推导出来
    std::vector a {1, 2, 3};
    for (int i : (a | std::ranges::views::reverse)) {
        std::cout << i << '\n';
    }

    /// drop
    std::cout << '\n';
    std::vector vec {1, 2, 3, 4, 5, 6};
    auto v = vec | std::ranges::views::reverse | std::views::drop (2);
    for (auto & i : v) {
        std::cout << i << '\n';
    }

    /// take
    std::cout << '\n';
    for (auto & i : vec | std::views::take (2)) {
        std::cout << i << '\n';
    }

    /// take_while, TODO
    std::cout << '\n';
    for (auto & i : vec | std::views::take_while ([](int i)->int {return i % 2 == 0;})) {
        std::cout << i << '\n';
    }

#if 1
    /// filter 
    std::cout << '\n';
    for (auto & i : vec | std::views::filter ([](int i) ->int {return i % 2 == 0;})) {
        std::cout << i << '\n';
    }
#endif

    /// split 
    std::cout << '\n';
    std::string s ("a,b,c,d,e");
    auto sr = s | std::views::split (',');
    for (const auto& i : sr) {
        std::cout << std::string_view (i.begin (), i.end ()) << '\n';
    }

    constexpr std::string_view words{"Hello^_^C++^_^20^_^!"};
    constexpr std::string_view delim{"^_^"};
    std::cout << '\n';
    for (const auto word : std::views::split(words, delim)) {
        std::cout << std::quoted(std::string_view{word.begin(), word.end()}) << ' ';
    }

#if 0
    /// join
    std::cout << '\n';
    constexpr std::string_view sv1 ("abc");
    constexpr std::string_view sv2 ("def");
    constexpr std::string_view sv3 ("ghi");
    constexpr std::vector<std::string_view> sv {sv1, sv2, sv3}
    auto jr = std::views::join (sv);
#endif
}
