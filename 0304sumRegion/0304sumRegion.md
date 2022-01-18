## 0304 二维区域和检索

### 1 题目：
[https://leetcode-cn.com/problems/range-sum-query-2d-immutable/](https://leetcode-cn.com/problems/range-sum-query-2d-immutable/)

### 2 解题思路：
- 1 普通思路：一维前缀和，按行计算前缀和，使用m x n的矩阵存储，然后计算矩形区域，则只需要O(m)的计算复杂度
- 2 优化：二维前缀和，pre[i][j]存储的是0，0到i，j处的矩形区域和，那么计算方式为：
> preMat2[i+1][j+1] = preMat2[i][j+1] + preMat2[i+1][j] - preMat2[i][j] + matrix[i][j];
```cpp
class NumMatrix {
public:
    static constexpr int matLen = 205;
    vector<vector<int>> preMat; // in one dimension
    vector<vector<int>> preMat2; // in 2 dimension
    

    int m = -1;
    int n = -1;
    NumMatrix(vector<vector<int>>& matrix) {
        // preMat.resize(this->matLen, vector<int>(this->matLen, 0));
        preMat2.resize(this->matLen, vector<int>(this->matLen, 0));
        m = matrix.size();
        n = matrix[0].size();
        for(int i = 0; i < m; ++i) {
            for(int j = 0; j < n; ++j) {
                // preMat[i][j+1] = preMat[i][j] + matrix[i][j];
                // cout << preMat[i][j+1] << endl;
                preMat2[i+1][j+1] = preMat2[i][j+1] + preMat2[i+1][j] - preMat2[i][j] + matrix[i][j];
            }
        }
    }
    
    int sumRegion(int row1, int col1, int row2, int col2) {
        int res = 0;
        res = preMat2[row2+1][col2+1] + preMat2[row1][col1] - preMat2[row1][col2+1] - preMat2[row2+1][col1];
        // for(int rowIdx = row1; rowIdx <= row2; ++rowIdx) {
        //     res += (preMat[rowIdx][col2+1] - preMat[rowIdx][col1]);
        // }
        return res;
    }
};
```