#include <algorithm>
#include <vector>
#include <iostream>

int
main ()
{
    std::vector v {1, 2, 3, 4, 5, 6, 7, 8, 9, 5, 6, 7, 8}; 

    std::cout << "---------- allof test ----------" << '\n';
    auto f_all_of = [](int a) -> bool { if (a > 0) { return true; } return false;};
    if (std::all_of (v.begin (), v.end (), f_all_of) == true) {
        std::cout << "allof > 0 ok\n";
    }

    std::cout << "---------- noneof test ----------" << '\n';
    auto f_none_of = [](int a) -> bool { if (a > 10) { return true; } return false;};
    if (std::none_of (v.begin (), v.end (), f_none_of) == true) {
        std::cout << "noneof > 10 ok\n";
    }

    std::cout << "---------- anyof test ----------" << '\n';
    auto f_any_of = [](int a) -> bool { if (a > 2) { return true; } return false;};
    if (std::any_of (v.begin (), v.end (), f_any_of) == true) {
        std::cout << "anyof > 10 ok\n";
    }

    std::cout << "---------- find_end test ----------" << '\n';
    /// 从一个大集合中搜索最后一个子集
    std::vector v_needle {5, 6, 7};
    auto iter_end = std::find_end (v.begin (), v.end (), v_needle.begin (), v_needle.end ());
    if (iter_end == v.end ()) {
        std::cout << "find_end err.\n";
    } else {
        std::cout << "find_end ok. distance: " << std::distance (v.begin (), iter_end) << std::endl;
    }

    std::cout << "---------- copy_if test ----------" << '\n';
    auto f_copy = [] (int a) -> bool {if (a > 5) {return true;} else {return false;}};
    std::vector<int> copy_v;
    std::copy_if (v.begin (), v.end (), std::back_inserter (copy_v), f_copy);

    for (auto& i : copy_v) {
        std::cout << i << '\n';
    }

    std::cout << "---------- copy_n test ----------" << '\n';
    copy_v.clear ();
    std::copy_n (v.begin (), 3, std::back_inserter (copy_v));
    for (auto& i : copy_v) {
        std::cout << i << '\n';
    }
    
    std::cout << "---------- partition_copy test ----------" << '\n';
    std::vector<int> out_true;
    std::vector<int> out_false;
    auto f_partition_copy = [](int a) -> bool {if (a > 5) {return true;} return false;};
    partition_copy (v.begin (), v.end (), std::back_inserter (out_true), 
        std::back_inserter (out_false), f_partition_copy);
    std::cout << "partition true: ";
    for (auto& i : out_true) {
        std::cout << i << ',';
    }
    std::cout << '\n';

    std::cout << "partition false: ";
    for (auto& i : out_false) {
        std::cout << i << ',';
    }
    std::cout << '\n';

    std::cout << "---------- fill_n test ----------" << '\n';
    std::vector<int> v_fill;
    v_fill.resize (10);
    std::fill_n (v_fill.begin (), 10, 5);
    for (auto& i : v_fill) {
        std::cout << i << ',';
    }
    std::cout << '\n';


    return 0;
}
