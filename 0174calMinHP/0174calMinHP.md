## 0174calMinHP 地下城

### 1 题目
[https://leetcode-cn.com/problems/dungeon-game/](https://leetcode-cn.com/problems/dungeon-game/)

### 2 解题思路
- 1 解题思路：dp 参考
  - 1.1 以起点作为dp的终点，因为dp我们需要关注的是，dp的终点一般为最后答案，所以我们从右下角遍历到左上角0,0
  - 1.2 dp[i][j]表示从ij到最终位置需要的最小生命，那么有： 
  
```cpp
class Solution {
public:
    int calculateMinimumHP(vector<vector<int>>& dungeon) {
        // dp
        int m = dungeon.size();
        int n = dungeon[0].size();
        // reach <i,j> needed min hp
        //  \textit{dp}[i][j]dp[i][j] 表示从坐标 (i,j)(i,j) 到终点所需的最小初始值
        vector<vector<int>> dp(m + 1, vector<int>(n + 1, INT_MAX));
        dp[m][n-1] = dp[m-1][n] = 1;

        for(int i = m-1; i >= 0; --i) {
            for(int j = n-1; j >= 0; --j) {
                dp[i][j] = max(min(dp[i+1][j], dp[i][j+1]) - dungeon[i][j], 1);
            }
        }
        return dp[0][0];
    }
};
```