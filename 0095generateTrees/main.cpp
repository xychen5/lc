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