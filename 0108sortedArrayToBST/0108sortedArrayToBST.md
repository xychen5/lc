## 0108. 将有序数组转换为二叉搜索树 

### 1 题目
[https://leetcode-cn.com/problems/convert-sorted-array-to-binary-search-tree/](https://leetcode-cn.com/problems/convert-sorted-array-to-binary-search-tree/)

### 2 解题思路
- 1 AVL tree最主要的特性在于，任何子树的左子树和右子树的高度差不超过1，所以方法为：
  - 1.1 每次找到数组中间的值作为root，然后两边分别作为左右子树，左边都比root小，右边都大，刚好满足AVL要求
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
    TreeNode* sortedArrayToBST(vector<int>& nums) {
        // find root whose left size and right size shall equal
        int n = nums.size();
        if(n <= 0) {
            return nullptr;
        }
        vector<int> left(nums.begin(), nums.begin() + n / 2);
        vector<int> right(nums.begin() + n / 2 + 1, nums.end());
        TreeNode* root = new TreeNode(
            nums[n/2]
            sortedArrayToBST(left),
            sortedArrayToBST(right)
        );
        return root;
    }
};
```
