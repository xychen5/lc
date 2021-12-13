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