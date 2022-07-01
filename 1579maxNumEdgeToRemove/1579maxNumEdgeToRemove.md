## 1579maxNumEdgeToRemove 保证图可完全遍历的最大删除边数

### 1 题目
[https://leetcode.cn/problems/remove-max-number-of-edges-to-keep-graph-fully-traversable/](https://leetcode.cn/problems/remove-max-number-of-edges-to-keep-graph-fully-traversable/)

### 2 解题思路
- 1 解题思路：（不如说：并查集就是典型的逆向思维）
  - 1.1 不要顺着考虑删除边的情况，那样式2^n复杂度，解决不了问题，逆向思维，考虑一条条加入边
  - 1.2 肯定是优先加入公共边，若能merge则是有用边，否则为无用边，则++res，然后看是否连通，如果连通，就不用alice和bob的专业边了，可以直接返回结果
  - 1.3 不然的话，要分别考虑alice和bob，对alice来说，从上面1.2中得到的并查集，对每一条a边尝试加入，失败则++res，对bob同样如此，最后返回res，当然失败情况就是，alice和bob至少有一个人的并查集的root数目大于1；

```cpp
class Solution {
public:
    
    class UF {
    public: 
        int rootNums;
        vector<int> parent;

        UF(int size) : rootNums(size - 1) {
            for(int i = 0; i < size; ++i) {
                parent.push_back(i);
            }
        }
        
        int find(int x) {
            int oldX = x;
            while(x != parent[x]) {
                // parent[x] = parent[parent[x]]; // compression path
                x = parent[x];
            }
            parent[oldX] = x; // the same as upwards
            return x;
        }

        bool merge(int x, int y) {
            int rootX = find(x);
            int rootY = find(y);
            if(rootX != rootY) {
                parent[rootX] = rootY;
                --rootNums;
                return true;
            }
            return false;
        }
    };
    
    int maxNumEdgesToRemove(int n, vector<vector<int>>& edges) {
        vector<vector<int>> aEdges;
        vector<vector<int>> bEdges;
        vector<vector<int>> abEdges;

        for(auto& e : edges) {
            if(1 == e[0]) {
                aEdges.push_back(e);
            } else if(2 == e[0]) {
                bEdges.push_back(e);
            } else  {
                abEdges.push_back(e);
            }
        }

        int removeEdgeCnt = 0;
        
        UF uf(n + 1);
        int abCnt = 0;
        // firstly add the common edges
        for(auto& e : abEdges) {
            if(!uf.merge(e[1], e[2])) {
                // cout << "ab: rm: " << e[1] << "-" << e[2] << endl;  
                ++removeEdgeCnt;
            } else {
                // cout << "ab: merge: " << e[1] << "-" << e[2] << endl;  
                ++abCnt;
            }
        }

        if(1 == uf.rootNums) {
            return edges.size() - abCnt;
        }
//  cout << "cur rmAB cnt: " << removeEdgeCnt << endl;
        UF ufA = uf;
        UF ufB = uf;
        // try to make alice all ok
        int aCnt = 0;
        for(auto& e : aEdges) {
            if(!ufA.merge(e[1], e[2])) {
                ++removeEdgeCnt;
                // cout << "a: rm: " << e[1] << "-" << e[2] << endl;  
            } 
        }
        // cout << "cur rmA cnt: " << removeEdgeCnt << endl;

        // try to make bob all ok
        int bCnt = 0;
        for(auto& e : bEdges) {
            if(!ufB.merge(e[1], e[2])) {
                ++removeEdgeCnt;
                // cout << "b: rm: " << e[1] << "-" << e[2] << endl;  
            }
        }

        //  cout << "cur rmB cnt: " << removeEdgeCnt << endl;
        if(1 == ufB.rootNums && 1 == ufA.rootNums) {
            return removeEdgeCnt;
        }
        return -1;
    }
};
```