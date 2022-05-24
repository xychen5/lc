## 0675golfCutTree 高尔夫砍树

### 1 题目
[https://leetcode.cn/problems/cut-off-trees-for-golf-event/](https://leetcode.cn/problems/cut-off-trees-for-golf-event/)

### 2 解题思路
- 1 解题思路：
  - 1.1 使用优先队列将所有树从小到高排序，存为trees
  - 1.2 每次从trees中取出一个树，对其进行bfs直到找到trees的下一个目标
- 2 bfs思路：
  - 2.1 queue初始化为起点
  - 2.2 对于queue中所有元素，加入当前queue的所有后继，加入以后就把元素置为visited
  - 2.3 进入下一个level
- 3 为什么加入的过程中就要吧元素置为vis？因为：假设1层有a,b, 2层有c，c为ab的邻居，那么遍历第1层的时候，对于ab的后继，到a，加入c，若不置为vis，则b会再加入一遍，导致bfs很慢！


```cpp
class Solution {
public:
    int m;
    int n;
    
    int dx[4] = {1, 0, -1, 0};
    int dy[4] = {0, -1, 0, 1};
    int dirs[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    
    int cutOffTree(vector<vector<int>>& forest) {
        // get all trees
        m = forest.size();
        n = forest[0].size();

        auto cmp = [](const pair<pair<int, int>, int>& a, const pair<pair<int, int>, int>& b) {
            return a.second > b.second;
        };
        priority_queue<pair<pair<int, int>, int>, vector<pair<pair<int, int>, int>>, decltype(cmp)>trees (cmp);

        for(int i = 0; i < m; ++i) {
            for(int j = 0; j < n; ++j) {
                if(forest[i][j] > 1) {
                    trees.push({{i, j}, forest[i][j]});
                }
            }
        }


        int curX = 0, curY = 0;
        int tarX = -1, tarY = -1;
        int res = 0;
        while(!trees.empty()) {
            auto tree = trees.top();
            trees.pop();

            tarX = tree.first.first;
            tarY = tree.first.second;
            
            // judge if we can walk to x, y
            // cout << "from/to: " << curX << "," << curY << " -> " << tarX << "," << tarY << endl; 
            if(!tryWalk(forest, curX, curY, tarX, tarY, res)) {
                return -1;
            } else {
                // cut tarX, tarY
                forest[tarX][tarY] = 1;
                curX = tarX;
                curY = tarY;
            }
            // auto step = bfs(forest, curX, curY, tarX, tarY);
            // if(-1 == step) {
            //     return -1;
            // } else {
            //     // cut tarX, tarY
            //     forest[tarX][tarY] = 1;
            //     res+= step;
            //     curX = tarX;
            //     curY = tarY;
            // }
        }

        return res;
    }

    int bfs(vector<vector<int>>& forest, int sx, int sy, int tx, int ty) {
    if (sx == tx && sy == ty) {
        return 0;
    }

    int row = forest.size();
    int col = forest[0].size();
    int step = 0;
    queue<pair<int, int>> qu;
    vector<vector<bool>> visited(row, vector<bool>(col, false));         
    qu.emplace(sx, sy);
    visited[sx][sy] = true;
    while (!qu.empty()) {
        step++;
        int sz = qu.size();
        for (int i = 0; i < sz; ++i) {
            auto [cx, cy] = qu.front();
            qu.pop();
            for (int j = 0; j < 4; ++j) {
                int nx = cx + dirs[j][0];
                int ny = cy + dirs[j][1];
                if (nx >= 0 && nx < row && ny >= 0 && ny < col) {
                    if (!visited[nx][ny] && forest[nx][ny] > 0) {
                        if (nx == tx && ny == ty) {
                            return step;
                        }
                        qu.emplace(nx, ny);
                        visited[nx][ny] = true;
                    }
                }
            }
        }
    }
    return -1;
}


    // using bfs from <curX, curY> to <tarX, tarY>, the depth of bfs should be the distance
    bool tryWalk(vector<vector<int>>& forest, int curX, int curY, int tarX, int tarY, int& res) {
        // bfs
        queue<pair<int, int>> curLevel;
        vector<vector<int>> vis(m, vector<int>(n, false));
        
        curLevel.push({curX, curY});
        vis[curX][curY] = true;

        int depth = 0;
        while(!curLevel.empty()) {
            // queue<pair<int, int>> nextLevel;

            // while(!curLevel.empty()) {
            int curLevelSize = curLevel.size();
            while(curLevelSize-- > 0) {
                auto curNode = curLevel.front();

                curLevel.pop();
                if(curNode == pair<int, int>{tarX, tarY}) {
                    // update res
                    res += depth;
                    return true;
                }
                for(int mv = 0; mv < 4; ++mv) {
                    int nextX = curNode.first + dx[mv];
                    int nextY = curNode.second + dy[mv];

                    if(0 <= nextX && nextX < m && 0 <= nextY && nextY < n && 0 != forest[nextX][nextY] && !vis[nextX][nextY]) {
                        curLevel.push({nextX, nextY});
                        vis[nextX][nextY] = true;
                        // cout << "nextNode: " << curNode.first << "," << curNode.second << endl; 
                    }
                }
            }
            // curLevel = std::move(nextLevel);
            ++depth;
        }
        return false;
    }
};

```