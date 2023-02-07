#include <chrono>
#include <iostream>
#include <thread>

namespace cn = std::chrono;
int
main ()
{
    cn::year_month_day ymd {cn::year (2023), cn::month (1), cn::day (29)};

    cn::seconds sec (1);
    ++sec;
    --sec;
    std::cout << "sleep "<< sec.count () << " seconds" << std::endl;

    auto tp1 = std::chrono::steady_clock::now ();
    std::this_thread::sleep_for (sec);
    auto tp2 = std::chrono::steady_clock::now ();
    std::cout << std::chrono::duration_cast<std::chrono::microseconds> (tp2 - tp1).count () << 
        " microseconds" << std::endl;
}
