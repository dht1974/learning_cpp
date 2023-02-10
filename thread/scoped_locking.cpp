#include <iostream>

/// std::scoped_lock可以对多个不同类型的mutex进行Scoped Locking (c++17)
/*
<mutex>
 739   template<typename... _MutexTypes>
 740     class scoped_lock
 741     {
 742     public:
 743       explicit scoped_lock(_MutexTypes&... __m) : _M_devices(std::tie(__m...))
 744       { std::lock(__m...); }
 745
 746       explicit scoped_lock(adopt_lock_t, _MutexTypes&... __m) noexcept
 747       : _M_devices(std::tie(__m...))
 748       { } // calling thread owns mutex
 749
 750       ~scoped_lock()
 751       { std::apply([](auto&... __m) { (__m.unlock(), ...); }, _M_devices); }
 752
 753       scoped_lock(const scoped_lock&) = delete;
 754       scoped_lock& operator=(const scoped_lock&) = delete;
 755
 756     private:
 757       tuple<_MutexTypes&...> _M_devices;
 758     };
*/
