#include <iostream>
#include <array>
#include <vector>
#include <string>

/// C++14以后，变量也可以参数化为特定的类型，这称为变量模板。

/* bits/ranges_base.h

  template<typename>
    inline constexpr bool disable_sized_range = false;

  template<typename _Tp>
    inline constexpr bool enable_borrowed_range = false;

-------------------------------

namespace std
{
    template<typename T> constexpr bool is_const_v = std::is_const<T>::value;
}

*/

template<typename T> 
constexpr T pi {3.1415926535897932385};

template<typename T = long double>
constexpr T PI = T {3.1415926535897932385};

template<int N>
    std::array<int, N> arr{};  // array with N elements, zero initialized

template <auto N>
    constexpr decltype(N) dval = N;  // type of dval depends on passed value

template<typename T>
    inline constexpr bool vt1 = false;

template<typename>
    inline constexpr bool vt2 = false;

int
main ()
{
    std::cout << pi<double> << '\n';
    std::cout << pi<float> << '\n';

    std::cout << PI<> << '\n';       // outputs a long double
    std::cout << PI<float> << '\n';  // outputs a float

    std::cout << dval<'c'> << '\n'; // N has value 'c' of type char
    arr<10>[0] = 42;                // sets first element of global arr
    for (std::size_t i = 0; i < arr<10>.size (); ++i) {  // uses values set in arr
        std::cout << arr<10>[i] << '\n';
    }

    std::cout << vt1<int> << ", " << vt1<double> << ", " << vt1<std::vector<int>> << '\n';
    std::cout << vt2<int> << ", " << vt2<std::string> << ", " << vt2<std::vector<int>> << '\n';
}
