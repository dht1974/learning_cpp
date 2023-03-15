#CPPFLAGS=-fmodules-ts -std=c++20 -g -Wall -Wextra
CPPFLAGS=-std=c++20 -g -Wall -Wextra

BIN = ypipe_test
all: prebuild ${BIN}

prebuild:
	-@ln -s ../gcm.cache 2>/dev/null

clean:
	rm -f ${BIN}
