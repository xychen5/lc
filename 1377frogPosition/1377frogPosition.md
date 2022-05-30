## 1377frogPosition T秒后青蛙的位置

### 1 题目
[https://leetcode.cn/problems/frog-position-after-t-seconds/](https://leetcode.cn/problems/frog-position-after-t-seconds/)

### 2 解题思路
- 1 解题思路：
  - 1.1 首先考虑使用bfs，因为bfs能够更好的知道下一层的孩子个数，这样我们就知道概率，而且层数也等于秒数，所以bfs优秀一些
  - 1.2 我们偏要用dfs:
    - 1.2.1 第一遍dfs，将树从上到下，得到每个node的孩子的个数以及它是否为叶子节点(能够进入下一层dfs的，就不是叶子节点，反过来思考就行！)
    - 1.2.2 第二遍dfs，单独处理叶子节点：
      - 那么用dfs也有道理的，每次下降入一层，则时间加1，相当于多跳一下（很显然不如bfs，因为bfs保证了只能从高层往底层跳）
      - dfs的时间如果比最终时间小，将节点最终时间的概率赋值为当前最大时间对应的概率即可！


```cpp
class Solution {
public:
    vector<vector<int>> g;
    unordered_map<int, unordered_map<int, double>> nodeTimeProb;
    unordered_map<int, int> sonsCnt;
    int finalTime = 0;

    vector<bool> vis;
    vector<bool> isLeaf;
    double frogPosition(int n, vector<vector<int>>& edges, int t, int target) {
        g.resize(n + 1, {});
        finalTime = t;
        vis.resize(n + 1, false);
        isLeaf.resize(n + 1, true);

        sort(edges.begin(), edges.end(), [](const vector<int>& a, const vector<int>& b) {
            return a[0] < b[0] || (a[0] == b[0] && a[1] < b[1]);
        });

        for(auto& e : edges) {
            g[e[0]].push_back(e[1]);
            g[e[1]].push_back(e[0]);
        }

        for(int i = 0; i < n; ++i) {
            nodeTimeProb[i] = {};
        }
        // cout <<"init done!" << endl;

        nodeTimeProb[1][0] = 1;
        vis[1] = true;
        dfsGetLeaf(1, isLeaf);
        
        for(int i = 0; i < n + 1; ++i) {
            vis[i] = false;
        }

        vis[1] = true;
        dfs(1, target, 0);

        return nodeTimeProb[target][t];
    }

    void dfsGetLeaf(int st, vector<bool>& isLeaf) {
        // deal leaf node
        for(auto son : g[st]) {
            if(vis[son]) {
                continue;
            }
            sonsCnt[st]++;
            vis[son] = true;
            isLeaf[st] = false;
            dfsGetLeaf(son, isLeaf);
        }
    }

    void dfs(int st, int tar, int time) {
        // deal leaf node
        if(isLeaf[st]) {
            if(time < finalTime) {
                nodeTimeProb[st][finalTime] = nodeTimeProb[st][time];
            }
            return;
        }

        for(auto son : g[st]) {
            // cout << " try son : " << son << endl;
            if(vis[son]) {
                continue;
            }

            vis[son] = true;
            nodeTimeProb[son][time+1] = nodeTimeProb[st][time] * 1.0 / (double)sonsCnt[st];
            // cout << "son/time : " << son << " | " << time << " -> " << nodeTimeProb[son][time+1] << endl;
            dfs(son, tar, time + 1);
        }

        
    }
};
```