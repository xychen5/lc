## 0329longestIncreasingPath  矩阵中的最长递增路径

### 1 题目
[https://leetcode-cn.com/problems/longest-increasing-path-in-a-matrix/](https://leetcode-cn.com/problems/longest-increasing-path-in-a-matrix/)


### 2 解题思路
- 1 自己的思路：
  - 1.1 对于每一个起点dfs，然后获取每个起点最长的递增路径
  - 1.2 改进： 1.1中很显然存在重复计算，那么我们只需要增加一个storeLen矩阵，将每一次dfs路径中每个点的最长递增路径都记下来，这样就规避了1.1中不同dfs经过同一个点之后的重复dfs探索
  - 1.3 storeLen存储的是每个顶点目前的最长路径，初始化为1(也就是他自己作为唯一顶点)
- 2 我陷入的误区
  - 2.1 1.2会有storeLen，那么每次对一个点进行dfs，获取的并不仅仅是一个顶点的storeLen[i][j]，而是整条路径中每个顶点的storeLen[i][j]，于是需要把storeLen[i][j]在dfs中更新，然后作为结果返回即可！不然在调用处更新的话，每次dfs只能更新storeLen[i][j]一个节点其实作用不大
  - 2.2 dfs中，需要visited的flag标志矩阵记录本次dfs访问过哪些节点来避免环形dfs的死循环吗？不需要，因为我们是**递增路径!**

- 2 拓扑排序的思路
回顾拓扑排序：
  - 2.0 当q不空
    - 2.0.1 队列q中存储出度为0的节点
    - 2.0.2 每次从队里出来一个视为访问过
    - 2.0.3 更新出队节点影响的节点的出度，出度为0加入q
  - 2.1 统计出队个数和总结点个数是否相等，不等则意味着有环路
  - 2.2 最关键的理解是，由于目标为递增路径，所以不需要考虑环路(不可能存在递增的环路，就像不存在首尾相连的上升楼梯)问题，则意味着可以使用拓扑排序，从出度为0的地方，开始做bfs，有几层bfs，则意味着最长的递增路径为多长。
```cpp
class Solution {
public:
    int m = -1;
    int n = -1;
    int dx[4] = {1, 0, -1, 0};
    int dy[4] = {0, 1, 0, -1};

    int longestIncreasingPath(vector<vector<int>>& matrix) {
        // using hash map to store the vertex's longest path length
        m = matrix.size();
        n = matrix[0].size();
        unordered_map<int, int> fromToLen;
        vector<vector<int>> storeLen(m, vector<int>(n, 1));
        
        // start from each point and do dfs, using fromToLen to store
        int res = INT_MIN;
        for(int i = 0; i < m; ++i) {
            for(int j = 0; j < n; ++j) {
                // star from the i, j
                res = max(res, dfs(i, j, matrix, storeLen));
            }
        }

        return res;
    }

    int dfs(int x, int y, vector<vector<int>>& matrix, vector<vector<int>>& storeLen) {
        // every time can only store storeLen[i][j], we should store the whole path
        // so we ABANDON IT!!!
        // int curMaxPath = 1;
        // for(int i = 0; i < 4; ++i) {
        //     int nextX = x + dx[i];
        //     int nextY = y + dy[i];
        //     if(0 <= nextX && m > nextX && 0 <= nextY && n > nextY && matrix[x][y] < matrix[nextX][nextY]) {
        //         if(-1 != storeLen[nextX][nextY]) {
        //             curMaxPath = max(curMaxPath, 1 + storeLen[nextX][nextY]);
        //         } else {
        //             curMaxPath = max(
        //                 curMaxPath,
        //                 1 + dfs(nextX, nextY, matrix, storeLen, visited)
        //             );
        //         }    
        //     }
        // }
        // return curMaxPath;

        for(int i = 0; i < 4; ++i) {
            int nextX = x + dx[i];
            int nextY = y + dy[i];
            // do not need visited to callback, cause we require ascending path
            if(0 <= nextX && m > nextX && 0 <= nextY && n > nextY && matrix[x][y] < matrix[nextX][nextY]) {
                if(1 != storeLen[nextX][nextY]) {
                    storeLen[x][y] = max(storeLen[x][y], 1 + storeLen[nextX][nextY]);
                } else {
                    storeLen[x][y] = max(
                        storeLen[x][y],
                        1 + dfs(nextX, nextY, matrix, storeLen)
                    );
                }    
            }
        }
        return storeLen[x][y];
    }
};
```

### 3 环路判断
- 1 bfs访问节点的数目超过n本身才能说明有环
- 2 或者dfs能够访问到之前访问过的节点，也说明有环
- 3 不能仅仅通过是否有出度为0的节点来判断是否成环，eg:
[[0,1],[1,1]]
- 4 使用拓扑排序
  - 4.0 当q不空
    - 4.0.1 队列q中存储出度为0的节点
    - 4.0.2 每次从队里出来一个视为访问过
    - 4.0.3 更新出队节点影响的节点的出度，出度为0加入q
  - 4.1 统计出队个数和总结点个数是否相等，不等则意味着有环路
