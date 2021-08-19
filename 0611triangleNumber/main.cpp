#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <limits.h>
#include <numeric>

using namespace std;


class Solution {
public:
    int triangleNumber(vector<int>& nums) {
        sort(nums.begin(), nums.end(), [](int a, int b){ return a < b;});
        
        int ans = 0;
        size_t len = nums.size();
        // ai + aj < ak, ai < aj < ak
        for (size_t i = 0; i < len; ++i) {
            for (size_t j = i + 1; j < len - 1; ++j) {
                // binary search k, which meet that: nums[k] < nums[i] + nums[j] < nums[k+1]
                size_t k = findK(nums, j + 1, nums[i] + nums[j]);
                ans += k - j;
            }
        }
        
        return ans;
    }
    
    // find the max of k which satisfy:
    // tar = nums[i] + nums[j] <= nums[k]
    size_t findK(vector<int>& nums, size_t stIdx, int tar) {
        size_t edIdx = nums.size() - 1;
        if(nums[edIdx] < tar) {
            return edIdx;
        }
        if(nums[stIdx] >= tar) { // will not find a k
            return stIdx-1;
        }
        while(1) {
            size_t curIdx = (stIdx + edIdx) / 2;
            if (nums[curIdx] > tar) {
                edIdx = curIdx;
            }else if (nums[curIdx] < tar) {
                stIdx = curIdx;
            }else {
                while(nums[curIdx] == tar) {
                    --curIdx;
                }
                return curIdx;
            }
            
            if(1 == edIdx - stIdx) {
                if(curIdx == edIdx) {
                    return edIdx - 1; // nums[edIdx] > tar
                } else if (curIdx == stIdx) {
                    return stIdx; // nums[stIdx] < tar
                }
            }
        }
    }
};

int main() {
    // vector<int> nums = {1, 15, 5, 11};
    // vector<int> nums = {1, 3};
    // vector<int> nums = {1, 3};
    // vector<int> nums = {1, 2, 5, 7};
    vector<int> nums = {2, 2, 3, 4};
    Solution sl;
    std::cout << sl.triangleNumber(nums) << std::endl;
    
    // std::cout << ios::left << std::setw(20) << "Hello, World!" << std::setw(5) << "a s " << 1 << std::endl;
    return 0;
}
