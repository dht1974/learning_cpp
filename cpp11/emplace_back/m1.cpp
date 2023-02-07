#include <vector>
#include <iostream>

struct AAA 
{
    int _a;

    AAA ()
    {
        std::cout << "constructor" << std::endl;
    }

    AAA (int a)
    : _a (a)
    {}

    ~AAA ()
    {
        std::cout << "destructor" << std::endl;
    }

    AAA (const AAA&) 
    {
        std::cout << "copy constructor" << std::endl;
    }

    AAA operator= (const AAA&) 
    {
        std::cout << "assign constructor" << std::endl;
        return *this;
    }

    AAA (const AAA&&) noexcept
    {
        std::cout << "move constructor" << std::endl;
    }

    AAA operator= (const AAA&&) 
    {
        std::cout << "move assign constructor" << std::endl;
        return *this;
    }
};

int
main ()
{
    std::vector<AAA> v;
    v.reserve (32);

    std::cout << "------- push_back rvalue -------" << std::endl;
    AAA aaa;
    v.push_back (std::move (aaa));

    std::cout << "------- push_back temporty var rvalue -------" << std::endl;
    v.push_back (AAA ());

    std::cout << "------- emplace_back -------" << std::endl;
    v.emplace_back (10);
    /// 多加入一个，在vector析构时，会多打一条析构信息
    v.emplace_back (11);
    std::cout << "-----------------------" << std::endl;
}
