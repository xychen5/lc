## 0095. 不同的二叉搜索树 II

### 1 题目
[https://leetcode-cn.com/problems/unique-binary-search-trees-ii/](https://leetcode-cn.com/problems/unique-binary-search-trees-ii/)

### 2 解题思路
- 1 首先明确一点，递归的主体为，从nums的数组中返回对应的所有可能的bst树
  - 1.1 输入： vector<int>
  - 1.2 返回： vector<treeNode*>
- 2 于是递归思路的想法就来了：
  - 2.1 对于一个node如何生成其所有可能的二叉树呢？我们只考虑第1层到第2层的(因为其他所有层的递归都是一样的逻辑，除非返回层不太一样)
    - 2.1.1 从nums中选择一个作为root，左边的numsLeft和右边的numsRight分别获取root的所有左右子树
    - 2.1.2 递归调用函数从numsLeft得到leftTrees，相应的得到rightTrees
    - 2.1.3 得到leftTrees和rightTrees以后，采用2层for循环和root拼装，得到最后的树

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
    vector<TreeNode*> generateTrees(int n) {
        vector<int> nodes;
        for(int i = 0; i < n; ++i) {
            nodes.emplace_back(i+1);
        }
        vector<TreeNode*> res;
        return getTreesFromArray(nodes);
    }

    vector<TreeNode*> getTreesFromArray(vector<int>& nodes) {
        int n = nodes.size();
        vector<TreeNode*> tmpRes;
        if(0 == n) {
            return {nullptr};
        }
        for(int i = 0; i < n; ++i) {
            int rootVal = nodes[i];
            vector<int> tmpLeft(nodes.begin(), nodes.begin() + i);
            vector<int> tmpRight(nodes.begin() + i + 1, nodes.end());
            vector<TreeNode*> left = getTreesFromArray(tmpLeft);
            vector<TreeNode*> right = getTreesFromArray(tmpRight);
            for(int m = 0; m < left.size(); ++m) {
                for(int n = 0; n < right.size(); ++n) {
                    TreeNode* root = new TreeNode(rootVal, left[m], right[n]); 
                    tmpRes.emplace_back(root); 
                }
            }
        }
        return tmpRes;
    }
}
```
