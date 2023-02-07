#include <random>
#include <iostream>
#include <fstream>
/// 正态分布

int
main ()
{
    std::linear_congruential_engine<size_t, 5, 8, 113372133> lce (3);

    /// 标准正态分布
    double mean = 0;        /// 均值
    double stddev = 1;      /// 标准差

    std::normal_distribution<double> nd (mean, stddev);

    /// std::cout << "mean: " << nd.mean () << std::endl;
    /// std::cout << "stddev: " << nd.mean () << std::endl;

    double one_sigma = 1;
    double two_sigma = 2;
    double three_sigma = 3;
    double four_sigma = 4;

    size_t one_sigma_count = 0;
    size_t two_sigma_count = 0;
    size_t three_sigma_count = 0;
    size_t four_sigma_count = 0;

    std::ofstream of_nd ("nd.csv");
    std::ofstream of_sigma ("sigma.csv");

    size_t count = 1000000;
    of_nd << "seq,val" << std::endl;
    for (size_t i = 0; i < count; ++i) {
        double val = nd (lce);
        if (fabs (val) <= one_sigma) {
            ++one_sigma_count;
        } else if (fabs (val) <= two_sigma) {
            ++two_sigma_count;
        } else if (fabs (val) <= three_sigma) {
            ++three_sigma_count;
        } else if (fabs (val) <= four_sigma) {
            ++four_sigma_count;
        }
        /// of_nd << i << ',' << val << '\n';
        of_nd << i << ',' << val << std::endl;
    }

    double one_sigma_o = double (one_sigma_count) * 100 / count;
    double two_sigma_o = double (two_sigma_count) * 100 / count;
    double three_sigma_o = double (three_sigma_count) * 100 / count;
    double four_sigma_o = double (four_sigma_count) * 100 / count;

    of_sigma << "nsigma,val" << std::endl;
    of_sigma << "1," << one_sigma_o << std::endl;
    of_sigma << "2," << one_sigma_o + two_sigma_o << std::endl;
    of_sigma << "3," << one_sigma_o + two_sigma_o + three_sigma_o << std::endl;
    of_sigma << "4," << one_sigma_o + two_sigma_o + three_sigma_o + four_sigma_o << std::endl;
    
#if 0
    std::cout << "1 sigma: " << one_sigma_o << "%" << std::endl;
    std::cout << "2 sigma: " << one_sigma_o + two_sigma_o << "%" << std::endl;
    std::cout << "3 sigma: " << one_sigma_o + two_sigma_o + three_sigma_o << "%" << std::endl;
    std::cout << "4 sigma: " << one_sigma_o + two_sigma_o + three_sigma_o + four_sigma_o << "%" << std::endl;
#endif
}
