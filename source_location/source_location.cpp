#include <source_location>
#include <iostream>

int
main ()
{
    auto sl = std::source_location ().current ();
    std::cout << sl.line () << std::endl;
    std::cout << sl.column () << std::endl;
    std::cout << sl.file_name () << std::endl;
    std::cout << sl.function_name () << std::endl;
}
