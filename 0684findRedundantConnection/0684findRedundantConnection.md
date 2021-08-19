# 0684 冗余链接

## 1 题目描述
[https://leetcode-cn.com/problems/redundant-connection](https://leetcode-cn.com/problems/redundant-connection)

## 2 解题思路
使用并查集，将每一条边都看做一个子树，然后一条边一条边加入这个树，当加入的边的两个顶点属于同一个子树时，就认为有回环，则返回这个冗余边。
见如下代码：
```cpp
class Solution {
public:
    vector<int> findRedundantConnection(vector<vector<int>>& edges) {
        tree.resize(edges.size() * 2 + 1, -1);
        subTreeSize.resize(edges.size() * 2 + 1, 1);
        
        vector<int> res;
        for(auto& c : edges) {
            if(!unionMerge(c[0], c[1], tree)) {
                res = c;
                break;
            }
        }
        return res;
    }
    
    int find(int tar, vector<int>& tree) {
        int curFather = tree[tar];
        if (curFather < 0) { // tar has no father, so he is the root
            tree[tar] = tar;
            return tar;
        }
        if(tar != curFather) {
            tree[tar] = find(curFather, tree); // compress the data path
        }
        return tree[tar];
    }
    
    
    bool unionMerge(int x, int y, vector<int>& tree) {
        int fx = find(x, tree);
        int fy = find(y, tree);
        if(fx == fy) {
            return false; // x, y are in the same tree, need no merge
        }
        if(subTreeSize[fx] >= subTreeSize[fy]){ // merge by rank of the sub Tree
            tree[fy] = fx;
            subTreeSize[fx] += subTreeSize[fy];
        } else {
            tree[fx] = fy;
            subTreeSize[fy] += subTreeSize[fx];
        }
        return true;
    }
    
    vector<int> subTreeSize;
    vector<int> tree;
};
```



