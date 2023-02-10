#CPPFLAGS=-fmodules-ts -std=c++20 -g -Wall -Wextra
CPPFLAGS= -std=c++20 -g -Wall -Wextra

BIN = all_none_any_of erase numeric
all: prebuild ${BIN}

prebuild:
	-@ln -s ../gcm.cache 2>/dev/null

clean:
	rm -f *.o ${BIN}
