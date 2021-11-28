## 2025waysToPartition

### 1 题目
[https://leetcode-cn.com/problems/maximum-number-of-ways-to-partition-an-array/](https://leetcode-cn.com/problems/maximum-number-of-ways-to-partition-an-array/)

### 2 解题思路
- 1 普通思路
对于每一个改变位置的数组，遍历每一个改变值的位置，然后遍历一遍数组统计有多少个该种改变方案下，有多少个分割方法，复杂度o(n**2)
- 2 改进思路
> 改变的情况下，使用hash来加速
> 其实就是将findPivotNum的寻找过程使用hash来加速，其过程如下:
> 注意findPivotNum在对每个changePos遍历的时候，都去O(n)查找有多少个满足如下条件的pivot的一个分割：
>     preSum[n] + nums[changePos] - k == 2 * preSum[pivot]  -> 对应的是改变的数字在pivot左边
>     或者 preSum[n] - nums[changePos] + k == 2 * preSum[pivot] -> 改变的在右边或者就在pivot处
> 则我们搜寻这些pivot使用hash在o(1)时间内完成
> 当前改变位置 r:改变位置左侧搜寻的前缀和 l:改变位置右侧搜寻的前缀和
> cur = 0, 则在r: preSum[1 : n-1]中搜寻 l:[]
> cur = 1, r: preSum[2 : n-1] l: preSum[1]
> ...
> cur = n-2, r: preSum[n-1] l: preSum[1:n-2]
> cur = n-1, r: [] l: preSum[1:n-1]
```cpp
class Solution {
public:
    int waysToPartition(vector<int>& nums, int k) {
        vector<long long> preSum = {0};
        long long n = nums.size();
        for(long long i = 0; i < nums.size(); ++i) {
            preSum.emplace_back(nums[i] + preSum.back());
        }

        // 注意findPivotNum在对每个changePos遍历的时候，都去O(n)查找有多少个满足如下条件的pivot的一个分割：
        //     preSum[n] + nums[changePos] - k == 2 * preSum[pivot]  -> 对应的是改变的数字在pivot左边
        //     或者 preSum[n] - nums[changePos] + k == 2 * preSum[pivot] -> 改变的在右边或者就在pivot处
        // 很显然左侧的数据可以用hash存起来，保证查找pivot的个数能够降低到O(1)
        unordered_map<long long, long long> pivotInLeft; // 存所有下标比curChangePos小的preSum
        unordered_map<long long, long long> pivotInRight; // 存所有下标大于等于curChangePos的preSum
        

        for(long long pivot = 1; pivot < nums.size(); ++pivot) {
            pivotInRight[2 * preSum[pivot]]++;
            // changePosInRight[preSum[n] - nums[pos] + k]++;
        }

        long long ans = 0;
        // 不改变的情况下
        ans = max(ans, findPivotNum(nums, preSum, 0, k, false));

        // // 改变的情况下 // o(n ** 2) 会超时，想办法加速
        // for(long long i = 0; i < nums.size(); ++i) {
        //     ans = max(ans, findPivotNum(nums, preSum, i, k, true));
        // }

        // 改变的情况下，使用hash来加速
        // 其实就是将findPivotNum的寻找过程使用hash来加速，其过程如下:
        // 注意findPivotNum在对每个changePos遍历的时候，都去O(n)查找有多少个满足如下条件的pivot的一个分割：
        //     preSum[n] + nums[changePos] - k == 2 * preSum[pivot]  -> 对应的是改变的数字在pivot左边
        //     或者 preSum[n] - nums[changePos] + k == 2 * preSum[pivot] -> 改变的在右边或者就在pivot处
        // 当前改变位置 r:改变位置左侧搜寻的前缀和 l:改变位置右侧搜寻的前缀和
        // cur = 0, 则在r: preSum[1 : n-1]中搜寻 l:[]
        // cur = 1, r: preSum[2 : n-1] l: preSum[1]
        // ...
        // cur = n-2, r: preSum[n-1] l: preSum[1:n-2]
        // cur = n-1, r: [] l: preSum[1:n-1]

        for(long long curChangePos = 0; curChangePos < nums.size(); ++curChangePos) {
            ans = max(pivotInRight[preSum[n] + nums[curChangePos] - k] + \
                      pivotInLeft[preSum[n] - nums[curChangePos] + k], \
                      ans) ;

            pivotInLeft[2 * preSum[curChangePos + 1]]++; 
            pivotInRight[2 * preSum[curChangePos + 1]]--;
        }
        return ans;
    }

    long long findPivotNum(vector<int>& nums, vector<long long>& preSum, long long changePos, long long k, bool change) {
        long long ans = 0;
        long long n = nums.size();
        if(!change) {
            for(long long pivot = 1; pivot < nums.size(); ++pivot) {
                if(preSum[n] == preSum[pivot] + preSum[pivot]) {
                    ++ans;
                }
            }
            return ans;
        }
        
        for(long long pivot = 1; pivot < nums.size(); ++pivot) {
            if(changePos < pivot) {
                if(preSum[n] == 2 * preSum[pivot] - nums[changePos] + k) {
                    ++ans;
                }
            } else {
                if(preSum[n] - nums[changePos] + k == 2 * preSum[pivot]) {
                    ++ans;
                }
            }
        }
        
        return ans;
    }
};
```