#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <limits.h>
#include <numeric>

using namespace std;


class Solution {
public:
    int minPairSum(vector<int>& nums) {
        sort(nums.begin(), nums.end(), [](int a, int b){ return a < b;});
        
        int curMax = 0;
        size_t len = nums.size();
        for(size_t idx = 0; idx < nums.size() / 2; ++idx) {
            int curPair = nums[idx] + nums[len - 1 - idx];
            curMax = (curMax > curPair) ? curMax : curPair;
        }
        return curMax;
    }
};

int main() {
    // vector<int> nums = {1, 15, 5, 11};
    // vector<int> nums = {1, 3};
    // vector<int> nums = {1, 3};
    vector<int> nums = {1, 7, 2, 5};
    Solution sl;
    std::cout << sl.minPairSum(nums) << std::endl;
    
    // std::cout << ios::left << std::setw(20) << "Hello, World!" << std::setw(5) << "a s " << 1 << std::endl;
    return 0;
}
