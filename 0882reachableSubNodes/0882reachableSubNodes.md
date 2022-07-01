## 0882reachableSubNodes 细分图中的可到达结点

### 1 题目
[https://leetcode.cn/problems/reachable-nodes-in-subdivided-graph/](https://leetcode.cn/problems/reachable-nodes-in-subdivided-graph/)

### 2 解题思路
- 1 解题思路：类似的题目：https://leetcode.cn/problems/partition-array-into-two-arrays-to-minimize-sum-difference/
  - 1.1 dijstra算出来到所有顶点的距离
  - 1.2 最终能到达的节点由两部分构成：
    - a : 来自原始节点，要求距离小于maxMoves
    - b : 来自细分节点：很简单，对于每个边uv，从u和v出发，分别还能前进maxMoves - dis[u], maxMoves - dis[v]，这就是细分节点的个数
      - 需要注意两点：1，maxMoves不一定比dis[u]大；2，若从u和v出发加起来的细分节点数大于uv之间所有的细分节点，记得clamp到uv之间的细分节点个数
- 2 回顾dijstra算法：
```cpp
unordered_map<int, unordered_map<int, int>> g;
        
        auto cmp = [](const pair<int, int>& a, const pair<int, int>& b) {
            return a.first > b.first;
        };
        priority_queue<pair<int, int>, vector<pair<int, int>>, decltype(cmp)> pq(cmp);

        for(auto& e : edges) {
            int u = e[0];
            int v = e[1];
            int w = e[2];
            g[u][v] = w+1;
            g[v][u] = w+1;
        }

        // init dis
        vector<int> disRes(n, INT_MAX);
        map<int, bool> visited;
        visited[0] = true;
        disRes[0] = 0;
        pq.push({0, 0});

        // contain 0 itSelf!

        int res = 0; 


        // dijstra
        while(pq.size() > 0) {
            auto node = pq.top();
            pq.pop();
            int u = node.second;
            int dis = node.first;

            // for disRes[u], every relax will push a new pair, so we need
            // to pass all old relaxed value
/**
 * 
 * eg: [[2,3,4],[1,3,9],[0,2,4],[0,1,1]]
 * 对于上图的dijstra的距离表的松弛过程为：
0 2 2147483647 2147483647 
0 2 5 2147483647 
0 2 5 12 // 这里，第一次松弛来自节点1，
0 2 5 10 // 第二次来自节点2，那么这两个松弛结果都会记录在pq里面，为了让后面
         // pq遍历到 0到3距离为12的时候能pass掉，我么你需要将12和  10(存于距离中)做比较，
         // 就可以直到12是第一次松弛的结果，10才是最终松弛的结果，否则如果还有其他节点，
         // 那么12会在10松弛完其他节点接着松弛，那就错了
         // 于是这个continue是必要的
*/
            if(disRes[u] < dis) {
                continue;
            }
            visited[u] = true;
            disRes[u] = dis;
            
            res += (disRes[u] <= maxMoves);

            // relax nodes by u
            for(auto& neighbor : g[u]) {
                int v = neighbor.first;
                int w = neighbor.second;
                // v has been proceed!
                if(!visited[v] && disRes[v] > disRes[u] + g[u][v]) {
                    disRes[v] = disRes[u] + g[u][v];
                    pq.push({disRes[v], v});
                    // print(disRes);
                }
           }
};

```


```cpp
class Solution {
public:
    int reachableNodes(vector<vector<int>>& edges, int maxMoves, int n) {
        unordered_map<int, unordered_map<int, int>> g;
        
        auto cmp = [](const pair<int, int>& a, const pair<int, int>& b) {
            return a.first > b.first;
        };
        priority_queue<pair<int, int>, vector<pair<int, int>>, decltype(cmp)> pq(cmp);

        for(auto& e : edges) {
            int u = e[0];
            int v = e[1];
            int w = e[2];
            g[u][v] = w+1;
            g[v][u] = w+1;
        }

        // init dis
        vector<int> disRes(n, INT_MAX);
        map<int, bool> visited;
        visited[0] = true;
        disRes[0] = 0;
        pq.push({0, 0});
        // disRes[0] = 0;
        // for(auto& neighbor : g[0]) {
        //     int to = neighbor.first;
        //     int w = neighbor.second
        //     disRes[to] = w;
        //     pq.push({w, to});
        // }

        // contain 0 itSelf!
        int res = 0; 


        // dijstra
        while(pq.size() > 0) {
            auto node = pq.top();
            pq.pop();
            int u = node.second;
            int dis = node.first;

            // for disRes[u], every relax will push a new pair, so we need
            // to pass all old relaxed value
            if(disRes[u] < dis) {
                continue;
            }
            visited[u] = true;
            disRes[u] = dis;
            
            res += (disRes[u] <= maxMoves);

            // relax nodes by u
            for(auto& neighbor : g[u]) {
                int v = neighbor.first;
                int w = neighbor.second;
                // v has been proceed!
                if(!visited[v] && disRes[v] > disRes[u] + g[u][v]) {
                    disRes[v] = disRes[u] + g[u][v];
                    pq.push({disRes[v], v});
                    print(disRes);
                }
            }
        }

        // count sub nodes
        for(auto& e : edges) {
            int u = e[0];
            int v = e[1];
            int w = e[2];
            int curSubNodes = 0;
            if(visited[u]) {
                curSubNodes += max(maxMoves - disRes[u], 0);
            }
            if(visited[v]) {
                curSubNodes += max(maxMoves - disRes[v], 0);
            }
            curSubNodes = min(curSubNodes, w);
            // cout << "curSub/edge: " << curSubNodes << " " << "e: " << u << "->" << v << endl;
            res += curSubNodes;
        }


        return res;
    }
    void print(vector<int>& dis) {
        for(int i = 0; i < dis.size(); ++i) {
            cout <<dis[i] << " ";
        }cout << "\n";
    }
};
```