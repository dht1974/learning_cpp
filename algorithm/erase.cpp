#include <algorithm>
#include <vector>
#include <iostream>

void info (std::vector<int>& v)
{
    std::for_each (v.begin (), v.end (), [] (int i) {
        std::cout << i << ' ';
    });
    std::cout << '\n';
    std::cout << "v.size: " << v.size () << " v.capacity: " << v.capacity () << std::endl;
}

int
main ()
{
    std::vector<int> v {1, 2, 1, 3, 1, 4, 1, 5};
 
    std::cout << "before erase: \n"; 
    info (v);

    std::cout << "erase: \n"; 
    /// std::remove (std::erase (v.begin (), v.end (), 1), v.end ());
    std::erase (v.begin (), v.end (), 1);
    info (v);
}
