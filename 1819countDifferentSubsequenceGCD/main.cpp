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
    
    int gcd(int a, int b) {
        int modeRes = b;
        do {
            modeRes = a % b;
            a = b;
            b = modeRes;
        } while(modeRes != 0); 
        return a; 
    }

    int countDifferentSubsequenceGCDs(vector<int>& nums) {
        int maxNum = *max_element(nums.begin(), nums.end());
        int n = nums.size();
        int ans = 0;
        // set速度可能不够快，使用普通的数组
        // unordered_set<int> set;
        // for(int i = 0; i < n; ++i) {
        //     if(set.count(nums[i]) == 0) {
        //         set.insert(nums[i]);
        //     }
        // }

        // array<bool, 200001> exist;
        vector<bool> exist(200005, false);
        // bool exist[200001];
        for(int i = 0; i < n; ++i) {
            exist[nums[i]] = true;
        }
        
        // 判断每一个可能的公因数 greatest common divisor
        for(int i = 1; i <= maxNum; ++i) {
            // 判断i是否为某个子序列的最大公因数:
            // 则需要判断所有含有i作为因数的位于nums中的数字组成的子序列的最大公因数是否为i
            // 比如当i = 3，而数组为 6 12，则3不是，因为不是最大公因数
            int curGCD = -1; 
            for(int j = i; j <= maxNum; j += i) {
                // j 为 k*i，若其出现在nums中的某个子序列，则对这个子序列两两求gcd
                if(exist[j]) {
                    if(curGCD == -1) {
                        curGCD = j;
                    } else {
                        curGCD = gcd(curGCD, j);
                    }
                }
            }
            if(curGCD == i) {
                ++ans;
            }
        }

        return ans;
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