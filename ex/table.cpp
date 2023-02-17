#include <iostream>

/// TODO 还有很多技术问题，目前没有答案

struct st_order
{
    int price;
    int qty;
};

/// template<template <typename...Idx>class...Idxs>
template<typename ST, typename...Idxs>
/// template<typename ST>
struct table_t 
{
    table_t ()
    {

    }

    bool insert (ST* st_ptr)
    {
     
        return true;   
    }
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

    }
};

int
main ()
{
    auto ret = index_1<int, int, int>();
    std::cout << ret.less (1, 2, -10) << std::endl;
    table_t<st_order, index_1<int, int, int>, index_1<int, int, int, int64_t>, index_1<int, uint32_t, int, int8_t, uint16_t>> t;
    st_order *order_ptr = new st_order;
    order_ptr->price = 100;
    order_ptr->qty = 100;
    t.insert (order_ptr);
}
