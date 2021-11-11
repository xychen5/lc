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
using namespace std;
class Solution {
public:
    int subarraysWithKDistinct(vector<int>& nums, int k) {
        return maxSubArrayNumForKDiff(nums, k) - maxSubArrayNumForKDiff(nums, k - 1);

    }

    int maxSubArrayNumForKDiff(vector<int>& nums, int k) {
        vector<int> freq(nums.size() + 1);
        long long res = 0;
        int st = 0;
        int ed = 0;
        int curCnt = 0;
        while(ed < nums.size()) {
            // 求每个ed对应得到的最多k个不同元素的子数组个数
            if(freq[nums[ed]] == 0) {
                curCnt ++;
            }
            freq[nums[ed]]++;
            ++ed;

            // 减小窗口到窗口内元素种类第一次为k-1个
            while(curCnt > k) {
                freq[nums[st]]--;
                if(freq[nums[st]] == 0) {
                    curCnt--;
                }
                ++st;
            }
            res += ed - st;
        }
        return res;
    }
};
int main() {
    // vector<int> nums = {1, 15, 5, 11};
    // vector<int> nums = {1, 3};
    // vector<int> nums = {1, 3};
    int n = 2;
    vector<int> nums1d = {1, 0};
    vector<vector<int>> nums2d1 = {{1}, {0}};
    vector<vector<int>> nums2d2 = {
        {1,0}
    };
    Solution sl;
    std::cout << sl.subarraysWithKDistinct(nums1d, 3) << std::endl;

    // std::cout << ios::left << std::setw(20) << "Hello, World!" << std::setw(5) << "a s " << 1 << std::endl;
    return 0;
}
