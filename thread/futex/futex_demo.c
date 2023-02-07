/* futex_demo.c

Usage: futex_demo [nloops]
(Default: 5)

Demonstrate the use of futexes in a program where parent and child
use a pair of futexes located inside a shared anonymous mapping to
synchronize access to a shared resource: the terminal. The two
processes each write 'num-loops' messages to the terminal and employ
a synchronization protocol that ensures that they alternate in
writing messages.
 */

/// 这个例子是 man 2 futex 提供的

#define _GNU_SOURCE
#include <err.h>
#include <errno.h>
#include <linux/futex.h>
#include <stdatomic.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/syscall.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <unistd.h>

static uint32_t *futex1, *futex2, *iaddr;

static int
futex(uint32_t *uaddr, int futex_op, uint32_t val,
        const struct timespec *timeout, uint32_t *uaddr2, uint32_t val3)
{
    return syscall(SYS_futex, uaddr, futex_op, val,
            timeout, uaddr2, val3);
}

/* Acquire the futex pointed to by 'futexp': wait for its value to
   become 1, and then set the value to 0. */

static void
fwait(uint32_t *futexp)
{
    long            s;
    const uint32_t  one = 1;

    /* atomic_compare_exchange_strong(ptr, oldval, newval)
       atomically performs the equivalent of:

       if (*ptr == *oldval)
     *ptr = newval;

     It returns true if the test yielded true and *ptr was updated. */

    while (1) {

        /* Is the futex available? */
        if (atomic_compare_exchange_strong(futexp, &one, 0))
            break;      /* Yes */

        /* Futex is not available; wait. */

        s = futex(futexp, FUTEX_WAIT, 0, NULL, NULL, 0);
        if (s == -1 && errno != EAGAIN)
            err(EXIT_FAILURE, "futex-FUTEX_WAIT");
    }
}

/* Release the futex pointed to by 'futexp': if the futex currently
   has the value 0, set its value to 1 and then wake any futex waiters,
   so that if the peer is blocked in fwait(), it can proceed. */

static void
fpost(uint32_t *futexp)
{
    long            s;
    const uint32_t  zero = 0;

    /* atomic_compare_exchange_strong() was described
       in comments above. */

    if (atomic_compare_exchange_strong(futexp, &zero, 1)) {
        s = futex(futexp, FUTEX_WAKE, 1, NULL, NULL, 0);
        if (s  == -1)
            err(EXIT_FAILURE, "futex-FUTEX_WAKE");
    }
}

int
main(int argc, char *argv[])
{
    pid_t         childPid;
    unsigned int  nloops;

    setbuf(stdout, NULL);

    nloops = (argc > 1) ? atoi(argv[1]) : 5;

    /* Create a shared anonymous mapping that will hold the futexes.
       Since the futexes are being shared between processes, we
       subsequently use the "shared" futex operations (i.e., not the
       ones suffixed "_PRIVATE"). */

    iaddr = mmap(NULL, sizeof(*iaddr) * 2, PROT_READ | PROT_WRITE,
            MAP_ANONYMOUS | MAP_SHARED, -1, 0);
    if (iaddr == MAP_FAILED)
        err(EXIT_FAILURE, "mmap");
    futex1 = &iaddr[0];
    futex2 = &iaddr[1];

    *futex1 = 0;        /* State: unavailable */
    *futex2 = 1;        /* State: available */

    /* Create a child process that inherits the shared anonymous
       mapping. */

    childPid = fork();
    if (childPid == -1)
        err(EXIT_FAILURE, "fork");

    if (childPid == 0) {        /* Child */
        for (unsigned int j = 0; j < nloops; j++) {
            fwait(futex1);
            printf("Child  (%jd) %u\n", (intmax_t) getpid(), j);
            fpost(futex2);
        }

        exit(EXIT_SUCCESS);
    }

    /* Parent falls through to here. */

    for (unsigned int j = 0; j < nloops; j++) {
        fwait(futex2);
        printf("Parent (%jd) %u\n", (intmax_t) getpid(), j);
        fpost(futex1);
    }

    wait(NULL);

    exit(EXIT_SUCCESS);
}

