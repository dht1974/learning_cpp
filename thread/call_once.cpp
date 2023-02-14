#include <thread>
#include <iostream>
#include <mutex>
#include <chrono>

std::once_flag flag;
int i = 0;
int foo ()
{
    i += 100;
    return i;
}

void t_fun ()
{
    std::this_thread::sleep_for (std::chrono::seconds (3));
    std::call_once (flag, foo);
}

int
main ()
{
    std::thread t1 (t_fun);
    std::thread t2 (t_fun);
    std::thread t3 (t_fun);
    t1.join ();
    t2.join ();
    t3.join ();

    std::cout << i << std::endl;
    std::cout << foo () << std::endl;
}
