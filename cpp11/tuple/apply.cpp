#include <tuple>
#include <iostream>

/// std::apply 和 R语言的apply含义不一样，std::apply 使用tuple

int
main ()
{
    auto t1 {std::make_tuple (1)};
    auto t2 {std::make_tuple (1, 2)};
    auto t3 {std::make_tuple (1, 2, 3)};

    std::apply ([] (int i) {std::cout << i << std::endl;}, t1);
    std::apply ([] (int i, int j) {std::cout << i << " : " << j << std::endl;}, t2);
    std::apply ([] (int i, int j, int k) {std::cout << i << " : " << j << " : " << k << std::endl;}, t3);

    /// 使用fold expression 
    std::apply ([] (auto... args) { ((std::cout << args << std::endl),...); }, 
        std::make_tuple (1, 2.0, 3, 4.0, 5, 7, "hello"));
}
