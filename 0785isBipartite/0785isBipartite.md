## 0785 是否二分图

### 1 题目
[https://leetcode-cn.com/problems/is-graph-bipartite/](https://leetcode-cn.com/problems/is-graph-bipartite/)

### 2 解题思路
- 1 普通思路
使用bfs遍历，考虑奇偶层级，奇层级为节点集合A，偶层级为节点集合B，最后扫描一遍所有的边，判断是否有边位于AB而不是横跨AB的，
有的话返回false，不然则true；
同时注意邻接表的判空，所有边个数为1为空的图，是可以二分的哦！
```cpp
class Solution {
public:
    bool isBipartite(vector<vector<int>>& graph) {
        int n = graph.size();
        
        int edgeNum = 0;
        for(int u = 0; u < n; ++u) {
            for(int v = 0; v < graph[u].size(); ++v) {
                ++edgeNum;
            }
        }
        if(edgeNum == 0) return true;

        // if not connected, return false
        vector<int> stack = {0};
        // vector<bool> vis(graph.size(), false);
        // vis[0] = true;
        // int visCnt = 1;
        // // dfs to check if connected
        // while(!stack.empty()) {
        //     int top = stack.back();
        //     bool allVisited = true;
        //     for(int i = 0; i < graph[top].size(); ++i) {
        //         if(!vis[graph[top][i]]) {
        //             stack.emplace_back(graph[top][i]);
        //             vis[graph[top][i]] = true;
        //             allVisited = false;
        //             visCnt++;
        //             break;
        //         }
        //     }
        //     if(allVisited) {
        //         stack.pop_back();
        //     }
        // }

        // if(visCnt != n) return false;

        // bfs to judge biPartitable
        deque<int> q = {};


        vector<bool> vis2(graph.size(), false);
            unordered_set<int> biPart1 = {};
            unordered_set<int> biPart2;
            deque<int> level = {};
        int bfsNum = 0;
        
        while(bfsNum != n) {        

            for(int i = 0; i < n; ++i) {
                if(!vis2[i]) {
                    q.emplace_back(i);
                    level.emplace_back(0);
                    biPart1.insert(i);
                    ++bfsNum;
                    vis2[i] = true;
                    break;
                }
            }
            while(!q.empty()) {
                int front = q.front();
                for(int i = 0; i < graph[front].size(); ++i) {
                    if(!vis2[graph[front][i]]) {
                        q.emplace_back(graph[front][i]);
                        ++bfsNum;
                        level.emplace_back(level.front() + 1);
                        if(level.front() % 2 == 0) {
                            biPart2.insert(graph[front][i]);
                        } else {
                            biPart1.insert(graph[front][i]);
                        }
                        vis2[graph[front][i]] = true;          
                    }
                }
                q.pop_front();
                level.pop_front();
            }
            // for(auto& i : biPart1) {
            //     std::cout << i << " ";
            // }
            // cout << endl;
            // for(auto& i : biPart2) {
            //     std::cout << i << " ";
            // }
            // cout << endl;
            
            for(int u = 0; u < n; ++u) {
                for(int v = 0; v < graph[u].size(); ++v) {
                    if((biPart2.count(u) == 1 && biPart2.count(graph[u][v]) == 1) || \
                    (biPart1.count(u) == 1 && biPart1.count(graph[u][v]) == 1)) {
                        return false;
                    }
                }
            }
        }


        return true;
    }
}
```

### 多写了
使用dfs判断整个图是否连通：
```cpp
        // if not connected, return false
        vecctor<int> stack = {0};
        vector<bool> vis(graph.size(), false);
        vis[0] = true;
        int visCnt = 1;
        // dfs to check if connected
        while(!stack.empty()) {
            int top = stack.back();
            bool allVisited = true;
            for(int i = 0; i < graph[top].size(); ++i) {
                if(!vis[graph[top][i]]) {
                    stack.emplace_back(graph[top][i]);
                    vis[graph[top][i]] = true;
                    allVisited = false;
                    visCnt++;
                    break;
                }
            }
            if(allVisited) {
                stack.pop_back();
            }
        }

        if(visCnt != n) return false;
```