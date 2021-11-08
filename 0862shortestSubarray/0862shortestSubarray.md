## 0862 和大于等于k的最短连续子数组

### 1 题目
[https://leetcode-cn.com/problems/shortest-subarray-with-sum-at-least-k/](https://leetcode-cn.com/problems/shortest-subarray-with-sum-at-least-k/)

### 2 解题思路
参考官方题解： [https://leetcode-cn.com/problems/shortest-subarray-with-sum-at-least-k/solution/he-zhi-shao-wei-k-de-zui-duan-zi-shu-zu-by-leetcod/](https://leetcode-cn.com/problems/shortest-subarray-with-sum-at-least-k/solution/he-zhi-shao-wei-k-de-zui-duan-zi-shu-zu-by-leetcod/)
首先，
- 1 暴力思路： O(n^2)，求出所有sum[i->j] 找出最小的即可
- 2.0 使用单调队列优化： monoQueue总是存下标 m[i] ，这些下标需要保证两个性质：
>- 我们用数组 P 表示数组 A 的前缀和，即 P[i] = A[0] + A[1] + ... + A[i - 1]。我们需要找到 x 和 y，使得 P[y] - P[x] >= K 且 y - x 最小。
>我们用 opt(y) 表示对于固定的 y，最大的满足 P[x] <= P[y] - K 的 x，这样所有 y - opt(y) 中的最小值即为答案。我们可以发现两条性质
>如果 x1 < x2 且 P[x2] <= P[x1]，那么 opt(y) 的值不可能为 x1，这是因为 x2 比 x1 大，并且如果 x1 满足了 P[x1] <= P[y] - K，那么 P[x2] <= P[x1] <= P[y] - K，即 x2 同样满足 P[x2] <= P[y] - K。
>如果 opt(y1) 的值为 x，那么我们以后就不用再考虑 x 了。这是因为如果有 y2 > y1 且 opt(y2) 的值也为 x，但此时 y2 - x 显然大于 y1 - x，不会作为所有 y - opt(y) 中的最小值。
- 2.1 做法为：

>我们维护一个关于前缀和数组 P 的单调队列，它是一个双端队列（deque），其中存放了下标 x：x0, x1, ... 满足 P[x0], P[x1], ... 单调递增。这是为了满足性质一。
>当我们遇到了一个新的下标 y 时，我们会在队尾移除若干元素，直到 P[x0], P[x1], ..., P[y] 单调递增。这同样是为了满足性质一。
>同时，我们会在队首也移除若干元素，如果 P[y] >= P[x0] + K，则将队首元素移除，直到该不等式不满足。这是为了满足性质二。

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