## 0109storedListToBST

### 1 题目：
[https://leetcode-cn.com/problems/convert-sorted-list-to-binary-search-tree/](https://leetcode-cn.com/problems/convert-sorted-list-to-binary-search-tree/)

### 2 解题思路：
首先意识到，root节点一定为中间，则可以立马想到递归：
leftList->middle->rightList

root = middle
root->left = convert(leftList)
root->right = convert(rightList)

```cpp
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
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
    TreeNode* sortedListToBST(ListNode* head) {
        if(head == nullptr) {
            return nullptr;
        }

        ListNode* p = head;
        vector<int> vec;
        while(p!=nullptr) {
            vec.emplace_back(p->val);
            p = p->next;
        }
        
        return vecToBST(vec);
    }

    TreeNode* vecToBST(vector<int>& vec) {
        int len = vec.size();
        if(len == 0) {
            return nullptr;
        }
        TreeNode* root = new TreeNode(vec[len/2]);
        if(len == 1) {
            return root;
        }

        vector<int> left(vec.begin(), vec.begin() + len /2);
        vector<int> right(vec.begin() + len/2 + 1, vec.end());

        root->left = vecToBST(left);
        root->right = vecToBST(right);
        return root;

    }
};
```