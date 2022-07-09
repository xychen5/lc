## 2302coountSunarrysScoreLessThanK 统计得分小于 K 的子数组数目

### 1 题目
[https://leetcode.cn/problems/count-subarrays-with-score-less-than-k/](https://leetcode.cn/problems/count-subarrays-with-score-less-than-k/)

### 2 解题思路
- 1 解题思路:
  - 1.1 使用st，ed记录当前窗口，将窗口扩展至最大的满足分数小于k的条件
  - 1.2 ++st，找到下一个st
  - 1.3 对于每个窗口如何计数：
    - 计数：以st开始的区间

```cpp
class Solution {
public:
    long long countSubarrays(vector<int>& nums, long long k) {
        // alway keep st,ed as the max status:
        // score(st, ed) <= k, ed cannot be bigger for each st
        // then we statistic for each st, how many ways start with st

        // moving window score = getScore(nums[st:ed])
        long long st = 0; 
        long long ed = 0;
        long long n = nums.size();
        long long curScore = 0;
        long long cnt = 0;
        while(st < n) {
            bool edMoved = false;
            while(ed < n && (curScore + nums[ed])*(ed - st + 1) < k) {
                curScore += nums[ed];
                ++ed;
                edMoved = true;
            }

            // add cnt start with cur st
            if(curScore*(ed - st) < k) {
                cnt += ed - st;
            }
            
            curScore -= nums[st];
            ++st;
        }
        return cnt;
    }
};
```