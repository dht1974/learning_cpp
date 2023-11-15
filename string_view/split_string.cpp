#include <string>
#include <string_view>
#include <vector>

#include <iostream>

int my_atoi (const char *nptr, size_t n)
{
    char *p = const_cast<char*> (nptr);
    char c = *(p + n);
    *(p + n) = '\0';
    int ret = atoi (p);
    *(p + n) = c;

    return ret;
}

void split_to_vector (std::string_view& line, std::vector<std::string_view>& vec)
{
    vec.clear ();
    std::string_view::size_type pos = 0, last_pos = 0;

    while ((pos = line.find_first_of (',', last_pos)) != std::string_view::npos) {
        vec.push_back (line.substr (last_pos, pos - last_pos));
        last_pos = pos + 1;
    }

    vec.push_back (line.substr (last_pos));
}

int
main ()
{
    std::string str ("20200721,688396,09:31:41.000,48.11,48.3,48.3,48.03,0.0,544879,2.627562205E7,48.27,4806,48.28,1000,48.29,21012,48.3,30249,48.36,500,48.22,1210,48.15,499,48.13,621,48.11,5161,48.1,13312,85678,4131616.21,180,222,44657,2154941.31,91,129,34041,1642203.79,74,100,20186,974028.34,37,57,101182,4882077.75,47,91,97963,4725811.37,45,97,51436,2481039.11,24,47,35576,1715282.22,16,44,145868,7036662.370000001,19,68,183630,8856716.25,20,148,87367,4214724.07,12,52,126631,6107230.59,12,97,30000,1449000.0,1,10,36478,1761887.3999999997,1,17,0,0.0,0,0,0,0.0,0,0,362728.0,1.749935633E7,391,48.11");

    std::vector<std::string_view> vec;
    vec.reserve (64);

    /// std::string_view sv (str.c_str (), str.size ());
    std::string_view sv (str, str.size ());
    split_to_vector (sv, vec);

    for (size_t i = 0; i < vec.size (); ++i) {
        std::cout << vec[i] << std::endl;

        if (i == 0) {
            printf ("%d\n", my_atoi (vec[i].data (), vec[i].size ()));
            printf ("%s\n", vec[i].data ());
        }
    }
}
