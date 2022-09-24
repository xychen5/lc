## 1591weirdPrinter2 奇怪打印机

### 1 题目
[https://leetcode.cn/problems/strange-printer-ii/](https://leetcode.cn/problems/strange-printer-ii/)

### 2 解题思路
- 1 解题思路
  - 一个矩形内部含有另一个矩形，那就认为是，有一条边
  - 那么如果能够打印成功，必然上面的边能够topology sort成功，否则就是有环，那就失败了

```cpp
class Solution {
public:
    bool isPrintable(vector<vector<int>>& targetGrid) {
        // topology sort
        // judge if there is loop in the topo graph
        // the edge's u point to v, then u contains v

        // node: min xy max xy
        using rec = pair<pair<int, int>, pair<int, int>>;

        int m = targetGrid.size();
        int n = targetGrid[0].size();

        unordered_map<int, rec> nodes;

        auto updateRec = [](rec& src, int x, int y) {
            src.first.first = min(src.first.first, x);
            src.first.second = min(src.first.second, y);
            src.second.first = max(src.second.first, x);
            src.second.second = max(src.second.second, y);
        };
        
        // get each rectangles
        for(int i = 0; i < m; ++i) {
            for(int j = 0; j < n; ++j) {
                if(0 == nodes.count(targetGrid[i][j])) {
                    rec tmp = {{i, j}, {i, j}};
                    nodes[targetGrid[i][j]] = tmp;
                } else {
                    updateRec(nodes[targetGrid[i][j]], i, j);
                }
            }
        }

        // build the graph
        unordered_map<int, vector<int>> g;
        unordered_map<int, int> inDeg;
        for(auto& node : nodes) {
            inDeg[node.first] = 0;
        }

        for(auto& node : nodes) {
            int minX = node.second.first.first;
            int minY = node.second.first.second;
            int maxX = node.second.second.first;
            int maxY = node.second.second.second;
            int curNode = node.first;
            unordered_set<int> used;
            for(int i = minX; i <= maxX; ++i) {
                for(int j = minY; j <= maxY; ++j) {
                    if(targetGrid[i][j] != curNode) {
                        // then curNode point to the contained node
                        if(0 != used.count(targetGrid[i][j])) {
                            continue;
                        }
                        used.insert(targetGrid[i][j]);
                        g[curNode].push_back(targetGrid[i][j]);
                        // cout << "edge: " << curNode  << " -> " << targetGrid[i][j]<< endl;
                        inDeg[targetGrid[i][j]]++;
                        // cout << targetGrid[i][j] <<  " inDeg: " << inDeg[targetGrid[i][j]] << endl;
                    }
                }
            }
        }

        // topo sort, if failed, then return false
        int usedNode = 0;
        unordered_set<int> visited;
        while(usedNode < inDeg.size()) {
            // find a start node
            queue<int> curLevel;
            bool notFound = true;
            for(auto p : inDeg) {
                int curNode = p.first;
                int inDegree = p.second;
                if(0 == inDegree && 0 == visited.count(curNode)) {
                    curLevel.push(curNode);
                    notFound = false;
                    break;
                }
            }
            if(notFound) {
                return false; 
            }

            while(curLevel.size() > 0) {
                int levelSize = curLevel.size();
                while(levelSize > 0) {
                    int curNode = curLevel.front();
                    // cout << "vis: " << curNode << endl;
                    curLevel.pop();
                    visited.insert(curNode);
                    ++usedNode;
                    // cout << "usedcnt: " << usedNode << endl;

                    for(auto neighbor : g[curNode]) {
                        --inDeg[neighbor];
                        if(0 == inDeg[neighbor]) {
                            curLevel.push(neighbor);
                        }
                    }
                    -- levelSize;
                }
            }
        }
        
        return true;
    }
};
```
