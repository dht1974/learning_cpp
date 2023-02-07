#include <iostream>
#include <ranges>
#include <string_view>

template<typename T>
struct split_or_helper {
    split_or_helper(T t) : t(t) {}
    T t;
};

template<typename T, typename U>
auto operator| (T &&t, const split_or_helper<U> &u) 
{
    return t
        | std::views::transform ([u](auto &&s) { return s | std::views::split (u.t); })
        | std::views::join;
}

template<typename V, typename... Args>
auto split (V&& v, Args&&... args) 
{
    return (std::ranges::single_view (v) | ... | split_or_helper (args));
}

template<typename V, typename... Args>
auto split_remove_empty(V&& v, Args&&... args) 
{
    return split(std::forward<V>(v), std::forward<Args>(args)...)
        | std::views::filter([](auto &&s) { return !s.empty(); });
}
 
int main() 
{
    constexpr std::string_view words {"ab,;cd;ef-,g//h.i"};
    for (const auto &word : split (words, ',', ';', '-', '/')) {
        std::cout << std::string_view(word.begin(), word.end()) << '\n';
    }

    std::cout << "----------\n";

    for (const auto &word : split_remove_empty(words, ',', ';', '-', '/')) {
        std::cout << std::string_view(word.begin(), word.end()) << '\n';
    }
    return 0;
}
