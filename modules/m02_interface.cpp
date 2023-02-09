export module m02;

import <string_view>;
import <iostream>;
import <vector>;

/// 整个命名空间export
/// export namespace m02 
namespace m02 
{
    export void say_hello (const std::string_view& name)
    {
        std::cout << "Hello, " << name << '!' << std::endl;
    }

    export class AAA
    {
    public:
        void foo ()
        {
            std::cout << "AAA::foo" << std::endl;
        }

        int add (std::vector<int>& v);

    private:
        void bar ()
        {
            std::cout << "AAA::bar" << std::endl;
        }
    };

    export class BBB
    {
    public:
        ~BBB ()
        {}
        
        /// 目前看多态支持还是有问题，在链接时报错
        /// virtual int lag (std::vector<int>& v, int lag) = 0;
        int lag (std::vector<int>& v, int lag);
    };

    export class CCC : public BBB
    {
    public:
        int lag (std::vector<int>& v, int lag);
    };
}
