#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <limits.h>
#include <numeric>
#include <unordered_map>

using namespace std;
class Solution {
public:
    int subarraySum(vector<int>& nums, int k) {
        vector<int> prefSum(nums.size());
        prefSum[0] = nums[0];
        for(int i = 1; i < nums.size(); ++i) {
            prefSum[i] += (nums[i] + prefSum[i-1]); 
        }

        int st = 0;
        int ed = 0;
        int ans = 0;
        int curSum = 0;
        std::unordered_map<int, int> hash;
        hash[0] = 1;
        while(ed < nums.size()) {
            if(hash.find(prefSum[ed] - k) != hash.end()) {
                ans += hash[prefSum[ed] - k];
            } 
            hash[prefSum[ed]]++;

            
            // for(int st = ed; st >= 0; --st) {
            //     curSum = prefSum[ed] - prefSum[st] + nums[st];
            //     if(curSum == k){
            //         ++ans;
            //     }
            // }
            ++ed;
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
    std::cout << sl.subarraySum(nums) << std::endl;

    // std::cout << ios::left << std::setw(20) << "Hello, World!" << std::setw(5) << "a s " << 1 << std::endl;
    return 0;
}