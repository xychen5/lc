## 0778 泳池游泳上升泳池

### 1 题目
[https://leetcode-cn.com/problems/swim-in-rising-water/](https://leetcode-cn.com/problems/swim-in-rising-water/)

### 2 解题思路
- 1 普通思路1
  - 对于每一个水位，采用bfs算法看是否能够到达，那么对于水位可以用二分法加速o(logn),bfs要o(n^2)，所以o(n^2logn)
- 2 普通思路2
  - **仔细理解改题目，问的是a和b什么时候能够连通的问题？那么自然就想到并查集**，反复说一句哈：并查集并的子树，查的是子树的root
  - 对于水位从低到高遍历，每次更新和当前水位相同高度的格子(注意，题目说的非常清除，所有的格子的值在0到n^2，且不同)和周围联通情况
  - 每次更新完连通情况我们看一下是否能够使得左上角和右下角的两个节点相互连通即可。

```cpp
class Solution {
public:
    int find(vector<int>& parent, int x) {
        while(x != parent[x]) {
            parent[x] = parent[parent[x]];
            x = parent[x];
        }

        return x;
    }

    bool unionMerge(vector<int>& parent, int x, int y) {
        int findX = find(parent, x);
        int findY = find(parent, y);
        if(findX != findY) {
            parent[findX] = findY
            return true;
        }
        return false;
    }

    int swimInWater(vector<vector<int>>& grid) {
        // for each threshold, maintain a unionFind
        // everytime increase thres, we modify the connection of unionFind
        int n = grid.size();

        if(n == 1) {
            return 0;
        }

        vector<int> parent(n * n);
        for(int i = 0; i < n * n; ++i) {
            parent[i] = i;
        }

        // Each value grid[i][j] is unique.
        vector<vector<int>> elevationToIdx(n * n, vector<int>(n));
        for(int i = 0; i < n; ++i) {
            for(int j = 0; j < n; ++j) {
                elevationToIdx[grid[i][j]][0] = i;
                elevationToIdx[grid[i][j]][1] = j;
            }
        }

        vector<vector<int>> moves = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
        for(int thres = 0; thres < n * n; ++thres) {
            // when the rain rise, process the exact the same height grid
            int tarX = elevationToIdx[thres][0];
            int tarY = elevationToIdx[thres][1];
            for(auto deltaXY : moves) {
                int newX = tarX + deltaXY[0];
                int newY = tarY + deltaXY[1];
                if(newX >= 0 && newY >= 0 && newX < n && newY < n && grid[newX][newY] <= thres) {
                    // cout << newX << " " << newY << "  ->" << thres <<endl;
                    unionMerge(parent, grid[newX][newY], grid[tarX][tarY]);
                    if(find(parent, grid[0][0]) == find(parent, grid[n - 1][n - 1])) {
                        return thres;
                    }
                }
            }
        }
        return n*n;
    }
}
```
