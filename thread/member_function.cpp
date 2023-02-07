#include <thread>
#include <iostream>
#include <chrono>
/// 使用类成员函数作为线程运行函数

typedef struct {
	int a;
} data_t;

class AAA
{
public:
	void thread_fun (data_t& data)
	{
		std::cout << "sleep " << data.a << " secs" << std::endl;
		std::this_thread::sleep_for (std::chrono::milliseconds (data.a * 1000));
	}
};

int
main ()
{
	data_t data;
	data.a = 3;

	AAA aaa;
	/// 给成员函数传递参数，需要使用std::ref
	std::thread *t_ptr = new std::thread (&AAA::thread_fun, &aaa, std::ref (data));

	if (t_ptr->joinable () == true) {
		t_ptr->join ();
		std::cout << "join ok\n";
	}
}
