## 0664wiredPrinter 奇怪打印机

### 1 题目
[https://leetcode-cn.com/problems/strange-printer](https://leetcode-cn.com/problems/strange-printer)

### 2 解题思路
- 1 解题思路：dp 参考官方解答

```cpp
class Solution {
public:
    int strangePrinter(string s) {
        int n = s.size();
        
        // f[i][j]f[i][j] 表示打印完成区间 [i,j][i,j] 的最少操作数
        vector<vector<int>> f(n, vector<int>(n, INT_MAX));
        
        // init:
        for(int i = 0; i < n; ++i) {
            f[i][i] = 1;
        }

        // dp
        for(int j = 1; j < n; ++j) {
            for(int i = j - 1; i >= 0; --i) {
                if(s[i] == s[j]) {
                    f[i][j] = f[i][j-1];
                } else {
                    for(int k = i; k < j; ++k) {
                        f[i][j] = min(f[i][k] + f[k+1][j], f[i][j]);
                    }
                }
                
            }
        }

        return f[0][n-1];

    }
};
```