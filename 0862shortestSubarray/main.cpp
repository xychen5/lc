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
    int shortestSubarray(vector<int>& nums, int k) {
        list<int> monoQueue;
        vector<long long> preSum = {0};
        for(size_t i = 0; i < nums.size(); ++i) {
            preSum.push_back(nums[i] + preSum.back());
        }

        // mainly ref: https://leetcode-cn.com/problems/shortest-subarray-with-sum-at-least-k/solution/he-zhi-shao-wei-k-de-zui-duan-zi-shu-zu-by-leetcod/
        int res = INT_MAX;
        for(int i = 0; i < preSum.size(); ++i) {
            while(monoQueue.size() > 0 && preSum[monoQueue.back()] >= preSum[i]) {
                monoQueue.pop_back();
            }
            while(monoQueue.size() > 0 && preSum[monoQueue.front()] <= preSum[i] - k) {
                res = std::min(res, i - monoQueue.front());
                                monoQueue.pop_front();

            }
            monoQueue.emplace_back(i);
        }
        return res < nums.size() + 1 ? res : -1;

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
    std::cout << sl.shortestSubarray(nums1d) << std::endl;

    // std::cout << ios::left << std::setw(20) << "Hello, World!" << std::setw(5) << "a s " << 1 << std::endl;
    return 0;
}
