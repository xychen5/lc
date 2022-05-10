## 0834sumOfDisInTree 树中距离之和

### 1 题目
[https://leetcode.cn/problems/sum-of-distances-in-tree/](https://leetcode.cn/problems/sum-of-distances-in-tree/)

### 2 解题思路
- 1 解题思路：查看官方解答
  - 1.1 本来思路：对每个点dfs，暴力加
  - 1.2 改进：利用动态规划

```cpp
class Solution {
public:

    vector<vector<int>> g;
    vector<int> ans, sz, dp;
    vector<int> sumOfDistancesInTree(int n, vector<vector<int>>& edges) {
        ans.resize(n, 0);
        sz.resize(n, 0);
        dp.resize(n, 0);

        // construct a graph
        g.resize(n, {});
        for(auto e : edges) {
            g[e[0]].push_back(e[1]);
            g[e[1]].push_back(e[0]);
        }
        
        // o(n**2)
        // vector<int> res(n, 0);
        // // do dfs for each node
        // for(int i = 0; i < n; ++i) {
        //     vector<bool> mark(n, false);
        //     int depth = 0;
        //     dfs(i, i, mark, res, g, depth);
        // }

        // return res;

        // dp:
        // 定义 \textit{dp}[u]dp[u] 表示以 uu 为根的子树，它的所有子节点到它的距离之和
        // 同时定义 \textit{sz}[u]sz[u] 表示以 uu 为根的后代的节点数量，包含自己    
        dfs1(0, -1);
        dfs2(0, -1);
            

        return ans;
    }

    void dfs1(int u, int f) {
        sz[u] = 1;
        dp[u] = 0;
        for(auto v : g[u]) {
            if(v != f) {
                dfs1(v, u);
                dp[u] += dp[v] + sz[v];
                sz[u] += sz[v];
            }
        }
    }

    void dfs2(int u, int f) {
        ans[u] = dp[u];
        for (auto& v: g[u]) {
            if (v != f) {
                // 为后继v做变换前的值
                int pu = dp[u], pv = dp[v];
                int su = sz[u], sv = sz[v];
 
                // 为v做变换
                dp[u] -= dp[v] + sz[v];
                sz[u] -= sz[v];
                dp[v] += dp[u] + sz[u];
                sz[v] += sz[u];
                
                dfs2(v, u);
                
                // 恢复变换
                dp[u] = pu, dp[v] = pv;
                sz[u] = su, sz[v] = sv;
            }
        }
    }

    void dfs(int st, int u, vector<bool>& mark, vector<int>& res, vector<vector<int>>& g, int& depth) {
        mark[u] = true;
        for(auto v : g[u]) {
            if(!mark[v]) {
                ++depth;
                res[st] += depth;
                dfs(st, v, mark, res, g, depth);
                --depth;
            }
        }

    }
};
```