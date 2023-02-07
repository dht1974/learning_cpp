#include <type_traits>
#include <iostream>

/// 下面代码摘自<type_traits>，比较难看明白

/// TODO 目前这部分代码还未全部理解

template<typename _From, typename _To,
       bool = std::__or_<std::is_void<_From>, std::is_function<_To>,
                    std::is_array<_To>>::value>
struct is_convertible_helper
{
    typedef typename std::is_void<_To>::type type;
};

/// 偏特化
template<typename _From, typename _To>
class is_convertible_helper<_From, _To, false>
{
    /// 这是一个模板函数声明，返回值是void
    template<typename _To1>
        static void __test_aux(_To1) noexcept;

    /// 一个模板函数__test的声明，
    template<typename _From1, typename _To1,
        /// 当一个参数不被使用时，可以把参数名称省略掉。 typename = decltype
        typename = decltype(__test_aux<_To1>(std::declval<_From1>()))>
    static std::true_type __test(int);

    template<typename, typename>
        static std::false_type
        __test(...);

public:
    typedef decltype(__test<_From, _To>(0)) type;
};

template<typename _From, typename _To>
struct IS_CONVERTIBLE
    : public is_convertible_helper<_From, _To>::type
{};

int
main ()
{
    /// if (IS_CONVERTIBLE<char, int>::type::value == std::true_type::value) 
    if (IS_CONVERTIBLE<char, int>::type::value == true) {
        std::cout << "char --> int ok.\n";
    } else {
        std::cout << "char --> int failed.\n";
    }
}
