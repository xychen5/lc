# 1546最大非重叠数组

## 1 题目
[https://leetcode-cn.com/problems/maximum-number-of-non-overlapping-subarrays-with-sum-equals-target/submissions/](https://leetcode-cn.com/problems/maximum-number-of-non-overlapping-subarrays-with-sum-equals-target/submissions/)

## 2 解题思路
最为关键的一句话：
每次找结束序号最小的和为target的子数组，然后从这个子数组的后面开始搜寻下一个子数组，经典贪心。

前缀和，普通为o(n^2)，使用hash优化：
subSum[j:i]，本来需要遍历所有的j找出为k的subarray，
但是换个思路：  其实就是找i之前，有多少个前缀和为 preSum[j] - k，
那么我们把前缀和用hash存一下，那不就能够很快找到了？

但是有一个问题，在下一次搜寻开始的时候，需要将上一次搜寻过程的hash清零，
否则上一次的hash的结果会影响当前子序和。
而且假设上一次搜寻到j了，那么这次从j+1开始搜寻，必须保证前缀和也是从j+1开始

```cpp
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
```




