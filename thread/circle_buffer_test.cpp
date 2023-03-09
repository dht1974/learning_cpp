#include "circle_buffer2.h"
#include <thread>

/// 测试facebook folly的无锁队列
struct AAA
{
    uint64_t a;
    uint64_t b;

    AAA (uint64_t aa, uint64_t bb) {
        a = aa;
        b = bb;
    }
};

/// folly::circle_buffer<AAA> que (4096);
folly::circle_buffer2<AAA> que (4096);

void t1_fun ()
{
    uint64_t i {0};
    for (;;) {
        if (que.isFull () == false) {
            que.write (i, i);
            ++i;
        } else {
            /// printf ("full\n");
        }
    }
}

void t2_fun ()
{
    uint64_t i {0};
    struct AAA aa (0, 0);
    for (;;) {
        if (que.isEmpty () == false) {
            if (que.read (aa) == true) {
                if (aa.a != i) {
                    printf ("err.\n");
                    exit (-1);
                }

                if (aa.a >= 500000000) {
                    exit (0);
                }
                if (aa.a % 100== 0) {
                    printf ("%lu\n", aa.a);
                }
                ++i;
            } else {
                printf ("read err\n");
            }
        } else {
            /// printf ("empty\n");
        }
    }
}

int
main ()
{
    std::thread t1 (t1_fun);
    std::thread t2 (t2_fun);
    
    t1.join ();
    t2.join ();
}
