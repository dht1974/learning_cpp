#CPPFLAGS=-fmodules-ts -std=c++20 -g -Wall -Wextra
CPPFLAGS= -g -Wall -Wextra -lrt

all: futex_demo

futex_demo: futex_demo.c
	gcc ${CPPFLAGS} -o $@ $^ -O0

clean:
	rm -f futex_demo
