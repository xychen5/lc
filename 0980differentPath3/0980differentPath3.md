## 0980differentPath3 不同路径3

### 1 题目
[https://leetcode.cn/problems/unique-paths-iii/](https://leetcode.cn/problems/unique-paths-iii/)

### 2 解题思路
- 1 解题思路：
  - 回溯，就暴力搜索就行，只需要考虑两个问题：
  - 什么时候进入下一个位置？没有出界，没有被访问过，不是障碍物
  - 什么时候返回？如果到edXY的时候，已经把所有0访问过，则认为找到一个方案，返回1，如果到edXY访问0的个数没达到总个数，则认为没找到，则返回0，最后将所有的返回值加起来就行

```cpp
class Solution {
public:
    int m,n;
    int dx[4] = {1, 0, -1, 0};
    int dy[4] = {0, 1, 0, -1};
    int tarSum = 0;
    int edX, edY;

    int backTrack(vector<vector<int>>& grid, vector<vector<bool>>& vis, int x, int y, int curSum) {
        if(x == edX && y == edY) {
            // cout << "yes: " << curSum << endl;
            if(curSum == tarSum) {
                return 1;
            } else {
                return 0;
            }
        }

        int ways = 0;
        for(int mv = 0; mv < 4; ++mv) {
            int nextX = x + dx[mv];
            int nextY = y + dy[mv];
            if(0 <= nextX && nextX < m && 0 <= nextY && nextY < n && \
                !vis[nextX][nextY] && \
                -1 != grid[nextX][nextY]
            ) {
                vis[nextX][nextY] = true;
                ways += backTrack(grid, vis, nextX, nextY, curSum + 1);
                vis[nextX][nextY] = false;
            }
        }

        return ways;
    }
    

    int uniquePathsIII(vector<vector<int>>& grid) {
        m = grid.size();
        n = grid[0].size();

        // just backTracking all 
        vector<vector<bool>> vis(m, vector<bool>(n, false));
        
        int x, y;
        for(int i = 0; i < m; ++i) {
            for(int j = 0; j < n; ++j) {
                if(1 == grid[i][j]) {
                    x = i; y = j;
                } else if(2 == grid[i][j]) {
                    edX = i; edY = j;
                    ++tarSum;
                } else  {
                    tarSum += (grid[i][j] == 0);
                }
            }
        }
        // cout << tarSum << endl;

        int curSum = 0;
        vis[x][y] = true;
        return backTrack(grid, vis, x, y, curSum);
    }
};
```
