#include <iostream>
#include <unordered_map>
#include <map>

int
main ()
{
    std::unordered_map<int, int> m {
        {1, 11}, {2, 12}, {3, 13},
        {4, 14}, {5, 15}, {6, 16},
        {7, 17}, {8, 18}, {9, 19},
    };

    auto node = m.extract (3);
    if (node.empty () == true) {
        std::cout << "extract err." << std::endl;
        return -1;
    }

    for (auto [k, v] : m) {
        std::cout << k << " : " << v << std::endl;
    }

    node.mapped () = 100;
    node.key () = 33;
    
    /// m.insert ({node.key (), node.mapped ()});
    m.insert (std::move (node));
    std::cout << "------" << std::endl;
    for (auto [k, v] : m) {
        std::cout << k << " : " << v << std::endl;
    }
}
