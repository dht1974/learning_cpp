CPPFLAGS= -std=c++20 -g -Wall -Wextra

BIN = piecewise_construct m1
all: prebuild ${BIN}

prebuild:
	-@ln -s ../../gcm.cache 2>/dev/null

clean:
	rm -f ${BIN}
