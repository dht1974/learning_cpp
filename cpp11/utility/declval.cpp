#include <utility>
#include <iostream>
#include <type_traits>

/* <type_traits>
    template<class T>
    typename std::add_rvalue_reference<T>::type 
    declval() noexcept;    
*/



template<typename T>
class AAA
{
public:

    int value ()
    {
        return 1;
    }

    void show ()
    {
        std::cout << "AAA" << std::endl;
    }
};
  /// && requires { static_cast<_To>(std::declval<_From>()); };

int
main ()
{
    AAA<int> aaa;
    decltype (aaa) bbb;

    bbb.show ();

    /// std::declval返回的是右值引用，所以要用std::move把左值变成右值
    decltype (std::declval<AAA<int>> ()) ccc = std::move (aaa);
    ccc.show ();

    decltype (std::declval<int> ()) ddd = 1;
    std::cout << ddd << std::endl;
}
