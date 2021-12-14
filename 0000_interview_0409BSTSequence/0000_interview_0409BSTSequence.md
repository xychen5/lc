##  面试题 04.09. 二叉搜索树序列

### 1 题目
[https://leetcode-cn.com/problems/bst-sequences-lcci/](https://leetcode-cn.com/problems/bst-sequences-lcci/)

### 2 解题思路
- 1 首先明确一点，递归的主体为，从root对应的tree中获取所有可能的bst子树序列
  - 1.1 输入： treeNode*
  - 1.2 返回： vector<vector<int>>
- 2 于是递归思路的想法就来了：
  - 2.1 对于一个root如何生成其所有可能的二叉树序列呢？我们只考虑第1层到第2层的(因为其他所有层的递归都是一样的逻辑，除非返回层不太一样)
    - 2.1.1 从root的左右子树获取其所有的左边子树序列lSeqs和右边子树序列rSeqs
    - 2.1.2 对lSeqs和rSeqs里的数据进行两两拼接，得到一组合合并序列，那么每一个两两拼接，可以获得很多个序列，具体拼接如下：
    - 2.1.3 那么很显然，记lSeqs和rSeqs中的一个两两拼接来自：lSeq，rSeq的长度分别为l和r，总长度为n，则有从n中选择l个的拼接方法，类似题目如下：
[1569. 将子数组重新排序得到同一个二叉查找树的方案数https://leetcode-cn.com/problems/number-of-ways-to-reorder-array-to-get-same-bst/](https://leetcode-cn.com/problems/number-of-ways-to-reorder-array-to-get-same-bst/)

经典写法：
```cpp
    void selectKFromN(int st, int k, vector<vector<int>>& res, vector<int>& nums, vector<int>& tmpRes) {
        if(k == 0) {
            res.emplace_back(tmpRes);
            return;
        }
        for(int i = st; i < nums.size() - k + 1; ++i) {
            tmpRes.emplace_back(nums[i]);
            selectKFromN(i + 1, k - 1, res, nums, tmpRes);
            tmpRes.pop_back();
        }
    }
```


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
class Solution {
public:
    vector<vector<int>> BSTSequences(TreeNode* root) {
        return getSequencesFromRoot(root);
    }

    vector<vector<int>> getSequencesFromRoot(TreeNode* root) {
        if(nullptr == root) {
            return {{}};
        }
        
        vector<vector<int>> sequences;
        // for(auto seq : s) {
        //     s.emplace_back(root->val);
        // }
        // get left sequences and right
        vector<vector<int>> lSeqs = getSequencesFromRoot(root->left);
        vector<vector<int>> rSeqs = getSequencesFromRoot(root->right);
        int lSize = lSeqs[0].size();
        int rSize = rSeqs[0].size();
        
        // cout << "d0" << endl;
        // select lSize's positions in lSize + rSize + 1 's vector
        vector<vector<int>> res;
        vector<int> nums;
        for(int i = 0; i < lSize + rSize; ++i) {
            nums.emplace_back(i+1);
        }
        vector<int> tmpRes;
        // cout << "d1" << endl;
        selectKFromN(0, lSize, res, nums, tmpRes);
        
        int seqLen = lSeqs[0].size() + rSeqs[0].size() + 1;
        // cout << "d2 " << lSize << "@" << rSize << "=" << seqLen << endl;
            
        for(auto & lSeq : lSeqs) {
            for(auto & rSeq : rSeqs) {
                
                // cout << "d3" << endl;
                vector<int> tmpSeq(seqLen);
                tmpSeq[0] = root->val;

                for(auto & idxVecForLeft : res) {
                    int curLeft = 0;
                    int curRight = 0;
                    int lastLeft = 1;
                    vector<bool> forRight(seqLen, true);
                    
                    // cout << "d4" << endl;
                    for(auto lIdx : idxVecForLeft) {
                        tmpSeq[lIdx] = lSeq[curLeft++];
                        forRight[lIdx] = false;
                    }
                    for(int i = 1; i < seqLen; ++i) {
                        if(forRight[i]) {
                            tmpSeq[i] = rSeq[curRight++];
                        }
                    }
                    sequences.emplace_back(tmpSeq);
                }
            }
        }

        return sequences;
    }

    void selectKFromN(int st, int k, vector<vector<int>>& res, vector<int>& nums, vector<int>& tmpRes) {
        if(k == 0) {
            res.emplace_back(tmpRes);
            return;
        }
        for(int i = st; i < nums.size() - k + 1; ++i) {
            tmpRes.emplace_back(nums[i]);
            selectKFromN(i + 1, k - 1, res, nums, tmpRes);
            tmpRes.pop_back();
        }
    }
}
```
