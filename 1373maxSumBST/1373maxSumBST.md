## 1373 maxSumBST 二叉搜索子树的最大键值和

### 1 题目
[https://leetcode-cn.com/problems/maximum-sum-bst-in-binary-tree/](https://leetcode-cn.com/problems/maximum-sum-bst-in-binary-tree/)

### 2 解题思路
- 1 采用后续遍历，(前中后遍历的前中后是针对root节点的访问时期和左右子树的比较)
- 2 对于每个节点，维持该节点的4个值：
  - int sum = 0; // 子树的所有和
  - int isBST = false; // 该节点为root的子树是否为BST
  - int maxVal = INT_MIN; // 该节点对应子树最大值
  - int minVal = INT_MAX; // 该节点对应子树最小值
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
        int sum = 0;
        int isBST = false;
        int maxVal = INT_MIN;
        int minVal = INT_MAX;
        entry() {};
    };
    map<void*, entry> bstRec;

    void dfs(TreeNode* root, int& res) {
        if(nullptr == root) {
            return;
        }
        dfs(root->left, res);
        dfs(root->right, res);

        // curRoot
        entry tmp;
        if(nullptr != root->left && nullptr != root->right) {
            tmp.sum = root->val + bstRec[root->right].sum + bstRec[root->left].sum;
            tmp.isBST = bstRec[root->right].isBST && \ 
                root->val < bstRec[root->right].minVal && \
                root->val > bstRec[root->left].maxVal;
            tmp.maxVal = max(root->val, bstRec[root->left].maxVal);
            tmp.maxVal = max(tmp.maxVal, bstRec[root->right].maxVal);
            tmp.minVal = min(root->val, bstRec[root->left].minVal);
            tmp.minVal = min(tmp.minVal, bstRec[root->right].minVal);
        } else if(nullptr == root->left && nullptr != root->right) {
            tmp.sum = root->val + bstRec[root->right].sum;
            tmp.isBST = bstRec[root->right].isBST && root->val < bstRec[root->right].minVal;
            tmp.maxVal = max(root->val, bstRec[root->right].maxVal);
            tmp.minVal = min(root->val, bstRec[root->right].minVal);
        } else if(nullptr != root->left && nullptr == root->right) {
            tmp.sum = root->val + bstRec[root->left].sum;
            tmp.isBST = bstRec[root->left].isBST && root->val > bstRec[root->left].maxVal;
            tmp.maxVal = max(root->val, bstRec[root->left].maxVal);
            tmp.minVal = min(root->val, bstRec[root->left].minVal);
        } else {
            tmp.sum = root->val;
            tmp.isBST = true;
            tmp.maxVal = root->val;
            tmp.minVal = root->val;
        } 
        if(tmp.isBST) {
            res = max(res, tmp.sum);
        } 
        // cout << root->val << " -> " << tmp.sum << endl;;
        bstRec[root] = tmp;

    }

    int maxSumBST(TreeNode* root) {
        int res = 0;
        dfs(root, res);
        return res;
    }
};
```
