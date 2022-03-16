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
    bool canCross(vector<int>& stones) {
        int n = stones.size();
        // jump to i, and last jump dis
        vector<vector<bool>> jump(n , vector<bool>(n, false));
        jump[0][0] = true;

        // the i th jump len <= i
        for(int i = 1; i < n; ++i) {
            if(stones[i] - stones[i - 1] > i) {
                return false;
            }
        }

        // dp, from j jump to i
        bool res = false;
        for(int i = 1; i < n; ++i) {
            for(int j = 0; j < i; ++j) {
                int k = stones[i] - stones[j];
                // cout << j << " -> " << i << " 's dis: " << k << endl;
                if(k > j + 1) {
                    continue;
                }
                // cout << jump[j].size() << " / " << k + 1 << " jump[j][k] || jump[j][k-1] || jump[j][k+1] " << jump[j][k] << jump[j][k-1] << jump[j][k+1] << endl;
                jump[i][k] = jump[j][k] || jump[j][k-1] || jump[j][k+1];
                if(i == n - 1 && jump[i][k]) {
                    res = true;
                }
            }
        }
        return res;
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