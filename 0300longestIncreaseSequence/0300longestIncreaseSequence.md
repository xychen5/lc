## 0300longestIncreaseSequence 最长递增序列

### 1 题目
[https://leetcode-cn.com/problems/longest-increasing-subsequence/](https://leetcode-cn.com/problems/longest-increasing-subsequence/)

### 2 解题思路
- 1 参考官方解答： dp[i] = max(dp[j] + 1), {j | 0 <= j < i}，dp[i]表示以nums[i]为结尾元素的最长递增子序列的长度，复杂度 o(n^2)
- 2 优化：遍历nums到nums[i]的时候，有minBitLIS[j]表示：对于nums[:i]这个子数组中，所有递增子序列子序列，在j位的最小数字，那么，最后minBitLIS的长度就是最终结果
  - 2.1 于是算法变成了：
  - 2.2 若nums[i] < minBitLIS.back()，则直接将nums[i]加入minBitLIS，否则找到第一个大于nums[i]的位置，然后替换为nums[i]
  - 2.3 遍历完成，返回minBitLIS的长度

```cpp
class Solution {
public:
    int lengthOfLIS(vector<int>& nums) {
        // official way 2:
        if(1 == nums.size()) {
            return 1;
        }
        vector<int> minBitLIS = {nums[0]};
        
        int len = 1;
        int n = nums.size();
        for(int i = 1; i < n; ++i) {
            if(minBitLIS.back() < nums[i]) {
                minBitLIS.push_back(nums[i]);
                ++len;
            } else {
                // bin search the first num bigger than nums[i] in minBitLIS
                // to update the min bit of LIS
                updateMinBit(minBitLIS, nums[i]);
            }
        }
         
        return len;
        
    }

    void updateMinBit(vector<int>& minBitVec, int num) {
        int n = minBitVec.size();
        int st = 0, ed = n-1;
        int mid = -1;
        while(st <= ed) {
            mid = (st + ed) / 2;
            if(minBitVec[mid] > num) {
                ed = mid - 1;
            } else if(minBitVec[mid] < num) {
                st = mid + 1;
            } else {
                break;
            }
        }
        if(minBitVec[mid] > num) {
            minBitVec[mid] = num;
        } else if(minBitVec[mid] < num){
            minBitVec[min(mid + 1, n-1)] = num;
        }
    }
};
```