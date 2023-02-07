module m02;
import <iostream>;
import <vector>;
import <algorithm>;
import <numeric>;

namespace m02
{
int AAA::add (std::vector<int>& v) 
{
    int sum = 0;

    sum = std::accumulate (v.begin (), v.end (), sum);

    return sum;
}
}
