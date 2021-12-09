// ConsoleApplication1.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
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
#include <set>

using namespace std;

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

int main()
{
    // vector<int> nums = {1, 15, 5, 11};
    // vector<int> nums = {1, 3};
    // vector<int> nums = {1, 3};
    int n = 2;
    vector<int> nums1d = { 1, 0 };
    vector<vector<int>> nums2d1 = { {1}, {0} };
    vector<vector<int>> nums2d4 = { {1,1,3,3},{3,1,4,2},{3,2,4,4},{1,3,2,4},{2,3,3,4} };
    Solution sl;
    // std::cout << sl.medianSlidingWindow(nums1d, 3) << std::endl;

    // std::cout << ios::left << std::setw(20) << "Hello, World!" << std::setw(5) << "a s " << 1 << std::endl;
    return 0;
    std::cout << "Hello World!\n";
}