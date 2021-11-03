#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <limits.h>
#include <numeric>
#include <unordered_map>
#include <unordered_set>

using namespace std;

class Solution {
public:
    int maxNonOverlapping(vector<int>& nums, int target) {
        int ans = 0;
        // vector<int> preSum(nums.size());

        // preSum[0] = nums[0];
        // for(int i = 1; i < nums.size(); ++i ){
        //     preSum[i] = preSum[i-1] + nums[i];
        // }
        // while(ed < nums.size()) {
        //     for(int st = lastFoundEd; st <= ed; ++st) {
        //         if(preSum[ed] - preSum[st] + nums[st] == target) {
        //             ++ans;
        //             lastFoundEd = ed+1;
        //             break;
        //         }
        //     }
        //     ++ed;
        // }

        int st = 0;
        int ed = 0;
        int lastFoundEd = ed;

        // map<int, int> hash;

        
        while(st < nums.size()) {
            ed = st;
            // hash.clear();   // clear history to avoid repeat count
            unordered_set<int> hash = {0};
            int curSumFromLastFoundEd = 0;
            while(ed < nums.size()) {
                curSumFromLastFoundEd += nums[ed];
                if(hash.count(curSumFromLastFoundEd - target)) {
                    ++ans;
                    st = ed;        // new search start
                    break;
                } else {
                    hash.insert(curSumFromLastFoundEd);
                }
                ++ed;
            }
            ++st;
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
    // std::cout << sl.subarraySum(nums) << std::endl;

    // std::cout << ios::left << std::setw(20) << "Hello, World!" << std::setw(5) << "a s " << 1 << std::endl;
    return 0;
}