# CPP=clang++
CPP=g++
CPPFLAGS=-fmodules-ts -std=c++20 -g -Wall -Wextra

all: prebuild m02

prebuild:
	-@ln -s ../gcm.cache 2>/dev/null

m02: m02_interface.cpp m02_impl_aaa.cpp m02_impl_ccc.cpp m02.cpp
	${CPP} ${CPPFLAGS} -c m02_interface.cpp
	${CPP} ${CPPFLAGS} -c m02_impl_aaa.cpp
	${CPP} ${CPPFLAGS} -c m02_impl_ccc.cpp
	${CPP} ${CPPFLAGS} -o m02 m02.cpp m02_interface.o m02_impl_aaa.o m02_impl_ccc.o
    

clean:
	rm -f *.o gcm.cache/*.gcm 01 m02
