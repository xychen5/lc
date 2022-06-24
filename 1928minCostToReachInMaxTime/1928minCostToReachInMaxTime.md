## 1928minCostToReachInMaxTime 规定时间内到达终点的最小花费

### 1 题目
[https://leetcode.cn/problems/minimum-cost-to-reach-destination-in-time/](https://leetcode.cn/problems/minimum-cost-to-reach-destination-in-time/)

### 2 解题思路
- 1 解题思路：动态规划：
  - f[t][i]: fees in exact time t to reach node i
  - f[t][i] = min(f[t - time(j, i)][j] + fee[i])

```cpp
class Solution {
public:
    using pii = pair<int, int>; 
    int minCost(int maxTime, vector<vector<int>>& edges, vector<int>& passingFees) {
        // build g
        int n = passingFees.size();
        vector<vector<pii>> g(n);
        for(auto&e : edges) {
            g[e[0]].push_back({e[1], e[2]});
            g[e[1]].push_back({e[0], e[2]});
        }


        // f[t][i]: fees in exact time t to reach node i
        int res = INT_MAX;
        vector<vector<int>> f(maxTime+1, vector<int>(n, INT_MAX));
        f[0][0] = passingFees[0];
        // f[t][i] = min(f[t - time(j, i)][j] + fee[i])
        for(int t = 1; t <= maxTime; ++t) {
            for(int i = 1; i < n; ++i) {
                for(auto& [j, time] : g[i]) {
                    if(t - time >= 0 && f[t-time][j] != INT_MAX) {
                        f[t][i] = min(f[t][i], f[t - time][j] + passingFees[i]);
                    }
                }
            }
        }

        for(int t = 1; t <= maxTime; ++t) {
            res = min(res, f[t][n-1]);
        }

        return res == INT_MAX ? -1 : res;
    }
}
```