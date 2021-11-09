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
    int minSubarray(vector<int>& nums, int p) {
        vector<long long> preSum = {0};
        // 存储前缀和模p的余数->前缀和的idx
        map<int, int> modValueToIdx;
        modValueToIdx[0] = 0;
        for(int i = 0; i < nums.size(); ++i) {
            preSum.emplace_back(preSum.back() + nums[i]);
        } 

        int tarMod = preSum.back() % p;
        int res = INT_MAX;
        for(int i = 0; i < nums.size(); ++i) {
            int curMod = preSum[i + 1] % p;
            modValueToIdx[curMod] = i + 1;
            if(curMod >= tarMod) {
                map<int, int>::iterator it = modValueToIdx.find(curMod - tarMod);
                if(it != modValueToIdx.end()) {
                    res = std::min(res, i + 1 - it->second);
                }
            } else {
                map<int, int>::iterator it = modValueToIdx.find(p + curMod - tarMod);
                if(it != modValueToIdx.end()) {
                    res = std::min(res, i + 1 - it->second);
                }
            }
        }

        return res >= nums.size() ? -1 : res;
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
    std::cout << sl.minSubarray(nums1d, 3) << std::endl;

    // std::cout << ios::left << std::setw(20) << "Hello, World!" << std::setw(5) << "a s " << 1 << std::endl;
    return 0;
}
