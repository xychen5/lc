# 0560subArraySum 子数组和为k

## 1 题目
[https://leetcode-cn.com/problems/subarray-sum-equals-k/](https://leetcode-cn.com/problems/subarray-sum-equals-k/)

## 2 解题思路
前缀和，普通为o(n^2)，使用hash优化：
subSum[j:i]，本来需要遍历所有的j找出为k的subarray，
但是换个思路：  其实就是找i之前，有多少个前缀和为 preSum[j] - k，
那么我们把前缀和用hash存一下，那不就能够很快找到了？
```cpp
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
```




