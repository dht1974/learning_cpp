CPPFLAGS=-fmodules-ts -std=c++20 -g -Wall -Wextra

BIN= move string_move noexcept_move const_move const_lvalue
all: prebuild ${BIN}

prebuild:
	-@ln -s ../../gcm.cache 2>/dev/null

clean:
	rm -f ${BIN}
