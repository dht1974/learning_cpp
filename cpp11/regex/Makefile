CPPFLAGS=-fmodules-ts -std=c++20 -g -Wall -Wextra

BIN=regex regex2
all: prebuild 

prebuild:
	-@ln -s ../../gcm.cache 2>/dev/null

clean:
	rm -f ${BIN}
