#include <iostream>
#include <vector>

std::vector<int> ints {775,782,784,920,777,767,776,856,768};
std::vector<int> ints2 {784,209,920,773,210,774,864,677,221,676,678,494,766,303,507,286,642,627,626,196,625,735,737,413,137,20,799,134,181,787,182,497,327,328,331,714,332,119,501,452,453,118,903,119,726,725,8,911,750};
std::vector<int> ints3 {262,869,427,824,428,683,647,684,406,916,917,648};
int main()
{
    for(auto it = ints3.begin(); it != ints3.end(); ++it)
    {
        std::cout << 
            3 * *it + 2 << ',';
    }
}