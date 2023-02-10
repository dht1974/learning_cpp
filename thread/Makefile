#CPPFLAGS=-fmodules-ts -std=c++20 -g -Wall -Wextra
CPPFLAGS=-std=c++20 -g -Wall -Wextra

BIN = member_function mutex atomic atomic_flag latch barrier condition_variable future interfence atomic_ref promise semaphore shared_mutex thread_local scoped_locking async
all: prebuild ${BIN}

prebuild:
	-@ln -s ../gcm.cache 2>/dev/null

clean:
	rm -f ${BIN}
