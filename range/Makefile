#CPPFLAGS=-fmodules-ts -std=c++20 -g -Wall -Wextra
# -fmodules-ts 还有bug 
CPPFLAGS= -std=c++20 -g -Wall -Wextra
# calendar
BIN=r1 span v1 v2 v3
all: prebuild ${BIN}

prebuild:
	-@ln -s ../gcm.cache 2>/dev/null

clean:
	rm -f *.o ${BIN}
