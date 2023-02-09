#include <iostream>

/// CPO（customization point object）

namespace thirdparty 
{
    struct complicated_structure 
    {

        /// friend 函数不是成员函数
        friend void do_something(complicated_structure &t) noexcept 
        {
            (void)t;
            std::cout << "customized do something" << std::endl;
        }
    };

    struct simple_structure {
    };
}

namespace standard 
{

    namespace detail 
    {
        template<typename T>
            void do_something(T &t) noexcept 
            {
                (void)t;
                std::cout << "standard do something" << std::endl;
            }

        struct do_something_t 
        {
            template<typename T>
                void operator()(T &t) noexcept 
                {
                    std::cout << "operator()" << std::endl;
                    do_something (t);
                }
        };
    }

    inline detail::do_something_t do_something {};
}


int main() 
{
   thirdparty::simple_structure s;
   standard::do_something(s);

   thirdparty::complicated_structure c;
   /// std::cout << "----------" << std::endl;
   /// do_something (c);
   /// std::cout << "----------" << std::endl;
   standard::do_something(c);

   using namespace standard;
   do_something(s);
   do_something(c);

   return 0;
}
