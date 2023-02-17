#include <iostream>
#include <vector>

/// TODO 还有很多技术问题，目前没有答案

struct st_order
{
    int member_no;
    int client_no;
    int contract_no;

    int price;
    int qty;
    int bs_flag;
};

template<typename...Fields>
class index_1 
{
public: 
    bool less (Fields&&... fields) const noexcept
    {
        auto ret = (0 + ... + fields);          
        if (ret < 1) {
            return false;
        } else {
            return true;
        }
    }
private:
    template<typename T>
    bool op (T&& t)
    {
        return true;
    }
};

#if 0
template<typename _Tp, typename _Up>
    struct __replace_first_arg
    { };

template<template<typename, typename...> class _SomeTemplate, typename _Up,
           typename _Tp, typename... _Types>
    struct __replace_first_arg<_SomeTemplate<_Tp, _Types...>, _Up>
    { using type = _SomeTemplate<_Up, _Types...>; };
#endif

/// template<typename T, typename U, typename ...P>    
/// struct table_t
/// {};

/// template<typename ST, template <typename, typename...>class Idxs, typename T, typename... Types>
/// struct table_t<ST, Idxs<T, Types...>>
template<typename ST, typename... Idxs>
struct table_t
{
    table_t ()
    {

    }

    bool insert (ST* st_ptr, Idxs... indexs)
    {
     
        return true;   
    }

};

int
main ()
{
    auto idx1 = index_1<int, double, int64_t, int> ();
    auto idx2 = index_1<int, double, int64_t, int, char> ();
    std::cout << idx1.less (1, 2.0, 2, -10) << std::endl;
    /// table_t<st_order, index_1<int, int, int>, index_1<int, int, int, int64_t>, index_1<int, uint32_t, int, int8_t, uint16_t>> t;
    table_t<st_order, index_1<int, double, int64_t, int>, index_1<int, double, int64_t, int, char>> t;
    st_order *order_ptr = new st_order;
    order_ptr->price = 100;
    order_ptr->qty = 100;
    t.insert (order_ptr, idx1, idx2);
}
