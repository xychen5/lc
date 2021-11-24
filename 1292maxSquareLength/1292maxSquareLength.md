## 1292最大方块长度

### 1 题目
[https://leetcode-cn.com/problems/maximum-side-length-of-a-square-with-sum-less-than-or-equal-to-threshold/](https://leetcode-cn.com/problems/maximum-side-length-of-a-square-with-sum-less-than-or-equal-to-threshold/)

### 2 解题思路
- 1 建立二维前缀和： 
  ```cpp
          vector<vector<int>> preSum(m+1, vector<int>(n+1, 0));
        for(int i = 1; i < m+1; ++i) {
            for(int j = 1; j < n+1; ++j) {
                preSum[i][j] = preSum[i-1][j] + preSum[i][j-1] - preSum[i-1][j-1] + mat[i-1][j-1];
            }
        }
  ```
- 2 遍历所有边长的正方形即可(每个正放形为起点加上边长)，遍历长度的过程可以通过二分搜索加速

值得思考的点：
如何快速得知当前位置是不是被阻挡了？
使用unordered_set作为hash快速查找

```cpp
class Solution {
public:
    int maxSideLength(vector<vector<int>>& mat, int threshold) {
        // mat.row >= m > i >= 0, mat.col >= n > j >= 0
        // preSum[m][n] -> preSum[i][j] = preSum[m][n] - preSum[m][j] - preSum[i][n] + preSum[i][j];
        int m = mat.size();
        int n = mat[0].size();
        vector<vector<int>> preSum(m+1, vector<int>(n+1, 0));
        for(int i = 1; i < m+1; ++i) {
            for(int j = 1; j < n+1; ++j) {
                preSum[i][j] = preSum[i-1][j] + preSum[i][j-1] - preSum[i-1][j-1] + mat[i-1][j-1];
            }
        }

        // traverse all square
        int maxSquareLen = std::min(m, n);
    //    for(int len = maxSquareLen; len >= 1; --len) { // len could be binary search
    //         for(int i = 0; i <= m - len; ++i) {
    //             for(int j = 0; j <= n - len; ++j) {
    //                 if(getRec(preSum, i+1, j+1, i + len, j + len) <= threshold) {
    //                     return len;
    //                 };
    //             }
    //         }
    //    }
        int stLen = 1;
        int edLen = maxSquareLen;
        int ans = 0;
        while(stLen <= edLen) {
            int len = (stLen + edLen) / 2;
            bool found = false;
            for(int i = 0; i <= m - len; ++i) {
                for(int j = 0; j <= n - len; ++j) {
                    if(getRec(preSum, i+1, j+1, i + len, j + len) <= threshold) {
                        found = true;
                    };
                }
            }
          
            if(found) { // len too small
                stLen = len+1;
                ans = len;
            } else { // len too big
                edLen = len-1;
            }
          
        }

        return ans;
    }

    int getRec(vector<vector<int>>& preSum, int i, int j, int m, int n) {
        return preSum[m][n] - preSum[m][j-1] - preSum[i-1][n] + preSum[i-1][j-1];
    }
};
```