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
    int minMoves(vector<int>& nums, int k) {
        // main ref: https://leetcode-cn.com/problems/minimum-adjacent-swaps-for-k-consecutive-ones/solution/de-dao-lian-xu-k-ge-1-de-zui-shao-xiang-lpa9i/

        vector<int> g;
        vector<int> gPreSum;
        gPreSum.emplace_back(0);
        for(int i = 0; i < nums.size(); ++i) {
            if(1 == nums[i]) {
                g.emplace_back(i - g.size());
                gPreSum.emplace_back(gPreSum.back() + g.back());
            }
        }

        // moving window with len = k
        int minMov = INT_MAX;
        int st = 0;
        while(st <= g.size() - k) {
            int midIdxInG = (st + st + k - 1) / 2;
            int midIdxInNums = g[midIdxInG];
            int movCnt = (2*(midIdxInG - st) - k + 1) * midIdxInNums + gPreSum[st + k] - gPreSum[midIdxInG + 1] - (gPreSum[midIdxInG] - gPreSum[st]);
            minMov = std::min(movCnt, minMov);

            ++st;
        }
        return minMov;
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
    std::cout << sl.minMoves(nums1d, n) << std::endl;

    // std::cout << ios::left << std::setw(20) << "Hello, World!" << std::setw(5) << "a s " << 1 << std::endl;
    return 0;
}
