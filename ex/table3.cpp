#include <iostream>

struct key_t
{

};


/// template<typename Key, typename Value, typename...Args>
template<typename...Args>
struct index_t
{
    bool less (Args&&... args)
    {
        /// return (op (std::forward<Args> (args)),...);
        return (...,op (5, std::forward<Args> (args)));
    }

private:
    template<typename T>
    bool op (int a, T&& t)
    {
        std::cout << "op: " << t << std::endl;
        return a < t;
    }
};

int
main ()
{
    index_t<int, int64_t, uint32_t, int, int> index;/// (1, 2, 3, 4, 5);
    index.less (1, 2, 3, 4, 5);
}
