## 1289minFallingPathSum 下降路径最小和  II

### 1 题目
[https://leetcode.cn/problems/minimum-falling-path-sum-ii/](https://leetcode.cn/problems/minimum-falling-path-sum-ii/)

### 2 解题思路
- 1 解题思路
  - dp[i][j]：表示以ij为路径结尾的最小下降路径和
  - dp[i][j] = min(dp[i-1][k] | k != j)
  - 然后结果就是： min(dp[n-1][j] | j)


```cpp
class Solution {
public:
    int minFallingPathSum(vector<vector<int>>& grid) {
        int n = grid.size();
        vector<vector<int>> dp(n, vector<int>(n, INT_MAX));
        for(int c = 0; c < n; ++c) {
            dp[0][c] = grid[0][c];
        }

        auto getMinElementExceptIndexE = []  (vector<int>& arr, int e) -> pair<int, int> {
            int res = INT_MAX;
            int minIdx = -1;
            for(int i = 0; i < arr.size(); ++i) {
                if(i != e) {
                    if(arr[i] < res) {
                        res = arr[i];
                        minIdx = i;
                    }
                }
            }
            return {res, minIdx};
        };

        for(int l = 1; l < n; ++l) {
            for(int c = 0; c < n; ++c) {
                auto p = getMinElementExceptIndexE(dp[l-1], c);
                dp[l][c] = min(dp[l][c], grid[l][c] + dp[l-1][p.second]);
                // cout << "lc: " << l << " " << c << " " << dp[l][c] << " min: " << p.first << " " << dp[l-1][p.second] << endl;
            }
        }

        int finRes = INT_MAX;
        for(int c = 0; c < n; ++c) {
            finRes = min(dp[n-1][c], finRes);
        }

        return finRes;
    }
};
```