#include <future>
#include <thread>
#include <iostream>
#include <chrono>
#include <vector>
#include <algorithm>
#include <numeric>
#include <cstdarg>

/*
 部分专家观点：
 async/future/promise 模型则很低效，而且很难让用户正确使用，并且严重缺乏对泛型的支持

 我的观点：
 async 启动一个线程，代价比较大，如果用于大批量长时间的工作，使用没问题，如果是小任务
 有点得不偿失，关键看应用场景，不能一概否定
*/
int foo (int a, int b)
{
    std::this_thread::sleep_for (std::chrono::seconds (3));
    return a + b;
}

struct AAA 
{
    int foo (int count, ...)
    {
        int ret {0};
        std::va_list v;
        va_start (v, count);
        for (int i = 0; i < count; ++i) {
            ret += va_arg (v, int);
        }
        va_end (v);
        return ret;   
    }
};

int
main ()
{
    auto f = std::async (std::launch::async, foo, 3, 5);
    std::cout << "before wait" << std::endl;

    f.wait ();
    auto result = f.get ();
    std::cout << result << std::endl;

    std::vector<int> v {1, 3, 5, 7, 9};
    auto fun1 = [&v] ()-> int {
        return std::accumulate (v.begin (), v.end (), 0);
    };
    auto f1 = std::async (std::launch::async, fun1);
    f1.wait ();
    std::cout << f1.get () << std::endl;

    AAA aaa;
    auto f2 = std::async (std::launch::async, &AAA::foo, &aaa, 5, 6, 7, 8, 9, 10);
    f2.wait ();
    std::cout << f2.get () << std::endl;
}
