CPPFLAGS=-fmodules-ts -std=c++20 -g -Wall -Wextra

# -fno-elide-constructors 禁止nrvo和rvo
NONVRO_CPPFLAGS= -std=c++20 -g -Wall -Wextra -fno-elide-constructors

# c++17强制进行rvo，即使使用了-fno-elide-constructors也不行，因此使用14编译
CPPFLAGS_14= -std=c++14 -g -Wall -Wextra -fno-elide-constructors

all: prebuild nrvo nonrvo nonrvo_14

prebuild:
	-@ln -s ../../gcm.cache 2>/dev/null

nrvo: nrvo.cpp
	g++ ${CPPFLAGS} -o $@ $^

nonrvo: nrvo.cpp
	g++ ${NONVRO_CPPFLAGS} -o $@ $^

nonrvo_14: nrvo.cpp
	g++ ${CPPFLAGS_14} -o $@ $^

clean:
	rm -f nrvo nonvro nonrvo_14
