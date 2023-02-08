#include <unistd.h>
#include <memory>
#include <iostream>

struct AAA_t {
    union {
        struct {
            uint32_t site_id:6 {};
            uint32_t area_id:8 {};
            uint32_t group_id:8 {};
            uint32_t node_id:10 {};
        };
        /// 由于是union，这个地方不能进行初始化，会覆盖前面的初始化内容，编译会报错
        uint32_t node_global_id ;
    };

    uint32_t aaa; 
};

int
main ()
{
    AAA_t aaa;
    aaa.site_id = 1;
    aaa.area_id = 5;
    aaa.group_id = 0;
    aaa.node_id = 1;

    std::cout << aaa.node_global_id << std::endl; 

    auto ptr = std::make_unique<AAA_t> ();
    /// auto ptr = new AAA_t;
    ptr->node_global_id = 5231235;
    std::cout << ptr->site_id << std::endl;
    std::cout << ptr->area_id << std::endl;
    std::cout << ptr->group_id << std::endl;
    std::cout << ptr->node_id << std::endl;
}
