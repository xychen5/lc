## 2065maxPathValueWithinMaxtime 规定时间内路径的最大价值

### 1 题目
[https://leetcode.cn/problems/maximum-path-quality-of-a-graph/](https://leetcode.cn/problems/maximum-path-quality-of-a-graph/)

### 2 解题思路
- 1 解题思路：
  - 1.1 考虑一个问题：如何遍历所有路径？那不就是回溯吗，对于u，尝试v进入下一个dfs，然后dfs完成v以后尝试下一个v，将之前的v设置为未访问即可
  - 1.2 那么什么时候更新结果？只要v == 0并且剩余时间 >= 0,就可以更新结果
  - 1.3 那什么时候返回？时间小于0了就返回啊
  - 1.4 有个问题，要求路径中节点的值不被重复加？那不就是回溯过程中，如果当前顶点v被用过，那么直接从v进入dfs，就不去将当前v的价值考虑进去就行，而且也不需要去标记它没被访问过，因为它是已经被访问过的节点（走回头路了嘛），因为只有一个地方可以回溯，那么就是进入v且v此时没有被访问过然后dfs完成以后可以将v置为未访问

```cpp
class Solution {
public:
    long long n;
    using pii = pair<long long, long long>;

    void dfs(unordered_map<long long, vector<pii>>& g, long long st, long long leftTime, vector<int>& values, vector<bool>& used, long long& res, long long& curValue) {
        // even the time cost least node not able to reach
        // cout << "at node/lefttime" << st << "/" << leftTime << endl;

        if(0 == st && leftTime >= 0) {
            res = max(res, curValue);
        }

        if(leftTime < 0) {
            return ;
        }

        for(auto& [v, w] : g[st]) {

            if(!used[v]) {
                // cout << "u->v: " << st << "->" << v << endl;
                used[v] = true;
                curValue += values[v];

                dfs(g, v, leftTime - w, values, used, res, curValue);

                // cout << "use new node: maxValue is : " << res << endl;
                curValue -= values[v];
                used[v] = false;
            } else {

                dfs(g, v, leftTime - w, values, used, res, curValue);
                // cout << "use new node: maxValue is : " << res << endl;
            }
        }
    }

    int maximalPathQuality(vector<int>& values, vector<vector<int>>& edges, int maxTime) {
        n =  values.size();

        unordered_map<long long, vector<pii>> g(n);
        for(auto& e : edges) {
            long long u = e[0];
            long long v = e[1];
            long long w = e[2];

           g[u].push_back({v, w});
           g[v].push_back({u, w});
        }
        
        // smallest weighted edge first
        for(auto& [node, neighbors] : g) {
            sort(neighbors.begin(), neighbors.end(), [](const pii& a, const pii& b) {
                return a.second < b.second;
            });
        }
        vector<bool> vecBool(n, false);
        vecBool[0] = true;

        long long res = INT_MIN;
        long long curValue = values[0];

        if(0 == g[0].size()) {
            return values[0];
        }

        dfs(g, 0, maxTime, values, vecBool, res, curValue);
        return res;
    }
};
```