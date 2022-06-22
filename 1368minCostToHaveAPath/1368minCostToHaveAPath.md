## 1368minCostToHaveAPath 使网格图至少有一条有效路径的最小代价

### 1 题目
[https://leetcode.cn/problems/minimum-cost-to-make-at-least-one-valid-path-in-a-grid/](https://leetcode.cn/problems/minimum-cost-to-make-at-least-one-valid-path-in-a-grid/)

### 2 解题思路
- 1 解题思路：
  - 1.1 说明思路：构图，正确方向，那么u到v的距离为0，否则为1
    - 那么不就求从00到mn的最短路吗？dijstra可以做
  - 1.2 但是你非要用bfs：
    - 解决办法也简单，此时决定一个点v是否进入下一次bfs不再是vis数组了，而是：用dis[u]表示从0到u的距离，然后它的邻居v们，是否进入下一次bfs，是由：dis[v] < dis[u] + g[u][v].weight，也就是如果v被松弛了，进入下一次bfs，这个和dijstra思想基本上是一样的，但是可能有很多重复计算
  - 1.3 这个叫01bfs，也就是说，队列里的点，到原点的距离，要么是dis，要么是dis+1，当然是使用deque维护，g[u][v].weight如果为1，从队尾进入，否则从对首进入，但是不这么做貌似也行哈哈哈，就用普通的队列即可

```cpp
class Solution {
public:
    int dx[4] = {1,-1, 0, 0};
    int dy[4] = {0, 0, 1, -1};
    int m, n;

    int bfs(vector<vector<pair<int, int>>>& g) {
        // start from 0, search first 0 wighted edges
        deque<pair<int, int>> curLevel; // <node, dis from 0,0>
        curLevel.push_front({0, 0});
        vector<bool> vis(m*n); 
        vector<int> disV(m*n, INT_MAX); 
        disV[0] = 0;
        int tar =  m * n - 1;
        
        
        int res = INT_MAX;
        while(0 != curLevel.size()) {
            // cout << "---" << endl;
            int curLevelSize = curLevel.size();
            while(curLevelSize-- > 0) {
                auto curNode = curLevel.front();
                curLevel.pop_front();
                // cout << curNode.first << "-> dis: " << curNode.second << endl;

                int curDis = disV[curNode.first];
                for(auto& [neighbor, dis] : g[curNode.first]) {
                    // cout << "from/to: " << curNode.first << "/ " << neighbor << endl;
                    int newDis = curDis + dis;
                    if(newDis < disV[neighbor]) {
                        curLevel.push_back({neighbor, dis});
                        // if(dis == 0) {
                        //     curLevel.push_front({neighbor, 0});
                        // } else {
                        //     curLevel.push_back({neighbor, 1});
                        // }
                        disV[neighbor] = newDis;
                    }
                    if(neighbor == tar) { 
                        res = min(res, disV[tar]); 
                    }
                }
            }
        }

        return res == INT_MAX ? 0 : res;
    }

    int minCost(vector<vector<int>>& grid) {
        m = grid.size();
        n = grid[0].size();
        vector<vector<pair<int, int>>> g(m * n);

        for(int i = 0; i < m; ++i) {
            for(int j = 0; j < n; ++j) {
                int curNode = j + i * n;
                // cout << "i/j" << i << " " << j << endl;
                for(int mvIdx = 0; mvIdx < 4; ++mvIdx) {
                    int nextI = i + dy[mvIdx];
                    int nextJ = j + dx[mvIdx];
                    if(0 <= nextI && nextI < m && 0 <= nextJ && nextJ < n) {
                        int nextNode = nextI * n + nextJ;
                        // cout << mvIdx << endl;
                        if(grid[i][j] == mvIdx + 1) {
                            g[curNode].push_back({nextNode, 0});
                            // cout << "to " << nextNode << " = " << 0 << " ";
                        } else {
                            g[curNode].push_back({nextNode, 1});
                            // cout << "to " << nextNode << " = " << 1 << " ";
                        }
                        // cout << "\n";
                    }
                }
                sort(g[curNode].begin(), g[curNode].end(), 
                    [](const pair<int, int>& a, const pair<int, int>& b) {
                        return a.second < b.second;
                });
            }
        }

        // bfs to get dis
        return bfs(g);
    }
}
```