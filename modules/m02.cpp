import m02;
import <vector>;
import <iostream>;

int
main ()
{
    m02::AAA aaa;

    aaa.foo ();
    std::vector<int> v;

    for (int i = 1; i <= 10; ++i) {
        v.push_back (i);
    }

    int sum = aaa.add (v);
    std::cout << "sum: " << sum << std::endl;

    m02::say_hello ("ggg");

    m02::CCC ccc;

    ccc.lag (v, 2);
    for (auto iter = v.begin (); iter != v.end (); ++iter) {
        std::cout << *iter << std::endl;
    }
}
