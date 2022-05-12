## 1028recoverFromPreoder 前序和深度恢复二叉树

### 1 题目
[https://leetcode.cn/problems/recover-a-tree-from-preorder-traversal/](https://leetcode.cn/problems/recover-a-tree-from-preorder-traversal/)

### 2 解题思路
- 1 解题思路：用栈模拟前序遍历的过程即可

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

    int cur = 0;
    int curDepth = 0;
    
    int getNode(string& traversal) {
        size_t pos = traversal.find("-", cur);
        if(pos == string::npos) {
            size_t lastInt = traversal.find_last_of("-");
            cur = traversal.size();
            return std::atoi(traversal.substr(lastInt+1).c_str());
        }
        int oldCur = cur;
        cur = pos;
        return std::atoi(traversal.substr(oldCur, pos - oldCur).c_str());
    }

    int getDepth(string& traversal) {
        size_t pos = traversal.find_first_not_of("-", cur);
        int oldCur = cur;
        cur = pos;
        return pos - oldCur;
    }


    TreeNode* recoverFromPreorder(string traversal) {
        TreeNode* root = new TreeNode(getNode(traversal));
        vector<TreeNode*> curPath{root};
        vector<int> dep{0};

        while(cur != traversal.size()) {
            // get depth
            int d = getDepth(traversal);
            int n = getNode(traversal);
            auto node = new TreeNode(n);
            if(dep.back() < d) {
                curPath.back()->left = node;
                curPath.push_back(node);
                dep.push_back(d);
            } else if(dep.back() == d) {
                curPath.pop_back();
                curPath.back()->right = node;
                curPath.push_back(node);
            } else {
                while(dep.back() > d) {
                    dep.pop_back();
                    curPath.pop_back();
                }
                curPath.pop_back();
                curPath.back()->right = node;
                curPath.push_back(node);
            }
        }

        return root;
    }
};
```