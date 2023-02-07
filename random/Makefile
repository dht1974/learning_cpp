CPPFLAGS=-fmodules-ts -std=c++20 -g -Wall -Wextra
#CPPFLAGS= -std=c++20 -g -Wall -Wextra

all: prebuild lcg normal_distribution 

prebuild:
	-@ln -s ../gcm.cache 2>/dev/null

lcg: lcg.cpp 
	g++ ${CPPFLAGS} -o $@ $^ 
    
normal_distribution: normal_distribution.cpp 
	g++ ${CPPFLAGS} -o $@ $^ 

run:
	./normal_distribution 
	@sleep 1
	./normal_distribution.R

clean:
	rm -f *.o lcg normal_distribution
