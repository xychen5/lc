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

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};


struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

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

int main() {
    // vector<int> nums = {1, 15, 5, 11};
    // vector<int> nums = {1, 3};
    // vector<int> nums = {1, 3};
    vector<int> nums = {1, 2, 2, 3};
    // Solution sl;
    // ListNode *n1 = new ListNode(1);
    // ListNode *n2 = new ListNode(2); n1->next = n2;
    // ListNode *n3 = new ListNode(3); n2->next = n3;
    // std::cout << ios::left << std::setw(20) << "Hello, World!" << std::setw(5) << "a s " << 1 << std::endl;
    return 0;
}
