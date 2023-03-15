#include "ypipe.hpp"
#include <iostream>
#include <thread>

typedef struct {
    int a;
    int b;
    char data[32];
} AAA_t;

zmq::ypipe_t<AAA_t, 4096> aaa_pipe;

static void t1_fun ()
{
    int seq {};
    AAA_t aaa_1;
    AAA_t aaa_2;
    AAA_t aaa_3;

    for (;;) {
        aaa_1.a = seq;
        aaa_1.b = seq + 1;

        aaa_2.a = seq + 2;
        aaa_2.b = seq + 3;

        aaa_3.a = seq + 4;
        aaa_3.b = seq + 5; 

        aaa_pipe.write (aaa_1, false);
        aaa_pipe.write (aaa_2, false);
        aaa_pipe.write (aaa_3, false);

        aaa_pipe.flush ();
        ++seq;
        usleep (100);
    }
}

static void t2_fun ()
{
    AAA_t aaa;
    for (;;) {
        if (aaa_pipe.read (&aaa) == true) {
            std::cout << aaa.a << std::endl;
        }
    }
}

int
main ()
{
    auto t1 = std::thread (t1_fun);
    auto t2 = std::thread (t2_fun);

    t1.join ();
    t2.join ();
}
