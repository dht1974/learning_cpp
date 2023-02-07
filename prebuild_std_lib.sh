#!/bin/bash

# 使用c++20 modules前需要将c++标准库进行预编译

rm -rf gcm.cache/usr/include/c++/

# 这几个不能批量编译，目前原因未明, execution 编译有问题，可能是还有bug
# echo "================== building execution ================="; 
# g++ -fmodules-ts -std=c++20 -x c++-system-header execution 
echo "================== building regex ================="; 
g++ -fmodules-ts -std=c++20 -x c++-system-header regex
echo "================== building thread ================="; 
g++ -fmodules-ts -std=c++20 -x c++-system-header thread
echo "================== building random ================="; 
g++ -fmodules-ts -std=c++20 -x c++-system-header random 
echo "================== building future ================="; 
g++ -fmodules-ts -std=c++20 -x c++-system-header future
echo "================== building condition_variable ================="; 
g++ -fmodules-ts -std=c++20 -x c++-system-header condition_variable 
echo "================== building stop_token ================="; 
g++ -fmodules-ts -std=c++20 -x c++-system-header stop_token 

std_lib_headers="algorithm cstdio filesystem memory shared_mutex any climits cstdlib forward_list memory_resource source_location array clocale cstring fstream mutex span tuple atomic cmath ctgmath functional new spanstream typeindex codecvt ctime numbers sstream typeinfo barrier compare cuchar initializer_list numeric stack type_traits bit complex cwchar iomanip optional stacktrace unordered_map cwctype ios ostream unordered_set bitset concepts iosfwd stdexcept utility cassert iostream valarray ccomplex coroutine istream queue variant cctype csetjmp deque iterator streambuf vector cerrno csignal exception latch ranges string version cfenv cstdalign limits ratio string_view cfloat cstdarg expected list syncstream charconv cstdbool locale scoped_allocator system_error chrono cstddef map semaphore cinttypes cstdint set"

for x in ${std_lib_headers}; 
do 
    echo "================== building ${x} ================="; 
    g++ -fmodules-ts -std=c++20 -x c++-system-header ${x}; 
done
