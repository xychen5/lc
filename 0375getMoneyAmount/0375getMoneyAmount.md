## 0375 此数字大小所需最小金额

### 1 题目
[https://leetcode-cn.com/problems/guess-number-higher-or-lower-ii/](https://leetcode-cn.com/problems/guess-number-higher-or-lower-ii/)


### 2 解题思路
- 1 采用最大最小算法：很明显，递归的获得在深度为depth下对于max或者minplayer相关的收益
- 2 该搜索过程我们采用矩阵存储模拟，对应到动态规划算法中区间DP[https://oi-wiki.org/dp/interval/](https://oi-wiki.org/dp/interval/)的类型
```cpp
function  minimax(node, depth, maximizingPlayer) is
    if depth = 0 or node is a terminal node then
        return the heuristic value of node
    if maximizingPlayer then
        value := −∞
        for each child of node do
            value := max(value, minimax(child, depth − 1, FALSE))
        return value
    else (* minimizing player *)
        value := +∞
        for each child of node do
            value := min(value, minimax(child, depth − 1, TRUE))
        return value
```

```cpp
class Solution {
public:
    int getMoneyAmount(int n) {
        // 采用区间dp
        // f[i][j]代表从i到j的获胜的最小现金
        // 
        // f[1][n] = min(x + max(f[1][k-1], f[k+1][n])) 
        // 结合题目意思： f[i][i] == 0，就一个数字没办法猜错
        // 

        vector<vector<int>> dp(n+1, vector<int>(n+1));

        for(int len = 1; len < n+1; ++len) {
            for(int i = 1; i < n - len + 2; ++i) {
                int j = i + len - 1;
                if(i == j) {
                    dp[i][j] = 0;
                    continue;
                }
                // when k == j
                dp[i][j] = j + dp[i][j-1];
                for(int k = i; k < j; ++k) {
                    dp[i][j] = min(dp[i][j], k + max(dp[i][k-1], dp[k+1][j]));

                }
            }
        }
        return dp[1][n];
    }
};
```
