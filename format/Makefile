CXX=g++-13
CPPFLAGS=-fmodules-ts -std=c++23 -g -Wall -Wextra
# -fmodules-ts 还有bug 
#CPPFLAGS= -std=c++20 -g -Wall -Wextra

BIN=format
all: prebuild ${BIN}

prebuild:
	-@ln -s ../gcm.cache 2>/dev/null

clean:
	rm -f *.o ${BIN}
