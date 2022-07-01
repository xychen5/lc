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
#include <string>

using namespace std;

class Solution {
public:

    int largestPalindrome(int n) {
        if(n == 1) {
            return 9;
        }
        // reverse thinking
        // traverse all Palindrome from big to small, if this num can be acuired through 2 nbit num's mul
        // return
        set<long long, std::greater<long long>> res;
        long long max = pow(10, n);
        for(long long tar = max - 1; tar >= max / 10; --tar) {
            string pali1 = to_string(tar);
            int oriLen = pali1.length();
            for(int i = pali1.length() - 1; i >= 0; --i) {
                pali1.push_back(pali1[i]);
            }
            // cout << pali1 << " " << pali2 << endl;

            long long revNum = stol(pali1);

            // check factor, cause a * b == revNum, then we travel the big one such as a, then when a * a < revNum
            // there will be no answer
            for(long long factor = max; factor * factor > revNum; --factor) {
                if(revNum % factor == 0) {
                    return revNum % 1337;
                }
            }

        }
        
        return -1;

    }
};


int main()
{
    // vector<int> nums = {1, 15, 5, 11};
    // vector<int> nums = {1, 3};
    // vector<int> nums = {1, 3};
    int n = 2;
    vector<int> nums1d = { 1, 0 };
    vector<vector<int>> nums2d1 = { {1}, {0} };
    vector<vector<int>> nums2d4 = { {1,1,3,3},{3,1,4,2},{3,2,4,4},{1,3,2,4},{2,3,3,4} };
    // Solution sl;
    // std::cout << sl.medianSlidingWindow(nums1d, 3) << std::endl;

    // std::cout << ios::left << std::setw(20) << "Hello, World!" << std::setw(5) << "a s " << 1 << std::endl;
    return 0;
    std::cout << "Hello World!\n";
}