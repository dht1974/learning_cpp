CPPFLAGS=-fmodules-ts -std=c++20 -g -Wall -Wextra

BIN=unique_ptr # shared_ptr
all: prebuild 

prebuild:
	-@ln -s ../../gcm.cache 2>/dev/null

clean:
	rm -f ${BIN}
