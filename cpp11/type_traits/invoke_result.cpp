#include <type_traits>
#include <iostream>

/*
   std::result_of 在c++17中变成deprecated，建议使用std::invoke_result。为了兼容
   std::result_of 基于std::invoke_result进行构建

以下面functor AAA为例
    std::invoke_result<AAA, int, int>::type abc;

type_traits:

3027   /// std::invoke_result
3028   template<typename _Functor, typename... _ArgTypes>
3029     struct invoke_result
3030     : public __invoke_result<_Functor, _ArgTypes...>
3031     {
3032       static_assert(std::__is_complete_or_unbounded(__type_identity<_Functor>{}),
3033     "_Functor must be a complete class or an unbounded array");
3034       static_assert((std::__is_complete_or_unbounded(
3035     __type_identity<_ArgTypes>{}) && ...),
3036     "each argument type must be a complete class or an unbounded array");
3037     };

                            |
                            V

AAA是一个类 2577 ~ 2579返回 false，而2580 ~ 2582返回true

2573   // __invoke_result (std::invoke_result for C++11)
2574   template<typename _Functor, typename... _ArgTypes>
2575     struct __invoke_result
2576     : public __result_of_impl<
2577         is_member_object_pointer<
2578           typename remove_reference<_Functor>::type
2579         >::value,
2580         is_member_function_pointer<
2581           typename remove_reference<_Functor>::type
2582         >::value,
2583     _Functor, _ArgTypes...
2584       >::type
2585     { };

经过编译 __result_of_impl<false, true, _Functor, _ArgTypes...>::type

                            |
                            V

匹配到下面这个类
2548   template<typename _MemPtr, typename _Arg, typename... _Args>
2549     struct __result_of_impl<false, true, _MemPtr, _Arg, _Args...>
2550     : public __result_of_memfun<__decay_t<_MemPtr>,
2551                 typename __inv_unwrap<_Arg>::type, _Args...>
2552     { };

                            |
                            V

2505   template<typename _MemPtr, typename _Arg, typename... _Args>
2506     struct __result_of_memfun;
2507                 
2508   template<typename _Res, typename _Class, typename _Arg, typename... _Args>
2509     struct __result_of_memfun<_Res _Class::*, _Arg, _Args...>
2510     {
2511       typedef typename remove_reference<_Arg>::type _Argval;
2512       typedef _Res _Class::* _MemPtr;
2513       typedef typename __conditional_t<is_base_of<_Class, _Argval>::value,
2514         __result_of_memfun_ref<_MemPtr, _Arg, _Args...>,
2515         __result_of_memfun_deref<_MemPtr, _Arg, _Args...>
2516       >::type type;
2517     };

*/

/// functor
struct AAA
{
    int operator()(int a, int b)
    {
        return a + b;
    }
};

int foo ()
{
    return 0;
}

int
main ()
{
    int a = AAA () (3, 6);
    std::cout << a << std::endl;

    std::invoke_result<AAA, int, int>::type abc;
    abc = 100;
    std::cout << abc << std::endl;

    std::invoke_result <decltype ([]()->int { return 0;})>::type def;
    def = 1000;
    std::cout << def << std::endl;

    std::invoke_result <decltype (foo)>::type hgi;
    hgi = 10000;
    std::cout << hgi << std::endl;
}
