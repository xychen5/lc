#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <limits.h>
#include <numeric>
#include <list>
#include <queue>
#include <unordered_set>
#include <unordered_map>
#include <map>

using namespace std;
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
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

int main() {
    // vector<int> nums = {1, 15, 5, 11};
    // vector<int> nums = {1, 3};
    // vector<int> nums = {1, 3};
    vector<int> nums = {1, 2, 2, 3};
    Solution sl;
    ListNode *n1 = new ListNode(1);
    ListNode *n2 = new ListNode(2); n1->next = n2;
    ListNode *n3 = new ListNode(3); n2->next = n3;
    // std::cout << ios::left << std::setw(20) << "Hello, World!" << std::setw(5) << "a s " << 1 << std::endl;
    return 0;
}
