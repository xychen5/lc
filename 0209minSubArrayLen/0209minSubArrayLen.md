## 0209 长度最小的和大于k的子数组

### 1 题目
[https://leetcode-cn.com/problems/shortest-subarray-with-sum-at-least-k/](https://leetcode-cn.com/problems/shortest-subarray-with-sum-at-least-k/)

### 2 解题思路
参考官方题解： 
首先，
- 1 暴力思路： O(n^2)，求出所有sum[i->j]>k 找出最小的j-i即可，优化思路：对于同一个j来说，找i的时候可以使用2分法快速定位最大的i，复杂度降为O(n^logn)
- 2 使用滑动窗口优化： 记录窗口为st->ed，那么每次移动窗口操作为： 首先将ed累加，直到窗口内的总和大于k，更新结果，然后将st++，直到窗口里面的值的和小于k，更新结果即可，其中需要注意的是，当移动st的时候，当窗口总和大于k时，每次都要更新结果，且需要特别处理窗口结果等于k的情况。

```cpp
class Solution {
public:
    int minSubArrayLen(int target, vector<int>& nums) {
        int st = 0;
        int ed = 0;
        int res = INT_MAX;
        int curSum = 0;
        vector<long long> preSum = {0};
        for(size_t i = 0; i < nums.size(); ++i) {
            preSum.push_back(nums[i] + preSum.back());
        }

        for(; st < nums.size(); ++st) {
            // add at the tail
            while(ed < nums.size()) {
                curSum = preSum[ed + 1] - preSum[st];
                if(curSum >= target) break;
                ++ed;
            }

            if(curSum >= target) {
                res = std::min(res, ed + 1 - st);
            } else {
                break;
            }

            // remove from the head
            while(st < nums.size() && curSum > target) {
                res = std::min(res, ed + 1 - st);
                curSum = preSum[ed + 1] - preSum[++st];
            }
            if(curSum == target) {
                res = std::min(res, ed + 1 - st);
            }
        }
        return res > nums.size() ? 0 : res;
    }
};
```