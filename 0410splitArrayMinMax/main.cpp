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
    int maxEnvelopes(vector<vector<int>>& envelopes) {
        int n = envelopes.size();
        if(n == 1) {
            return 1;
        }
        int len = 1;
        
        // by x, already increasing
        sort(envelopes.begin(), envelopes.end(), [&](vector<int>& a, vector<int>& b) {
            if(a[0] < b[0]) {
                return true;
            } else if(a[0] == b[0]) { // then, with same x, can only get one y, this is the core
                return a[1] > b[1];
            } else {
                return false;
            }
        });

        // only care about the y
        vector<int> minBitLIS = { envelopes[0][1] };
        for(int i = 1; i < n; ++i) {
            if(envelopes[i][1] > minBitLIS.back()) {
                ++len;
                minBitLIS.push_back(envelopes[i][1]);
            } else {
                *lower_bound(minBitLIS.begin(), minBitLIS.end(), envelopes[i][1]) = envelopes[i][1];
            }

        }
        return len;
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