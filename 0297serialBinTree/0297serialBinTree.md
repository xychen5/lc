
## 0297 二叉树序列化反序列化

### 1 题目：
[https://leetcode-cn.com/problems/serialize-and-deserialize-binary-tree/](https://leetcode-cn.com/problems/serialize-and-deserialize-binary-tree/)

### 2 解题思路：
- 1 bfs生成序列化的字符串numsStr
- 2 反序列化主要流程如下
  - 2.0 从numsStr转化成nums数组
  - 2.1 初始化curlevel为root
    - 2.2 计算出nextlevel有多少个节点
    - 2.3 按照2.3从2.0中取出对应的nextlevel
    - 2.4 将curLevel和nextlevel链接起来，很简单，curLevel取出来一个，nextLevel取出来2个
    - 2.5 更新curLevel为nextLevel，这样我们就可以处理下一层级

```cpp
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
```