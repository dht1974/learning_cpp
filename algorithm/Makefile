CPPFLAGS=-fmodules-ts -std=c++20 -g -Wall -Wextra
#CPPFLAGS= -std=c++20 -g -Wall -Wextra

all: prebuild all_none_any_of erase

prebuild:
	-@ln -s ../gcm.cache 2>/dev/null

all_none_any_of: all_none_any_of.cpp 
	g++ ${CPPFLAGS} -o $@ $^ 
    
clean:
	rm -f *.o all_none_any_of 
