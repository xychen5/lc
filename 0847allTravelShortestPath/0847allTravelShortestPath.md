## 0847allTravelShortestPath 访问所有节点最短路径

### 1 题目
[https://leetcode.cn/problems/shortest-path-visiting-all-nodes/](https://leetcode.cn/problems/shortest-path-visiting-all-nodes/)

### 2 解题思路
- 1 解题思路：
  - 1.1 使用三元组 <u, mask, dist>表示，当前节点u的mask的搜索情况对应的搜索距离dist，调用bfs即可，但是对于下一个v，我们需要检测： v节点的1 << v | mask这种访问情况是否被访问过
  - 1.2 如何考虑这个方法？
    - 1.2.1 初始化的时候所有节点都加入队里（认为可以从每个节点出发）
    - 1.2.2 bfs的具体过程中，退出条件就是 队首的mask是否标记了所有节点都被访问
  - 1.3 这个方法为什么可以？
    - 一句话：这个方法：利用bfs，按照路径长度从小到大遍历了所有的可能路径（队列初始化有所有的顶点就是这个意思），比如初始化，就是说将长度为0的所有可能路径遍历完成，然后下一层bfs会将所有长度为1的可能路径遍历完成，这个路径的记录方式为mask以及mask对应的终点u，那么由于路径长度是从小到大去遍历的，那么必然保证最终答案是最短路径，
    - 假设用dfs做，那么dfs要考虑所有路径可能，然后去比较，那么会出现枚举的情况，然鹅bfs不会，因为省去所有长度比最短路径大的路径
- 2 总结一下：最关键的有两点
  - 2.1 利用bfs能够将遍历路径的长度从小到大遍历的特性
  - 2.2 使用<到达点，已经遍历的点，目前长度>来记录所有的遍历情况这个trick很聪明

```cpp
// 这里看一个具体 
[[1,2,3],[0],[0],[0]]

// 具体的遍历顺序为：
// 遍历到达的节点 目前遍历的节点 遍历路径的长度
0 00000001 0
1 00000010 0
2 00000100 0
3 00001000 0
1 00000011 1
2 00000101 1
3 00001001 1
0 00000011 1
0 00000101 1
0 00001001 1
2 00000111 2
3 00001011 2
1 00000111 2
3 00001101 2
1 00001011 2
2 00001101 2
0 00000111 3
0 00001011 3
0 00001101 3
3 00001111 4
3 00001111 4


```

```cpp
class Solution {
public:
    int shortestPathLength(vector<vector<int>>& graph) {
        queue<tuple<int, int, int>> curLevel;
        int n = graph.size();
        vector<vector<bool>> seen(n, vector<bool>(1 << n));

        for(int i = 0; i < n; ++i) {
            curLevel.emplace(i, 1 << i, 0);
            seen[i][1 << i] = true;
        }

        while(!curLevel.empty()) {
            auto [node, mask, dist] = curLevel.front();
            // printf("%d %x", node, mask);
            // cout << dist << endl;
            curLevel.pop();
            
            // << not priority to -
            if(mask == (1 << n) - 1) {
                return dist;
            }
            
            for(auto neighbor : graph[node]) {
                int newMask = mask | 1 << neighbor;
                if(!seen[neighbor][newMask]) {
                    curLevel.emplace(neighbor, newMask, dist + 1);
                    seen[neighbor][newMask] = true;
                }
            }
        }

        return -1;
    }
};
```