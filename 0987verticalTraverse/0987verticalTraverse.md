## 0987verticalTraverse 垂序遍历

### 1 题目
[https://leetcode-cn.com/problems/vertical-order-traversal-of-a-binary-tree/](https://leetcode-cn.com/problems/vertical-order-traversal-of-a-binary-tree/)

### 2 解题思路
- 1 解题思路：
  - 1.1 dfs即可，dfs(left, col - 1), dfs(right, col + 1)，向左边的话，col - 1, 向右边dfs，col + 1;


```cpp
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    unordered_map<int, vector<pair<int, int>>> colToNodes;
    vector<vector<int>> verticalTraversal(TreeNode* root) {
        if(nullptr == root) {
            return {};
        }
        dfs(root, 0, 0);
        
        int colCnt = colToNodes.size();
        vector<vector<int>> res(colCnt);

        int minCol = INT_MAX;
        for(auto p : colToNodes) {
            minCol = min(p.first, minCol);
        }

        auto cmp = [](const pair<int, int>& a, const pair<int, int>& b) {
            return a.second < b.second || (a.second == b.second && a.first < b.first);
        };

        for(auto p : colToNodes) {
            auto& vec = p.second;
            sort(vec.begin(), vec.end(), cmp);
            vector<int> tmp;
            for(auto num : vec) {
                tmp.push_back(num.first);
            }
            res[p.first - minCol] = std::move(tmp);
        }

        return res;
        
    }

    void dfs(TreeNode* root, int colIdx, int level) {
        if(nullptr == root) {
            return;
        }
        if(0 == colToNodes.count(colIdx)) {
            colToNodes[colIdx] = { {root->val, level } };
        } else {
            colToNodes[colIdx].push_back({ root->val, level });
        }
        
        dfs(root->left, colIdx - 1, level + 1);
        dfs(root->right, colIdx + 1, level + 1);
    }
};
```