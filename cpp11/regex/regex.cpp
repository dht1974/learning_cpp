#include <vector>
#include <iostream>
#include <utility>
#include <regex>
#include <string>

typedef struct {
	uint64_t total {0};
	uint64_t free {0};
	uint64_t used {0};
	uint64_t buffered {0};
} top_mem_stat_t;

int
main ()
{
	top_mem_stat_t stat;
	/// 从下面这个字符串中提取有用的信息
	std::string str {"MiB Mem : 64029.29+total, 61226.17+free, 2407.867 used, 1423.922 buff/cache"};

	/// perl 正则表达式，应该和posix差别不大
	/// 使用c++调试正则表达式比较困难，可以先在perl中进行调试，然后拷贝过来使用，注意要用 R"()"包裹起来，否则有编译警告
	std::regex reg (R"((.+)\s+Mem\s+:\s+(\d+\.\d+)\+*total,\s+(\d+\.\d+)\+*free,\s+(\d+\.\d+)\+*\s*used,\s+(\d+\.\d+)\+*\s*buff)");
#if 0
	/// 是否匹配
	if (std::regex_search(str, reg) == false) {
        std::cout << "Text dosen't contains the phrase 'regular expressions'\n";
		return -1;
    } 
#endif

	std::smatch sub_match;
	if (std::regex_match (str, sub_match, reg) == false) {
        std::cout << "regex_match err.'\n";
		return -1;
	}

	auto words_begin = std::sregex_iterator (str.begin(), str.end(), reg);
    auto words_end = std::sregex_iterator ();

	for (auto w = words_begin; w != words_end; ++w) {
		std::cout << (*w).str () << std::endl;
	}

    return 0;
}
