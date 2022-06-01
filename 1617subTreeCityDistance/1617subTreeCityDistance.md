## 1617subTreeCityDistance 统计子树中城市之间最大距离

### 1 题目
[https://leetcode.cn/problems/count-subtrees-with-max-distance-between-cities/](https://leetcode.cn/problems/count-subtrees-with-max-distance-between-cities/)

### 2 解题思路
- 1 解题思路：
  - 1.1 使用16位的mask，每一位代表对应的节点是否存在，然后减少mask，直到mask为0,
  - 1.2 对于每一个mask，构建图，然后从邻居最少的点进行bfs，看高度，和是否连通
  - 1.3 1.2过程中，第一次bfs就知道是否连通，如果不连通直接退出，测试下一个mask即可

```cpp
class Solution {
public:
    
    void getTree(map<int, vector<int>>& g, vector<vector<int>>& edges, int mask) {
        int nodes = 0;
        while(mask > 0) {
            int ffsPos = ffs(mask) - 1;
            g[ffsPos + 1] = {}; 
            mask -= (1 << ffsPos);
        }

        for(auto& e : edges) {
            if(0 == g.count(e[0]) || 0 == g.count(e[1])) {
                continue;
            }
            g[e[0]].push_back(e[1]);
            g[e[1]].push_back(e[0]);
        }
    }

    pair<int, bool> bfs(map<int, vector<int>>& g, int stPoint, vector<int>& vis, queue<int>& curLevel) {
        for(auto& i : vis) {
            i = false;
        }

        // bfs to getHeight
        int cnt = 0;
        int height = 0;
        
        curLevel.push(stPoint);
        vis[stPoint] = true;
        ++cnt;

        // cout << "\n@@@@@@@@@@\n"; 
        while(!curLevel.empty()) {
            int curSize = curLevel.size();

            bool hasNext = false;
            while(curSize-- > 0) {
                auto curNode = curLevel.front();
                curLevel.pop();
                // cout << "cur: " << curNode << " ";
                for(auto& neighbor : g[curNode]) {
                    if(!vis[neighbor]) {
                        curLevel.push(neighbor);
                        // cout << neighbor << " ";
                        vis[neighbor] = true;
                        hasNext = true;
                        ++cnt;
                    }
                }
            }
            // cout << " | hasNext: " << hasNext << "\n";
            height += hasNext;
        }
                // cout << "--@@@@@@@@@@\n";

        return {height, cnt == g.size()};
    }

    // return <height, isCotinualbe>
    pair<int, bool> getHeight(map<int, vector<int>>& g) {
        // create vis
        // map<int, bool> vis;
        vector<int> vis(16, false);


        queue<int> curLevel;

        int nodeCnt = g.size();

        int minNeighbor = INT_MAX;
        for(auto& p : g) {
            vis[p.first] = false;
            minNeighbor = min((int)p.second.size(), minNeighbor);
        }
        
        pair<int, bool> res = {-1, false};
        for(auto& p : g) {
            if(minNeighbor != p.second.size()) {
                continue;
            }
            auto tmp = bfs(g, p.first, vis, curLevel);
            if(tmp.second) {
                if(tmp.first > res.first) {
                    // cout << "starting from: " << p.first << " | h: " << tmp.first << endl;
                    res = tmp;
                }
            } else {
                return {-1, false};
            }
        }
        // cout << "done!" << endl;

        return res;
    }


    vector<int> countSubgraphsForEachDiameter(int n, vector<vector<int>>& edges) {
        int mask = (1 << n) - 1;
        
        // disCnt[0] : subTreesCnt whose dis is 1
        vector<int> disCnt(n - 1);
        map<int, vector<int>> g;

        while(mask > 0) {
            int curMask = mask;
            // cout << "curMask: " << bitset<8>(curMask) << " | ";
            
            g.clear();

            getTree(g, edges, curMask);
            if(g.size() <= 1) {
                --mask;
                continue;
            }
            // print(g);
            auto res = getHeight(g);
            
            if(res.second) {
                disCnt[res.first - 1]++;
            }

            --mask;
        }

        return disCnt;
    }

    void print(map<int, vector<int>>& g) {
        cout << " ---------- st --------- \n";
        for(auto& p : g) {
            cout << p.first << ": ";
            for(auto n : p.second) {
                cout << n << " ";
            }cout << "\n";
        }
    }
};
```