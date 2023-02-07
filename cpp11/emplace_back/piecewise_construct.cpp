#include <vector>
#include <iostream>
#include <utility>
#include <tuple>

struct AAA_key
{   
    int a;
    int b;

    AAA_key (int a, int b)
    {
        this->a = a;
        this->b = b;
    }
};

struct AAA
{
    int a;
    int b;
    int c;

    AAA (int a, int b, int c)
    {
        this->a = a;
        this->b = b;
        this->c = c;
    }

    void show ()
    {
        std::cout << a << " : " << b << " : " << c << std::endl;
    }
};

int
main ()
{
    std::vector<std::pair<AAA_key, AAA>> vec;
    vec.reserve (16);

    vec.push_back (std::make_pair (AAA_key (1, 2), AAA (1, 2 ,3)));
    vec.emplace_back (std::piecewise_construct, 
        std::forward_as_tuple (11, 22), 
        std::forward_as_tuple (11, 22, 33));

    vec[0].second.show ();
    vec[1].second.show ();

    return 0;
}
