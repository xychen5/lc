## 1483kAncestorInTree  树节点的第 K 个祖先

### 1 题目
[https://leetcode.cn/problems/kth-ancestor-of-a-tree-node/](https://leetcode.cn/problems/kth-ancestor-of-a-tree-node/)

### 2 解题思路
- 1 解题思路：
  - 1.1 BinaryLifting思想
    - dp[node][k] 存储的是 node 节点距离为 2^k 的祖先是谁
    - dp[node][k] = dp[node][dp[node][k-1]][k-1]
  - 1.2 查询：
    - 举个例子： 对于 5 号(从0开始)节点的第12个祖先，也就是1100个祖先，
    - 我们首先: 1100 = 1000 + 100，
    - 于是先找到第4个祖先，dp[5][2],
    - 然后从第4个祖先找到第8个祖先：dp[dp[5][2]][3]

```cpp
class TreeAncestor {
public:
    vector<vector<int>> dp; // dp[node][k]存储的是2^k的祖先
    TreeAncestor(int n, vector<int>& parent) {
        // dp[node][j] = dp[dp[node][j - 1]][j - 1]
        
        // init dp, dp[i][0] = parent[i]
        dp.resize(n, {});
        for(int node = 0; node < n; ++node) {
            dp[node].push_back(parent[node]);
        }

        // travel k fron 1 to log(n)
        int k = 1;
        // when all node's 2^k ancestor is -1
        
        do {
            bool allNegative = true;
            for(int node = 0; node < n; ++node) {
                if(dp[node][k-1] == -1) {
                    dp[node].push_back(-1);
                } else {
                    allNegative = false;
                    dp[node].push_back(dp[dp[node][k-1]][k-1]);
                }
            }
            if(allNegative) {
                break;
            }
            ++k;
        } while(1);
    }
    
    int getKthAncestor(int node, int k) {
        // cout << "-------------------\n";
        // return -1;
        // ffs: find first set bit pos from right to left
        while(1) {
            // get first set bit
            int ffsPos = ffs(k) - 1;
            if(ffsPos >= dp[node].size()) {
                return -1;
            }
            
            // cout << bitset<10>(k) << " | " << ffsPos << endl;
            int ancestor = dp[node][ffsPos];
            k = k - (1 << ffsPos);
            node = ancestor;

            // all set bits consumed!
            if(k == 0) {
                return ancestor;
            }

            // k too big, no such k
            if(-1 == ancestor) {
                return -1;
            }            
        }
        return node;

    }
};
```