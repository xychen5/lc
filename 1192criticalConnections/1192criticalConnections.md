## 1192criticalConnections 查找集群内的「关键连接」

### 1 题目
[https://leetcode.cn/problems/critical-connections-in-a-network/](https://leetcode.cn/problems/critical-connections-in-a-network/)

### 2 解题思路
- 1 解题思路：使用tarjan算法：求割点和割边
  - 算法实现参考：https://www.cnblogs.com/collectionne/p/6847240.html
  - 一句话概括算法：dfsNo[i]: i号节点dfs的顺序， low[i]：i号节点以及其子树中所有的搜索节点仅通过 回边 能够到达的节点的dfs序号(回边：非搜索树上的边)，若对于边u->v,有：dfsNo[u] < low[v]，说明v通过回边无法到达u之前的节点，那么说明uv为割边，必须是小于，因为若果回边能回到u，且dfsNo[u] == low[v]，则说明uv不是割边！   
  - 同理，dfsNo[u] <= low[v]可以得出u为割点，之所以有等于号，是因为u是可以被割的


```cpp
class Solution {
public:
    
    void Tarjan(vector<vector<int>>& g, int st, vector<int>& parent, vector<int>& low, vector<int>& dfsNo, int no, set<int>& cutPoints, vector<vector<int>>& cutEdges) {
        int rootChildNum = 0;
        low[st] = dfsNo[st] = no;
        for(auto neighbor : g[st]) {
            // if(parent[neighbor] == st) {
            //     continue;
            // }
            if(-1 != dfsNo[neighbor]) { // st -> neighbor 是一条回边
                if(parent[st] != neighbor) { // 且不在搜索子树内
                    low[st] = min(low[st], dfsNo[neighbor]); // 更新low[st]为所有能通过回边到达的最小的dfsNo
                }
            } else {
                parent[neighbor] = st;
                ++rootChildNum;
                
                ++no;
                // cout << "u/v " << st<<"/"<<neighbor << " " << no << endl;
                Tarjan(g, neighbor, parent, low, dfsNo, no, cutPoints, cutEdges);
                low[st] = min(low[st], low[neighbor]); // 更新为所有搜索子树节点中能够通过回边到达的最小的dfsNo
                
                if(-1 != parent[st] && dfsNo[st] <= low[neighbor]) {
                    cutPoints.insert(st);
                }
                if(dfsNo[st] < low[neighbor]) {
                    cutEdges.emplace_back(vector<int>{st, neighbor});
                }
            }
        }
        if(parent[st] == -1 && rootChildNum >= 2) {
            cutPoints.insert(st);
        }
    }

    vector<vector<int>> criticalConnections(int n, vector<vector<int>>& connections) {
        // build graph
        vector<vector<int>> g(n);
        for(auto e : connections) {
            g[e[0]].push_back(e[1]);
            g[e[1]].push_back(e[0]);
        }

        vector<int> dfsNo(n, -1);
        vector<int> low(n, -1); // low[i]：i号节点以及其子树中所有的搜索节点仅通过 回边 能够到达的节点的dfs序号(回边：非搜索树上的边)
        vector<int> parent(n, -1); // 记录搜索树
        int no = 0;

        set<int> cutPoints;
        vector<vector<int>> cutEdges;
        dfsNo[0] = 0;
        Tarjan(g, 0, parent, low, dfsNo, no, cutPoints, cutEdges);
        for(auto i : cutPoints) {
            cout << i << " ";
        }
        cout << "low: ";
        for(auto i : low) {
            cout << i << " ";
        }
        cout << "\ndfsNo: ";
        for(auto no : dfsNo) {
            cout << no << " ";
        }
        return cutEdges;
    }
};

```