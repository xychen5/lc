## 1367isSubPath

### 1 题目：
[https://leetcode-cn.com/problems/linked-list-in-binary-tree/](https://leetcode-cn.com/problems/linked-list-in-binary-tree/)

### 2 解题思路：
- 1 dfs获得所有节点
- 2 对所有节点遍历看是否能够找到链表对应的序列

- 3 可能的优化：
  - 3.1 子树的高度小于链表长度的直接跳过哦
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
    ListNode* oriHead = nullptr;
    std::list<TreeNode*> searchTreeNodeQueue;
    std::vector<TreeNode*> allSubTrees;
    std::unordered_set<TreeNode*> visitedNode;
    bool isSubPath(ListNode* head, TreeNode* root) {
        if(root == nullptr ){
            return false;
        }
        // 在搜寻的过程中检测的思路，而应该对每一个节点去考虑
        // 原本思路：
        // 一边dfs，一边找这个list，关键是一旦不匹配了，则
        // 回到原来的第一次head匹配的位置的左右子树进行搜寻
        // 这里有一个问题，这样做完全没办法减少搜索的次数，然后增加了代码复杂度
        oriHead = head;
        dfsTravel(root);
        for(int i = 0; i < allSubTrees.size(); ++i) {
            if (search(head, allSubTrees[i])) return true;
        }
        return false;
    }

    void dfsTravel(TreeNode* root) {
        if(root!=nullptr) {
            allSubTrees.push_back(root);
            dfsTravel(root->left);
            dfsTravel(root->right);
        }

    }

    bool search(ListNode* curHead, TreeNode* root) {
        if(curHead == nullptr){
            return true;
        } 
        if(root == nullptr ){
            return false;
        }

        if(curHead->val == root->val) {

            return search(curHead->next, root->left) || search(curHead->next, root->right);
            // if(search(curHead->next, root->left)) return true;
            // if(search(curHead->next, root->right)) return true;
        } 
        return false;
    }
};
```
