## 0115numDistinct 目标子序列不同的个数

### 1 题目
[https://leetcode-cn.com/problems/distinct-subsequences/](https://leetcode-cn.com/problems/distinct-subsequences/)

### 2 解题思路
- 1 解题思路：
  - 创建二维数组 \textit{dp}dp，其中 \textit{dp}[i][j]dp[i][j] 表示在 s[i:]s[i:] 的子序列中 t[j:]t[j:] 出现的个数。
  
```cpp
class Solution {
public:
    int numDistinct(string s, string t) {
        int m = s.size(), n = t.size();
        // 创建二维数组 \textit{dp}dp，其中 \textit{dp}[i][j]dp[i][j] 表示在 s[i:]s[i:] 的子序列中 t[j:]t[j:] 出现的个数。
        
        vector<vector<unsigned long>> dp(m + 1, vector<unsigned long>(n + 1));
        if(m < n) {
            return 0;
        }

        // init dp[i][n]
        for(int i = 0; i <= m; ++i) {
            dp[i][n] = 1;
        }

        // when i < m && j < n
        for(int i = m-1; i >= 0; --i) {
            for(int j = n-1; j >= 0; --j) {
                if(s[i] == t[j]) {
                    dp[i][j] = dp[i+1][j+1] + dp[i+1][j];
                } else {
                    dp[i][j] = dp[i+1][j];
                }
            }
        }

        return dp[0][0];
        
    }
};
```