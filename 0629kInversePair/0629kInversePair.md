## 0629kInversePair k个逆序数对的方案数

### 1 题目
[https://leetcode-cn.com/problems/k-inverse-pairs-array/](https://leetcode-cn.com/problems/k-inverse-pairs-array/)

### 2 解题思路
- 1 解题思路：dp 参考官方解答

```cpp
class Solution {
public:
    static int constexpr mod = 1000000007;

    int kInversePairs(int n, int k) {
        vector<vector<int>> f(n + 1, vector<int>(k + 1, 0));

        // 设 f[i][j]f[i][j] 表示我们使用数字 1, 2, \cdots, i1,2,⋯,i 的排列构成长度为 ii 的数组
        f[0][0] = 1;
        for(int i = 1; i <= n; ++i) {
            for(int j = 0; j <= k; ++j) {
                // f[i][j] = f[i][j-1] + f[i-1][j] - f[i-1][j-i];
                f[i][j] = (j-1 >= 0 ? f[i][j-1] : 0) + f[i-1][j] - (j-i >= 0 ? f[i-1][j-i] : 0);
                if(f[i][j] >= mod) {
                    f[i][j] -= mod;
                } else if(f[i][j] < 0) {
                    f[i][j] += mod;
                }
            }
        }
        
        return f[n][k];
    }
};
```