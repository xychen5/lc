## 0403frogCrossRiver 青蛙过河

### 1 题目
[https://leetcode-cn.com/problems/frog-jump/](https://leetcode-cn.com/problems/frog-jump/)

### 2 解题思路
- 1 动态规划：首先明白动态规划最终是指向结果的，于是，定义dp[i][k]，为到达i的最后一跳长度为k，是否能够跳到目的地
  - 1.1 首先有疑问：那k岂不是max(stone) - min(stone)，那k就会非常大，不合理啊？错，因为每一跳长度最多增加1，然而你最多有n-1跳，于是 k <= n-1
  - 1.2 状态转移: dp[i][k] = dp[j][k] || dp[j][k-1] || dp[j][k+1]，j就是i的上一跳，那么我们可以直到，j到i，k=stone[i] - stone[j]
  - 1.3 需要注意到上面的状态转移: 因为是从j跳，必须保证: k <= j+1，因为你从第j个石头开始跳，最远长度就是j+1


```cpp
class Solution {
public:
    bool canCross(vector<int>& stones) {
        int n = stones.size();
        // jump to i, and last jump dis
        vector<vector<bool>> jump(n , vector<bool>(n, false));
        jump[0][0] = true;

        // the i th jump len <= i
        for(int i = 1; i < n; ++i) {
            if(stones[i] - stones[i - 1] > i) {
                return false;
            }
        }

        // dp, from j jump to i
        bool res = false;
        for(int i = 1; i < n; ++i) {
            for(int j = 0; j < i; ++j) {
                int k = stones[i] - stones[j];
                // cout << j << " -> " << i << " 's dis: " << k << endl;
                if(k > j + 1) {
                    continue;
                }
                // cout << jump[j].size() << " / " << k + 1 << " jump[j][k] || jump[j][k-1] || jump[j][k+1] " << jump[j][k] << jump[j][k-1] << jump[j][k+1] << endl;
                jump[i][k] = jump[j][k] || jump[j][k-1] || jump[j][k+1];
                if(i == n - 1 && jump[i][k]) {
                    res = true;
                }
            }
        }
        return res;
    }
};
```