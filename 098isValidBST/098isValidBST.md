## 98. 验证二叉搜索树

### 1 题目
[https://leetcode-cn.com/problems/validate-binary-search-tree/](https://leetcode-cn.com/problems/validate-binary-search-tree/)

### 2 解题思路
- 1 为每一个node保存一个**以当前节点为root的子树的最大值和最小值**，那么每一个node就可以检测当前node是否为有效bst啦
  - 顺带一提，node寸的信息可以使用hash存(unordered_map)，这样速度快点
- 2 普通思路：dfs中序遍历，获取访问的顺序数组，然后判断是否为单调递增，不然则为非法数组。
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
    struct entry {
        long long lMax = LLONG_MIN;
        long long rMin = LLONG_MAX;
    };
    unordered_map<void*, entry> entries;

    bool isValidBST(TreeNode* root) {
        long long lMax = LLONG_MIN;
        long long rMin = LLONG_MAX;
        entry tmp;
        entries[nullptr] = tmp;
        return checkValid(root);
    }

    // max, min means in the max/min value in root's tree
    bool checkValid(TreeNode* root) {
        if(root == nullptr) {
            return true;
        }
        bool c1 = checkValid(root->right);
        bool c2 = checkValid(root->left);
        entry l = entries[root->left];
        entry r = entries[root->right];
        entry rootEntry;
        
        if(l.lMax >= root->val) {
            return false;
        }
        if(r.rMin <= root->val) {
            return false;
        }
        rootEntry.lMax = max(l.lMax, static_cast<long long>(root->val));
        rootEntry.rMin = min(l.rMin, static_cast<long long>(root->val));
        rootEntry.lMax = max(rootEntry.lMax, r.lMax);
        rootEntry.rMin = min(rootEntry.rMin, r.rMin);

        entries[root] = rootEntry;
        return c1 && c2;
    }
};
```
