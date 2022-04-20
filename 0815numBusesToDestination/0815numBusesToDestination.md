## 0815numBusesToDestination 最少换乘数

### 1 题目
[https://leetcode-cn.com/problems/bus-routes/](https://leetcode-cn.com/problems/bus-routes/)

### 2 解题思路
- 1 解题思路：
  - 1.1 首先，能够想到用图去解答，然后点是车站，一条线路中的所有点构建一个完全图，所有边长度为1，这就能够说明用1个bus路线就能够到达目标，但是这复杂度有点高，是n^2 * m，而后bfs从src到tar只需要o(m)即可
  - 1.2 我们将思路换一下，因为考虑是从线路切换到线路，那么我们用线路代表节点，那么图的边什么时候会产生？当一个站台被两个线路同时拥有时，那么就将这两条线路对应的节点添加一个边

```cpp
class Solution {
public:
    unordered_map<int, vector<int>> lG;
    unordered_map<int, unordered_set<int>> stopToLines;
    unordered_set<int> lineTar;
    int numBusesToDestination(vector<vector<int>>& routes, int source, int target) {
        // build graph, g's e(i, j) means, there is a commen stop between line i and line j
        if(source == target) {
            return 0;
        }

        for(int lineId = 0; lineId < routes.size(); ++lineId) {
            for(auto& stop : routes[lineId]) {
                if(0 == stopToLines.count(stop)) {
                    stopToLines[stop] = {lineId};
                } else {
                    // for(auto line : stopToLines[stop]) {
                    //     if(0 == lG.count(line)) {
                    //         lG[line] = {lineId};
                    //     } else {
                    //         lG[line].push_back(lineId);
                    //     }
                    //     if(0 == lG.count(lineId)) {
                    //         lG[lineId] = {line};
                    //     } else {
                    //         lG[lineId].push_back(line);
                    //     }
                    // }
                    stopToLines[stop].insert(lineId);
                }
            }
        }

        // build lines
        for(auto& p : stopToLines) {
            auto lines = p.second;
            for(int lineI : lines) {
                for(int lineJ : lines) {
                    if(lineI != lineJ) {
                        if(0 == lG.count(lineI)) {
                            lG[lineI] = {lineJ};
                        } else {
                            lG[lineI].push_back(lineJ);
                        }
                    }
                }
            }
        }

        int res = INT_MAX;
        lineTar = stopToLines[target];

        // do bfs 
        for(auto lineSrc : stopToLines[source]) {
            int tmp = getBusSwitched(lineSrc);
            if(-1 != tmp){
                res = min(res, tmp);
            }
        }

        return res == INT_MAX ? -1 : res;
    }

    // bfs cal lines switched
    int getBusSwitched(int lineSrc) {
        queue<int> level;
        level.push(lineSrc);
        vector<int> mark(501, false);
        mark[lineSrc] = true;
        if(0 != lineTar.count(lineSrc)) {
            return 1;
        }

        int curLineCnt = 1;
        while(level.size() > 0) {
            queue<int> nextLevel;
            ++curLineCnt;
            while(level.size() > 0) {
                int curNode = level.front();
                level.pop();
                // cout << "\ncurNode: " << curNode << endl;
                for(auto& neighbor : lG[curNode]) {
                    // if reach the tar
                    if(0 != lineTar.count(neighbor)) {
                        // cout << "d2 starting from line:  " << lineSrc << endl;
                        return curLineCnt;
                    }
                    
                    if(!mark[neighbor]) {
                        nextLevel.push(neighbor);
                        mark[neighbor] = true;
                    }
                }
            }
            level = (move(nextLevel));
        }
        // cout << "d3 starting from line:  " << lineSrc << endl;
        return -1;
    }
};
```