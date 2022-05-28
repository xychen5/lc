## 0864getAllKeys 获取所有钥匙的最短路径

### 1 题目
[https://leetcode.cn/problems/shortest-path-to-get-all-keys/submissions/](https://leetcode.cn/problems/shortest-path-to-get-all-keys/submissions/)

### 2 解题思路
- 1 解题思路：
  - 1.1 首先考虑使用bfs,因为从起点到终点，bfs的遍历深度就等于最短路径，那么有一个问题对于：["@a.","bAB"]这样的地图如何知道经过a和b的最短路呢？
  - 1.2 也就是这个bfs会走"回头路"，但是又不是完全的回头路，因为走路的人的状态发生了变化，也就是手里多了钥匙，也就是bfs的变种：带状态(压缩)的bfs
  - 1.3 那么就很容易想到，原来最普通的bfs判断是否走过就是只用了位置xy，那么现在我们多增加一个信息，也就是拥有的钥匙，那么该点没有走过变成了什么呢？那就是：该点位置没有走过，或者当前的拥有钥匙的状态在该点没有出现过
  - 1.4 有了1.3我们就很容易知道，用什么数据结构去存顶点是否被访问啦： map<pair<int, int>, set<int>> seenKey; 左边是该点的位置，右边是该点所经历过的所有钥匙的集合
  - 1.5 还需要考虑如何记录路径长度：map<pair<pair<int, int>, int>, int> dis; 很显然，左侧是<xy,key>，右侧代表了xy在key情况下的路径长度
  - 1.6 考虑一个具体["@a.","bAB"]的例子即可：
```log
cur: 0,0 -> 000000
next: 0,1 charis a-> 000001
next: 1,0 charis b-> 000010
cur: 0,1 -> 000001
next: 0,2 charis .-> 000001
next: 1,1 charis A-> 000001
next: 0,0 charis @-> 000001
cur: 1,0 -> 000010
next: 0,0 charis @-> 000010
cur: 0,2 -> 000001
cur: 1,1 -> 000001
next: 1,0 charis b-> 000011
```
  

```cpp
class Solution {
public:

    int m, n;
    int dx[4] = {-1, 0, 1, 0};
    int dy[4] = {0, 1, 0, -1};

    int shortestPathAllKeys(vector<string>& grid) {
        m = grid.size();
        n = grid[0].size();
        int i = 0;
        int j = 0;
        int keyNum = 0;
        int stX = -1, stY = -1;
        for(auto& s : grid) {
            j = 0;
            for(auto& c : s) {
                if('a' <= c && c <= 'f') {
                    ++keyNum;
                }
                if('@' == c) {
                    stX = i;
                    stY = j;
                }
                ++j;
            }
            ++i;
        }
        
        int tarKey = 0;
        for(int i = 0; i < keyNum; ++i) {
            tarKey = tarKey | (1 << i);
        };

        // cout << "tarKey is : " << bitset<8>(tarKey) << " | st: " << stX << " " << stY << endl;
        return bfs(grid, stX, stY, tarKey);
    }

    bool canWalk(vector<string>& grid, int x, int y, int keyInfo) {
        if('A' <= grid[x][y] && grid[x][y] <= 'F') {
            int keyNum = grid[x][y] - 'A';
            return ((keyInfo >> keyNum) & 1) != 0;
        } 
        if('#' == grid[x][y]) {
            return false;
        }

        return true;
    }

    int bfs(vector<string>& grid, int stX, int stY, int tarKey) {
        queue<pair<pair<int, int>, int>> curLevel; // xy, key
        curLevel.push({{stX, stY}, 0});
        map<pair<pair<int, int>, int>, int> dis; // xy, key -> pathLen
        map<pair<int, int>, set<int>> seenKey; // xy -> key
        dis[{{stX, stY}, 0}] = 0;
        seenKey[{stX, stY}] = {0};

        int res = 0;

        while(!curLevel.empty()) {
            int curSize = curLevel.size();
            while(curSize-- > 0) {
                auto curNode = curLevel.front();
                int curDis = dis[curNode];
                int x = curNode.first.first;
                int y = curNode.first.second;
                int curKey = curNode.second;

                curLevel.pop();
                // cout << "cur: " << x << "," << y << " -> " << bitset<6>(curKey) << endl;
                for(int mv = 0; mv < 4; ++mv) {
                    int nextX = x + dx[mv];
                    int nextY = y + dy[mv];
                    pair<int, int> nextNode = {nextX, nextY};
                    // nextNode not explored or has new keys
                    if(0 <= nextX && nextX < m && 0 <= nextY && nextY < n && \
                         canWalk(grid, nextX, nextY, curKey) && \
                        (0 == seenKey.count(nextNode) || 0 == seenKey[nextNode].count(curKey))) {
                        int nextKey = curKey;
                        if('a' <= grid[nextX][nextY] && grid[nextX][nextY] <= 'f') {
                            nextKey = curKey | (0x1 << (grid[nextX][nextY] - 'a'));
                        }
                        
                        curLevel.push({{nextX, nextY}, nextKey});
                        seenKey[{nextX, nextY}].insert(nextKey);
                        dis[{nextNode, nextKey}] = dis[curNode] + 1;
                        
                        // cout << "next: " << nextX << "," << nextY << " charis "<< grid[nextX][nextY] << "-> " << bitset<6>(nextKey) << endl;
                        if(nextKey == tarKey) {
                            return dis[curNode] + 1;
                        }
                    }
                }
            }
        }
        return -1;
    }
};

```