## 0310minHeightTree 最小高度树

### 1 题目
[https://leetcode-cn.com/problems/minimum-height-trees/](https://leetcode-cn.com/problems/minimum-height-trees/)

### 2 解题思路
- 1 其实想一下，从叶子节点开始bfs，第一层是所有的叶子节点，下一层是第一层的叶子去掉以后的所有叶子，直到剩下的点在2个以内，就保证了最小高度树

```cpp
class Solution {
public:
    vector<int> findMinHeightTrees(int n, vector<vector<int>>& edges) {
        // at most has 2 MHT
        // start from the leaf node to do bfs, when the next node's 
        // unvisited neighbors are 1（it becomes a leaf）,  then add it 
        // to the res vec, and do bfs to res vec
        // until there are less than 2 nodes left in the bfs process, then stop
        if(edges.size() == 0) {
            return {0};
        }

        queue<int> res;
        vector<int> neighbors(n, 0);
        vector<vector<int>> g(n, vector<int>(0));
        for(auto& e : edges) {
            g[e[0]].push_back(e[1]);
            g[e[1]].push_back(e[0]);
            for(auto& v : e) {
               neighbors[v]++;
            }
        }

        // add leaf nodes to the res
        for(int vIdx = 0; vIdx < n; ++vIdx) {
            if(1 == neighbors[vIdx]) {
                res.push(vIdx);
            }
        }

        // do bfs
        int unvisitedNum = n;
        vector<bool> visited(n, false);
        while(unvisitedNum > 2) {
            int curLevelSize = res.size();
            for(int i = 0; i < curLevelSize; ++i) {
                int curNode = res.front();
                visited[curNode] = true;
                res.pop();

                for(auto neighbor : g[curNode]) {
                    if(!visited[neighbor]) {
                        --neighbors[neighbor];
                        if(1 == neighbors[neighbor]) {
                            res.push(neighbor);
                            visited[neighbor] = true;
                        }
                    }                 
                }
            }
            unvisitedNum -= curLevelSize;
        }

        vector<int> ret;
        while(!res.empty()) {
            ret.push_back(res.front());
            res.pop();
        }
        return ret;
    }
};
```