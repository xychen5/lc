## 0363maxSumSubMatrix 最大子区域和

### 1 题目：
[https://leetcode-cn.com/problems/max-sum-of-rectangle-no-larger-than-k/](https://leetcode-cn.com/problems/max-sum-of-rectangle-no-larger-than-k/)

### 2 解题思路：
- 1 普通思路：一维前缀和，按行计算前缀和，使用m x n的矩阵存储，然后计算矩形区域，则只需要O(m)的计算复杂度
- 2 优化：二维前缀和，pre[i][j]存储的是0，0到i，j处的矩形区域和，那么计算方式为：
> preMat2[i+1][j+1] = preMat2[i][j+1] + preMat2[i+1][j] - preMat2[i][j] + matrix[i][j];
- 3 使用二位前缀和去计算子区域的和，搜索子区域的方式：
  - 3.1 对于每个子区域的上下边界搜索左右边界，上下左边界搜索复杂度为o(n^2), 而后搜索左右边界，对于每一个右边界O(n)，搜索左边界，什么样的左边界？left满足sum(up, down, 0, right) - k <= sum(up, down, 0, left), 也就是在[0, right]的范围内找到最小的大于sum(up, down, 0, right) - k的left，在遍历的过程中使用set存所有的sum(up, down, 0, right), 在这个set里面找left，使用lower_bound函数，只需要log(n)复杂度，于是总复杂度为 o(m^2 * nlog(n))
  - 3.2 上述核心思想： 本来需要找right和left的对子，但是现在借助k，找left就变成在right的历史中搜索即可
    - 3.2.1 原来思想：sum(up, down, 0, right) - sum(up, down, 0, left) <= k
    - 3.2.2 新的思想：sum(up, down, 0, right) - k <= sum(up, down, 0, left)
```cpp
class Solution {
public:
    static constexpr int matLen = 102;
    vector<vector<int>> preMat; // 2d prefix sum
    int m = -1;
    int n = -1;
    int maxSumSubmatrix(vector<vector<int>>& matrix, int k) {
        // cal 2d prefix sum
        m = matrix.size();
        n = matrix[0].size();
        preMat.resize(m+1, vector<int>(n+1, 0));
        for(int i = 0; i < m; ++i){
            for(int j = 0; j < n; ++j){
                preMat[i+1][j+1] = preMat[i][j+1] + preMat[i+1][j] - preMat[i][j] + matrix[i][j];
                // cout << preMat[i+1][j+1] << endl;
            }
        }

        // for each up and down, find max l,r
        int res = INT_MIN;
        for(int d = 0; d < m; ++d) {
            for(int u = d; u >= 0; --u) {
                set<int> lSet = {0};
                for(int r = 0; r < n; ++r) {
                    int sumRight = sumRegion(u, d, 0, r);
                    set<int>::iterator lbPtr = lSet.lower_bound(sumRight - k);
                    lSet.insert(sumRight);
                    if(lbPtr != lSet.end()) {
                        res = max(res, sumRight - *lbPtr);
                    }
                }
            }
        }

        return res;
    }

    int sumRegion(int up, int down, int left, int right) {
        return preMat[down+1][right+1] - preMat[down+1][left] - preMat[up][right+1] - preMat[up][left];
    }
};
```