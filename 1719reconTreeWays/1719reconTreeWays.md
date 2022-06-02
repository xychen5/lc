## 1719reconTreeWays 重构一棵树的方案数

### 1 题目
[https://leetcode.cn/problems/number-of-ways-to-reconstruct-a-tree/](https://leetcode.cn/problems/number-of-ways-to-reconstruct-a-tree/)

### 2 解题思路
- 1 解题思路：
  - 1.1 最重要的一个观察：谁的度大，谁就在越上层比如root，它的度必为n - 1,否则一定会出现一个后继root组成的pair不在pairs里面
  - 1.2 当度相等的时候，意味着可以做parent可以做son，那么就可以是说最少有2中方案和
- 2 于是我们的思路就是：
  - 2.1 对于除了root的所有节点比如说node_i，找到它最小(小就是说，度少)的祖先（这里在贪心，找到的祖先是紧邻的parent），然后判断这个节点的邻居包含所有node_i节点的neighbors，不是的话就说明构建失败，否则构建成功
  - 2.2 为什么贪心可行？因为最小的parent一定是上一个节点的parent，因为两层紧挨，那么他们的差距一定是最小的，否则是更大的祖先

```cpp
class Solution {
public:
    int checkWays(vector<vector<int>>& pairs) {
        unordered_map<int, unordered_set<int>> tree;
        vector<int> degrees(501, 0);
        for(auto& vec : pairs) {
            tree[vec[0]].emplace(vec[1]);
            tree[vec[1]].emplace(vec[0]);
            
            ++degrees[vec[0]];
            ++degrees[vec[1]];
        }
        int n = tree.size();

        int root = -1;
        for(auto& [node, neighbors] : tree) {
            if(n - 1 == degrees[node]) {
                root = node;
                break;
            }
        }

        if(-1 == root) {
            return 0;
        }

        // 最重要的一个观察：
        // 谁的度大，谁就在越上层比如root，它的度必为n - 1,否则一定会出现一个后继
        // 和root组成的pair不在pairs里面
        // 当度相等的时候，意味着可以做parent可以做son，那么就可以是说最少有2中方案
        // 于是我们的思路就是：
        // 对于除了root的所有节点比如说node_i，找到它最小(小就是说，度少)的parent（这里在贪心），然后判断这个parent是否
        // 包含所有node_i节点的neighbors，不是的话就说明构建失败，否则构建成功
        int res = 1;
        for(auto& [curNode, neighbors] : tree) {
            if(curNode == root) {
                continue;
            }
            
            int curDeg = degrees[curNode];
            int parentDeg = INT_MAX;
            int parentNode = -1;
            // 找到degree刚好大于他的那个neighbors
            for(auto& neighbor : neighbors) {
                // 如果这个neighbor能够当parent，并且比目前的parent还要小
                // cout << "n/c: " << neighbor << "/" << curNode << " | deg: " << degrees[neighbor] << "/" << curDeg << endl; 
                if(curDeg <= degrees[neighbor] && parentDeg > degrees[neighbor]) {
                    parentNode = neighbor;
                    parentDeg = degrees[neighbor];
                }
            }

            if(-1 == parentNode) {
                return 0;
            }

            // 检测这个parent是不是能够含有所有的curNode的邻居
            for(auto& neighbor : neighbors) {
                if(neighbor == parentNode) {
                    continue;
                }
                if(0 == tree[parentNode].count(neighbor)) {
                    return 0;
                }
            }

            if(parentDeg == curDeg) {
                res = 2;
            }
        }

        return res;
    }
};
```