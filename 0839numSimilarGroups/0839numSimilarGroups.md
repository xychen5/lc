## 0839numSimilarGroups 相似字符串组数

### 1 题目
[https://leetcode.cn/problems/similar-string-groups/](https://leetcode.cn/problems/similar-string-groups/)

### 2 解题思路
- 1 解题思路：
  - 1.1 edge: 相似字符串之间
  - 1.2 求组数？连通个数->并查集即可

```cpp
class Solution {
public:
    using node = int;
    
    unordered_map<string, node> toNode;

    class UF {
    public:
        vector<int> parent;
        UF(int size) {
            for(int i = 0; i < size; ++i) {
                parent.push_back(i);
            }
        }

        int find(int x) {
            while(x != parent[x]) {
                x = parent[x];
            }
            return x;
        }

        void merge(int x, int y) {
            int fX = find(x);
            int fY = find(y);

            if(fX != fY) {
                // change a root's parent to another root
                parent[fX] = fY;
            }
        }

    };

    int numSimilarGroups(vector<string>& strs) {

        // rm duplications
        unordered_set<string> strs2;
        for(auto s : strs) {
            strs2.insert(s);
        }
        vector<string> rmDup;
        for(auto s : strs2) {
            rmDup.push_back(s);
        }
       
        
        int n = rmDup.size();
        vector<vector<int>> g;
        g.resize(n, {});
        
        // get all edges
        auto check = [](string& a, string& b) {
            if(a.size() != b.size()) {
                return false;
            }
            int len = a.size();
            int cursor = 0;
            char vecA[2] = {'0', '0'};
            char vecB[2] = {'0', '0'};
            while(cursor < len && a[cursor] == b[cursor]) {
                ++cursor;
            }
            vecA[0] = a[cursor];
            vecB[0] = b[cursor++];
            while(cursor < len && a[cursor] == b[cursor]) {
                ++cursor;
            }
            vecA[1] = a[cursor];
            vecB[1] = b[cursor++];

            // check first 2 diff pos and left part
            if(vecB[1] == vecA[0] && vecB[0] == vecA[1] && \
             (cursor == len || (cursor < len && a.substr(cursor) == b.substr(cursor)))
             ) {
                return true;
            }
            return false;
        };
        // suppose there is an edge between the similar pair
        for(int i = 0; i < n; ++i) {
            for(int j = 0; j < i; ++j) {
                if(i != j && check(rmDup[i], rmDup[j])) {
                    g[i].push_back(j);
                    g[j].push_back(i);
                    // cout << "pair: " << rmDup[i] << "\n        " << rmDup[j] << endl;
                    // cout << "i->j: " << i << " " << j << endl;
                }
            }
        }

        // uf to find how many roots
        UF uf(n);
        for(int i = 0; i < n; ++i) {
            for(auto j : g[i]) {
                uf.merge(i, j);
            }
        }

        int groupCnt = 0;
        for(int i = 0; i < n; ++i) {
            if(i == uf.find(i)) {
                ++groupCnt;
            }
        }

        return groupCnt;
    }
};
```