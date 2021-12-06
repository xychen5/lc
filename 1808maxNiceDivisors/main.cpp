// ConsoleApplication1.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <limits.h>
#include <numeric>
#include <list>
#include <queue>
#include <unordered_set>
#include <unordered_map>
#include <map>
#include <set>

using namespace std;
class Solution {
public:
    static constexpr long long lPrime = 1000000007;
    int maxNiceDivisors(int primeFactors) {
        int res = 0;
        int numsOfThree = primeFactors / 3;
        if(primeFactors <= 3) {
            return primeFactors;
        } else if(primeFactors % 3 == 0) {
            return fastPow(3, numsOfThree) % lPrime;
        } else if(primeFactors % 3 == 1) {
            // eg: primeFactors = 7: then 3 * 3 * 1 < 3 * 2 * 2
            return fastPow(3, numsOfThree - 1) * 4 % lPrime;
        } else if(primeFactors % 3 == 2) {
            return fastPow(3, numsOfThree) * 2 % lPrime;
        } 
        return -1;
    }

    // p ^ q
    // cause the final result will mod 10**9 + 7, because: (axb)%c == (a%c)x(b%c)%c
    // u can do it here any times u like, besides to avoid long long overflow
    long long fastPow(long long p, long long q) {
        long long res = 1;
        while(q > 0) {
            if(1 & q) {
                res = (res % lPrime) * (p % lPrime);
            }
            p = (p * p ) % lPrime;
            q >>= 1;
        }
        return res;
    }
}

int main()
{
    // vector<int> nums = {1, 15, 5, 11};
    // vector<int> nums = {1, 3};
    // vector<int> nums = {1, 3};
    int n = 2;
    vector<int> nums1d = { 1, 0 };
    vector<vector<int>> nums2d1 = { {1}, {0} };
    vector<vector<int>> nums2d4 = { {1,1,3,3},{3,1,4,2},{3,2,4,4},{1,3,2,4},{2,3,3,4} };
    Solution sl;
    // std::cout << sl.medianSlidingWindow(nums1d, 3) << std::endl;

    // std::cout << ios::left << std::setw(20) << "Hello, World!" << std::setw(5) << "a s " << 1 << std::endl;
    return 0;
    std::cout << "Hello World!\n";
}