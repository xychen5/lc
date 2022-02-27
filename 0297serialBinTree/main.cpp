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
#include <string>

using namespace std;

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Codec {
public:

    int nullNode = 1001;
    string nullNodeStr = "1001";

    // Encodes a tree to a single string.
    string serialize(TreeNode* root) {
        if( nullptr == root) {
            return to_string(1001);
        }

        string res = ""; // std::to_string(root->val) + "," + serialize(root->left) + "," + serialize(root->right);
        // bfs
        deque<TreeNode*> curLevel;
        curLevel.push_back(root);
        while(!curLevel.empty()) {
            TreeNode* curNode = curLevel.front();
            curLevel.pop_front();
            if(nullptr == curNode) {
                res += nullNodeStr + ",";
                continue;
            } else {
                res += to_string(curNode->val) + ",";
            }
            curLevel.push_back(curNode->left);
            curLevel.push_back(curNode->right);
        }
        // cout << res << endl;
        return res.substr(0, res.length() - 1);
    }

    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data) {
        queue<int> nums;
        stringstream ss(data);
        string numStr;
        while(getline(ss, numStr, ',')) {
            nums.push(stoi(numStr));
        }

        if(nullNode == nums.front()) {
            return nullptr;
        }
        TreeNode* root = new TreeNode(nums.front());
        nums.pop();
        deque<TreeNode*> curLevel;
        curLevel.push_back(root);
        while (!curLevel.empty()){
            // prepare next level
            queue<TreeNode*> nextLevel; 
            int nextLevelCnt = 0;
            for(auto& node : curLevel) {
                if(nullptr != node) {
                    nextLevelCnt += 2;
                }
            }

            while(nextLevelCnt > 0) {
                if(nullNode == nums.front()){
                    nextLevel.push(nullptr);
                } else {
                    nextLevel.push(new TreeNode(nums.front()));
                }
                --nextLevelCnt;
                nums.pop();
            };
            
            // attach nextLevel to curLevel
            int nextLevelIdx = 0;
            int curLevelSize = curLevel.size();
            while(curLevelSize) {
                TreeNode* curNode = curLevel.front();
                curLevel.pop_front();
                if(nullptr != curNode) {
                    curNode->left = nextLevel.front();
                    curLevel.push_back(nextLevel.front());
                    nextLevel.pop();
                    curNode->right = nextLevel.front();
                    curLevel.push_back(nextLevel.front());
                    nextLevel.pop();
                }
                --curLevelSize;
            }
            // move to nextLevel
        }

        return root;
    }
};

// Your Codec object will be instantiated and called as such:
// Codec ser, deser;
// TreeNode* ans = deser.deserialize(ser.serialize(root));

int main() {
    // vector<int> nums = {1, 15, 5, 11};
    // vector<int> nums = {1, 3};
    // vector<int> nums = {1, 3};
    vector<int> nums = {1, 2, 2, 3};
    Solution sl;
    // std::cout << sl.largestRectangleArea(nums) << std::endl;
    std::cout << "Hello, World!" << std::endl;
    return 0;
}
