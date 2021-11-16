## 0375 此数字大小所需最小金额

### 1 题目
[https://leetcode-cn.com/problems/number-of-provinces/](https://leetcode-cn.com/problems/number-of-provinces/)


### 2 解题思路
该解题方案实际上为有向图强联通分量求解的一个子集，无向图即为顶点和顶点之间的边均为双向边。
这里以kosaraju算法为例:
- 1 对于有向图，一开始我们需要获取dfs的逆序遍历栈，原因是，在第二次dfs也就是逆图中的遍历我们可以总是用最晚完成遍历的点去遍历，如此依赖，这样的一个遍历就能得到一个连通分量。
- 2 但是针对无向图，不需要这样，因为遍历到不能拓展新的节点，我们就获取到了一个连通分量。
```cpp
class Solution {
public:
    void dfs(vector<vector<int>>& g, vector<int>& reversePost, vector<bool>& vis, int tarV) {
        vis[tarV] = true;
        for(int j = 0; j < g.size(); ++j) {
            if(g[tarV][j] != 0) {
                if(!vis[j]) {
                    dfs(g, reversePost, vis, j);
                }
            }    
        }
        reversePost.emplace_back(tarV);
    }

    int findCircleNum(vector<vector<int>>& isConnected) {
        // 获取逆图
        int n = isConnected.size();
        vector<vector<int>> revIsConnected(isConnected);

        // 由于不是针对有向图，故不需要这一步
        // 获取逆序
        vector<bool> vis(n, false);
        vector<int> reversePost;
        // dfs(isConnected, reversePost, vis, 0);

        // 直接任选一点遍历，看有几个连通分量即可
        int ans = 0;       
        for(int j = 0; j < isConnected.size(); ++j) {
            if(!vis[j]) {
                dfs(isConnected, reversePost, vis, j);
                ans ++;
            }          
        }
        return ans;
    }
};
```
