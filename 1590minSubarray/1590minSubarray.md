## 1590 最短移除子数组以便被k整除

### 1 题目
[https://leetcode-cn.com/problems/make-sum-divisible-by-p/](https://leetcode-cn.com/problems/make-sum-divisible-by-p/)

### 2 解题思路
较为容易想到前缀和思路：
- 1 首先考虑到：移除一个什么样的子数组，能够使得被k整除？
  - 记总和为s，那么s%p为余数，所以需要移除一个余数为s%p的子数组来使得被k整除 
  - 那么至少o(n^2)复杂度的算法就有了
- 2 如何快速找到子数组？
  - 提问： 对于每到来的一个下标，是否为可以移除的子数组的右边界呢？仅仅需要找到之前的前缀和中是否存在一个前缀和与当前下标的前缀和构成子数组mod p的余数是否为s%p即可
  - 如何快速找到是否有这么一个前缀和呢？考虑使用map来存，key： 余数， value: 前缀和下标，假设当前下标对应的余数为mod，目标余数s%p = r，那么只需要找之前的所有前缀和中是否有余数为 mod - r(或者 mod - r + p)的前缀和即可


```cpp
class Solution {
public:
    int shortestSubarray(vector<int>& nums, int k) {
        list<int> monoQueue;
        vector<long long> preSum = {0};
        for(size_t i = 0; i < nums.size(); ++i) {
            preSum.push_back(nums[i] + preSum.back());
        }

        // mainly ref: https://leetcode-cn.com/problems/shortest-subarray-with-sum-at-least-k/solution/he-zhi-shao-wei-k-de-zui-duan-zi-shu-zu-by-leetcod/
        int res = INT_MAX;
        for(int i = 0; i < preSum.size(); ++i) {
            while(monoQueue.size() > 0 && preSum[monoQueue.back()] >= preSum[i]) {
                monoQueue.pop_back();
            }
            while(monoQueue.size() > 0 && preSum[monoQueue.front()] <= preSum[i] - k) {
                res = std::min(res, i - monoQueue.front());
                                monoQueue.pop_front();

            }
            monoQueue.emplace_back(i);
        }
        return res < nums.size() + 1 ? res : -1;

    }
};
```