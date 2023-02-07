CPPFLAGS=-fmodules-ts -std=c++20 -g -Wall -Wextra

all: prebuild err_concept concept

prebuild:
	-@ln -s ../gcm.cache 2>/dev/null

err_concept: err_concept.cpp
	g++ ${CPPFLAGS} -o $@ $^

clean:
	rm -f err_concept 
