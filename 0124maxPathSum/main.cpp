#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <limits.h>
#include <numeric>

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
    int maxPathSum(TreeNode* root) {
        maxGain(root);
        return ans;
    }

    int maxGain(TreeNode* root) {
        if(root == nullptr) {
            return 0;
        }
        // 左侧的最大和是否比0大，比0小的话，那么这个左子树就直接舍弃
        int leftGain = max(maxGain(root->left), 0);
        // 右侧的最大和是否比0大
        int rightGain = max(maxGain(root->right), 0);

        // 当前节点和左右子树的链接的最大路径
        ans = std::max(ans, leftGain + rightGain + root->val);
        // 当前节点的最大路径的值
        return root->val + std::max(leftGain, rightGain);
    }
private:
    int ans = INT_MIN;
};

int main() {

    // std::cout << ios::left << std::setw(20) << "Hello, World!" << std::setw(5) << "a s " << 1 << std::endl;
    return 0;
}