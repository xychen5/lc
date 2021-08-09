#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <limits.h>
#include <numeric>

using namespace std;

class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        int ans = nums[0];
        int tmpSum = 0;
        for(size_t idx = 0; idx < nums.size(); ++idx) {
            tmpSum = std::max(nums[idx], tmpSum + nums[idx]); // 当，tmpSum小于零，则重新开始选择子串
            ans = max(tmpSum, ans);
        }
        return ans;
    }
};

int main() {
    // vector<int> nums = {1, 15, 5, 11};
    // vector<int> nums = {1, 3};
    // vector<int> nums = {1, 3};
    vector<int> nums = {1, 2, 2, 3};
    Solution sl;
    std::cout << sl.maxSubArray(nums) << std::endl;

    // std::cout << ios::left << std::setw(20) << "Hello, World!" << std::setw(5) << "a s " << 1 << std::endl;
    return 0;
}