module m02;
import <iostream>;
import <vector>;
import <algorithm>;
import <numeric>;

namespace m02
{
    int CCC::lag (std::vector<int>& v, int lag) 
    {
        if (lag == 0) {
            return 0;
        }

        /// 向右移
        if (lag > 0) {
            if (v.size () < (size_t)lag) {
                std::fill (v.begin (), v.end (), 0);
                return 0;
            }

            size_t j = 0;
            for (size_t i = (size_t) (lag - 1); i < v.size (); ++i, ++j) {
                v[j] = v[i];
            }

            for (size_t i = 0; i < size_t (lag); ++i) {
                v[v.size () - i] = 0;
            }
        } else {
            if (v.size () < (size_t)(-lag)) {
                std::fill (v.begin (), v.end (), 0);
                return 0;
            }

            for (size_t i = 1; i <= size_t (-lag); ++i) {
                v[v.size () - i] = v[-lag - i];
            }

            for (size_t i = 0; i < size_t (lag); ++i) {
                v[i] = 0;
            }
        }

        return 0;
    }
}
