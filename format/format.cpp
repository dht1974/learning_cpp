#include <format>
#include <string>
#include <vector>
#include <iostream>
#include <type_traits>
/// 注意：format在g++13支持，参考一下Makefile

int
main ()
{
	/// f的类型是std::string
	auto f = std::format ("hello {}", "world"); 
	decltype (f) s {"str"};
	std::cout << s << std::endl;
	static_assert (std::is_same_v<decltype (f), std::string>, "not a std::string");
	std::cout << f << std::endl;

	int a = 1;
	double b = 2.0;
	std::string c {"str3.0"};
	std::cout << std::format ("{}, {}, {}", a, b, c) << std::endl;

	/// 不同的输出顺序
	std::cout << std::format ("{2}, {1}, {0}", a, b, c) << std::endl;
	std::cout << std::format ("{1}, {2}, {0}", a, b, c) << std::endl;

	/// 解决浮点数精度丢失问题，其实也被截断了，比printf精度高点
	std::cout << std::format ("pi = {}\n", std::numbers::pi);
	printf ("printf pi = %f\n", std::numbers::pi);

	/// TODO，后面没清空
	char buf[32];
	std::format_to_n (buf, std::size (buf), "{}", std::numbers::pi); 
	std::cout << buf << std::endl; 

	/// 进制
	std::cout << std::format ("{:x}", 100) << std::endl;
	std::cout << std::format ("{:o}", 100) << std::endl;
	std::cout << std::format ("{:b}", 100) << std::endl;
}
