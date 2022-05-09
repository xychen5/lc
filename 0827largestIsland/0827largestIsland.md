## 0827largestIsland 最大岛屿

### 1 题目
[https://leetcode.cn/problems/making-a-large-island/](https://leetcode.cn/problems/making-a-large-island/)

### 2 解题思路
- 1 解题思路：并查集
  - 1.1 具体的，对于每个0，首先看4周的4个位置，为1，然后找出这些root，最多4个最多1个，然后加上位置0本身体的1，去更新最大岛屿即可

```cpp
class Solution {
public:
    
    class UF {
    public: 
        vector<int> parent;
        vector<int> rootSize;

        UF(int size) {
            for(int i = 0; i < size; ++i) {
                parent.push_back(i);
            }
            rootSize.resize(size, 1);
        }

        int find(int x) {
            while(x != parent[x]) {
                x = parent[x]; // path compression may be done here!
            }
            return x;
        }

        void merge(int x, int y) {
            int fX = find(x);
            int fY = find(y);
            if(fX != fY) {
                parent[fX] = fY; // chang a cc's root to point to another cc's root
                rootSize[fY] += rootSize[fX];
            }
        }

        bool inSameCC(int x, int y) {
            int fX = find(x);
            int fY = find(y);
            return fX == fY;
        }
    };

    int dx[4] = {1, 0, -1, 0};
    int dy[4] = {0, 1, 0, -1};
    int n = -1;

    int getNode(int i, int j) {
        return i * n + j;
    }

    int largestIsland(vector<vector<int>>& grid) {
        n = grid.size();

        UF uf(n*n);
        for(int x = 0; x < n; ++x) {
            for(int y = 0; y < n; ++y) {
                if(!grid[x][y]) {
                    continue;
                }
                for(int mv = 0; mv < 4; ++mv) {
                    int nextX = x + dx[mv];
                    int nextY = y + dy[mv];
                    if(nextX >= 0 && nextX < n && \
                    nextY >= 0 && nextY < n) {
                        if(grid[nextX][nextY]) {
                            uf.merge(getNode(x, y), getNode(nextX, nextY));
                        }
                    }
                }
            }
        }
        
        // for(auto i : uf.parent) {
        //     cout<< i<< " ";
        // }cout << "\n";
        // for(auto i : uf.rootSize) {
        //     cout<< i<< " ";
        // }cout << "\n";
        

         
        int res = 1;
        int cnt1 = 0;
        // travel all 0's position to see if we can make a bigger island
        for(int x = 0; x < n; ++x) {
            for(int y = 0; y < n; ++y) {
                if(grid[x][y]) {
                    ++cnt1;
                    continue;
                }
                // int nodeU = getNode(x, y);
                // int rootU = uf.find(nodeU)
                unordered_set<int> cc;
                // cc.insert(rootU);
                int curRes = 0;
                
                // find 4 around points, and find their roots, maybe only one root
                for(int mv = 0; mv < 4; ++mv) {
                    int nextX = x + dx[mv];
                    int nextY = y + dy[mv];

                    if(nextX >= 0 && nextX < n && \
                    nextY >= 0 && nextY < n && \
                    grid[nextX][nextY]) {
                        int nodeV = getNode(nextX, nextY);
                        int rootV = uf.find(nodeV);
                        if(cc.count(rootV) != 0) {
                            continue;
                        }
                        cc.insert(rootV);
                        // cout << "added! root : " << rootV << endl;
                        curRes += uf.rootSize[rootV];
                    }
                }

                // update res
                res = max(res, curRes + 1);
            }
        }

        return cnt1 == n*n ? n*n : res;
    }
};
```