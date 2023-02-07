#include <initializer_list>
#include <variant>
#include <iostream>
#include <string>
#include <vector>
#include <map>
/// std::variant实现类似union的功能

int
main ()
{
    std::variant<int, double, std::string, std::vector<int>, std::map<int, int>> v;
    std::cout << v.index () << std::endl;
    v = 133;
    std::cout << v.index () << std::endl;
    v = {"aaa"};
    std::cout << v.index () << std::endl;
    v = 123.01;
    std::cout << v.index () << std::endl;
    std::vector vec {1, 2, 3, 4, 5};
    v = vec;
    std::cout << v.index () << std::endl;
    std::map<int, int> m {{1, 2}, {3, 4}, {5, 6}};
    v = m;
    std::cout << v.index () << std::endl;

    auto ret = std::get<4> (v); 
    for (auto& i : ret) {
        std::cout << i.first << " : " << i.second << std::endl;
    }

    try {
        std::cout << std::get<1> (v) << std::endl;
    } catch (std::bad_variant_access& e) {
        std::cout << e.what () << std::endl;
    }
}
