#CPPFLAGS=-fmodules-ts -std=c++20 -g -Wall -Wextra
CPPFLAGS= -std=c++20 -g -Wall -Wextra

all: prebuild fs

prebuild:
	-@ln -s ../gcm.cache 2>/dev/null

fs: fs.cpp
	g++ ${CPPFLAGS} -o $@ $^

clean:
	rm -f fs
