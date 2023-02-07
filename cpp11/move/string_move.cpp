#include <string>
#include <vector>
#include <iostream>
#include <stdio.h>

/// 还没有完成

/// 此程序用作单步调试使用，观察c++标准库如何处理move操作，加深对move的理解

int
main ()
{
    /// std::string s {"abc"};   /// 参考下面代码，字符串长度太短，会使用string类里的
    /// local buf，只有大的字符串才会在堆内分配
/*    
 213   template<typename _CharT, typename _Traits, typename _Alloc>
 214     template<typename _InIterator>
 215       _GLIBCXX20_CONSTEXPR
 216       void
 217       basic_string<_CharT, _Traits, _Alloc>::
 218       _M_construct(_InIterator __beg, _InIterator __end,
 219            std::forward_iterator_tag)
 220       {
 221     size_type __dnew = static_cast<size_type>(std::distance(__beg, __end));
 222 
 223     if (__dnew > size_type(_S_local_capacity))
 224       {
 225         _M_data(_M_create(__dnew, size_type(0)));
 226         _M_capacity(__dnew);
 227       }
 228     else
 229       _M_use_local_data();


 _S_local_capacity 长度目前是15, 229行是使用类中的local_buf

 213       enum { _S_local_capacity = 15 / sizeof(_CharT) };
 214
 215       union
 216       {
 217     _CharT           _M_local_buf[_S_local_capacity + 1];
 218     size_type        _M_allocated_capacity;
 219       };

*/

    /// 字符串必须很长，才会在堆中分配内存，否则在栈中分配
    std::string s {"abc111111111111111111111111111111111111111111111111111111111111111111"};
    /// gdb 可以看到s使用malloc在堆中分配内存

    std::vector<std::string> v;
    v.reserve (2);
#if 0
    /// 传统的拷贝方式
    v.push_back (s);
/*                  
        stack mem           |      heap mem
                            |
    std::string             |
    +--------------------+  |  +------------------+
    | s._M_dataplus._M_p | --> | abc111...1111111 | 
    +--------------------+  |  +------------------+     
                            |                           
    push_back 后，vector中有一个新创建出来的string      
                            |                           
                            |   vector中的std::string                           
            +------------+     +--------------------+     +------------------+
            | v._M_start | --> | s._M_dataplus._M_p | --> | abc111...1111111 |
            +------------+     +--------------------+     +------------------+
                            |
                            |
*/

#else
    /// move方式
    v.push_back (std::move (s));

/*                  
        stack mem           |      heap mem
                            |
    std::string             |
    +--------------------+  |  +------------------+
    | s._M_dataplus._M_p | XXX>| abc111...1111111 | <---o
    +--------------------+  |  +------------------+     |
                            |                           |
    push_back 后，vector中有一个新创建出来的string      |
                            |                           |
                            |   vector中的std::string   | 
            +------------+     +--------------------+   |
            | v._M_start | --> | s._M_dataplus._M_p | --o 
            +------------+     +--------------------+    
                            |
                            |


basic_string move构造函数被调用，调用栈

#0  std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> >::basic_string (
    this=0x41a300, __str=...) at /usr/include/c++/12/bits/basic_string.h:671
#1  0x00000000004039dc in std::construct_at<std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> >, std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> > > (
    __location=0x41a300) at /usr/include/c++/12/bits/stl_construct.h:97
#2  0x000000000040356b in std::allocator_traits<std::allocator<std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> > > >::construct<std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> >, std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> > > (__a=...,
    __p=0x41a300) at /usr/include/c++/12/bits/alloc_traits.h:518
#3  0x00000000004032e6 in std::vector<std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> >, std::allocator<std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> > > >::emplace_back<std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> > > (this=0x7fffffffd6f0)
    at /usr/include/c++/12/bits/vector.tcc:117
#4  0x0000000000403180 in std::vector<std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> >, std::allocator<std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> > > >::push_back (this=0x7fffffffd6f0, __x=...) at /usr/include/c++/12/bits/stl_vector.h:1294
#5  0x0000000000402493 in main () at string_move.cpp:76

 670       basic_string(basic_string&& __str) noexcept
 671       : _M_dataplus(_M_local_data(), std::move(__str._M_get_allocator()))
 672       {
 673     if (__str._M_is_local())
 674       {
 675         traits_type::copy(_M_local_buf, __str._M_local_buf,
 676                   __str.length() + 1);
 677       }
 678     else
 679       {
 680         _M_data(__str._M_data());
 681         _M_capacity(__str._M_allocated_capacity);
 682       }
 683 
 684     // Must use _M_length() here not _M_set_length() because
 685     // basic_stringbuf relies on writing into unallocated capacity so
 686     // we mess up the contents if we put a '\0' in the string.
 687     _M_length(__str.length());
 688     __str._M_data(__str._M_local_data());
 689     __str._M_set_length(0);
 690       }


*/

    /// move 以后，再次使用s，这是错误的。此时s的指针已经被设置为nullptr
    /// std::cout << s << std::endl;
    printf ("%s\n", s.c_str ());
#endif
}
