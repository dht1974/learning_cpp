#include <map>
#include <stdio.h>

void display (std::map<int, int>& m) noexcept
{
    for (auto iter = m.begin (); iter != m.end (); ++iter) {
        printf ("%d --> %d\n", iter->first, iter->second);
    }
}

int
main ()
{
    std::map<int, int> m;

    m.insert (std::make_pair (1, 1));
    m.insert (std::make_pair (2, 2));
    m.insert (std::make_pair (3, 3));
    m.insert (std::make_pair (4, 4));
    m.insert (std::make_pair (5, 5));
    m.insert (std::make_pair (6, 6));

    display (m);

    printf ("====================\n");
    for (auto iter = m.begin (); iter != m.end ();) {
        if ((iter->first % 2) == 0) {
            m.erase (iter++);
        } else {
            iter->second += 10;
            ++iter;
        }
    }

    display (m);
}
