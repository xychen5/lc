#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <limits.h>
#include <numeric>

using namespace std;


class Solution {
public:
    bool canPartition(vector<int>& nums) {
        // caculate the sum and divide by 2, convert the porblem into:
        // try to find a subset's sum whose value is half of the whole sum
        long long wholeSum = std::accumulate(nums.begin(), nums.end(), 0);
        size_t len = nums.size();

        if(1 == wholeSum % 2 || nums.size() < 2) {
            return false;
        }

        long long tarSum = wholeSum / 2;
        vector<vector<int>>  sum(len+1, vector<int>(wholeSum+1, INT32_MIN));
        // when c = 0 => value = 0
        for (size_t front = 0; front < len+1; ++front) {
            sum[front][0] = 0;
        }

        // sum[preNum][varSum] means: the maxi sum of front <preNum> number
        // assume all values are 1
        for(int preNum = 1; preNum < len+1; ++preNum) {             // preNum th item
            for(int varSum = 1; varSum < wholeSum+1; ++varSum) {    // current capacity
                if (varSum - nums[preNum-1] >= 0) {                    // not enough left space to add new one
                    sum[preNum][varSum] = std::max(
                            sum[preNum-1][varSum],                     // not take this value
                            sum[preNum-1][varSum-nums[preNum-1]] + 1   // take this value
                    );
                    if(sum[preNum][varSum] < 0) {
                        sum[preNum][varSum] = INT32_MIN;               // not fully packaged volume's value is int32_min
                    }
                    
                }
                else {
                    sum[preNum][varSum] = sum[preNum-1][varSum];       // not take this value
                }
                
                if(varSum == tarSum) {
                    if (sum[preNum][varSum] > 0) {
                        return true;
                    }
                }
            }
        }

        return false;
    }
};

int main() {
    // vector<int> nums = {1, 15, 5, 11};
    // vector<int> nums = {1, 3};
    // vector<int> nums = {1, 3};
    vector<int> nums = {1, 2, 2, 3};
    Solution sl;
    std::cout << sl.canPartition(nums) << std::endl;

    // std::cout << ios::left << std::setw(20) << "Hello, World!" << std::setw(5) << "a s " << 1 << std::endl;
    return 0;
}
