CPPFLAGS=-fmodules-ts -std=c++20 -g -Wall -Wextra
#CPPFLAGS= -std=c++20 -g -Wall -Wextra

all: prebuild pc 

prebuild:
	-@ln -s ../../gcm.cache 2>/dev/null

pc: pc.cpp 
	g++ ${CPPFLAGS} -o $@ $^ 
    

clean:
	rm -f *.o pc
