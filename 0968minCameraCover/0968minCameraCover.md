## 0968minCameraCover 监控二叉树

### 1 题目
[https://leetcode-cn.com/problems/binary-tree-cameras/submissions/](https://leetcode-cn.com/problems/binary-tree-cameras/submissions/)

### 2 解题思路
- 1 首先得在思考的过程中，理解改题目的本质就是，
  - 1.1 在dfs的过程中，在每个节点可以放置或者不放置相机，重要的是，如何去体现放置还是不放置相机
  - 1.2 如何提现呢？很简单，比如root放置，然后你想让它的两个子节点都不放置，那么直接递归调用两个子节点的后代即可，具体看代码即可
  - 1.3 那么对于每个节点，有几种放置相机的可能呢？
    - 一共三种，要么root，要么left，要么right，然后取最小代价即可，这里以选择left子节点仔细说明：
```cpp
        // choosing: right 
        int tmpRightCover = min(
            // r的监控器对r的两个子节点都有监控作用，于是直接去计算两个子节点的子节点
            1 + minCameraCover(r_rll) + minCameraCover(r_rlr) + minCameraCover(r_rrl) + minCameraCover(r_rrr) + minCameraCover(r_l),
            min(
                // r的监控器对r的两个子节点中的右孩子有监控作用，于是计算方式变为算右孩子两个子节点加上左侧节点
                // partly ignore, will not put cam on r_rr, may on r_r
                1 + minCameraCover(r_rrl) + minCameraCover(r_rrr) + minCameraCover(r_rl) + minCameraCover(r_l),
                // r的监控器对r的两个子节点中的左孩子有监控作用，于是计算方式变为算左孩子两个子节点加上右侧节点
                // partly ignore, will not put cam on r_rl, may on r_l
                1 + minCameraCover(r_rll) + minCameraCover(r_rlr) + minCameraCover(r_rr) + minCameraCover(r_l)
            )
        );
```
- 2 优化思路：
  - 2.1 同一层递归里面，相同函数名不要反复出现，用临时变量存储以加速
  - 2.2 使用hash存储对应的节点的最小监控值，如果能在hash命中就不用反复计算
  - 2.3 优先计算小规模，然后计算大规模
- 3 关于为什么需要hash来避免反复计算：
  - 3.1 看例子：
[0,null,0,null,0,null,0,null,0,null,0,0,null,0,null,0,null,0,null,0,null,0,null,0,null,0,null,0,0,null,null,null,0,null,0,null,0,null,0,null,0,null,0,null,0,null,0,null,0,null,0,null,0,null,0,null,0,null,0,null,0,null,0,null,0,null,0,null,0,null,0,null,0,null,0,null,0,null]
  - 3.2 也就是单链表，你会发现，到达第4个节点，可以有两种监控方式，那么说明第4个节点的计算会重复2次，于是需要记忆化搜索

```cpp
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
    int level = 0;
    unordered_map<TreeNode* , int> memo;
    int minCameraCover(TreeNode* root) {
        ++level;
        if(nullptr == root) {
            return 0;
        }

        if(nullptr == root->left && nullptr == root->right) {
            return 1;
        }
        
        // dp:
        TreeNode* r_l = root->left;
        TreeNode* r_r = root->right;

        TreeNode* r_ll = getL(r_l);
        TreeNode* r_lr = getR(r_l);
        TreeNode* r_rl = getL(r_r);
        TreeNode* r_rr = getR(r_r);

        TreeNode* r_lll = getL(r_ll);
        TreeNode* r_llr = getR(r_ll);
        TreeNode* r_lrl = getL(r_lr);
        TreeNode* r_lrr = getR(r_lr);
        TreeNode* r_rll = getL(r_rl);
        TreeNode* r_rlr = getR(r_rl);
        TreeNode* r_rrl = getL(r_rr);
        TreeNode* r_rrr = getR(r_rr);
 
        int cover_r_lll = getFromMemo(r_lll);
        int cover_r_llr = getFromMemo(r_llr);
        int cover_r_lrl = getFromMemo(r_lrl);
        int cover_r_lrr = getFromMemo(r_lrr);
        int cover_r_rll = getFromMemo(r_rll);
        int cover_r_rlr = getFromMemo(r_rlr);
        int cover_r_rrl = getFromMemo(r_rrl);
        int cover_r_rrr = getFromMemo(r_rrr);

        int cover_r_ll = getFromMemo(r_ll);
        int cover_r_lr = getFromMemo(r_lr);
        int cover_r_rl = getFromMemo(r_rl);
        int cover_r_rr = getFromMemo(r_rr);

        int cover_r_l = getFromMemo(r_l);
        int cover_r_r = getFromMemo(r_r);

        // // choosing: root
        // int tmpRootCover = min(
        //     // min(
        //         // do not ignore
        //     1 + minCameraCover(r_ll) + minCameraCover(r_lr) + minCameraCover(r_rl) + minCameraCover(r_rr),
        //         // 1 + minCameraCover(r_l) + minCameraCover(r_r)
        //     // ),
        //     // partly ignore root choosen
        //     min(
        //         1 + minCameraCover(r_ll) + minCameraCover(r_lr) + minCameraCover(r_r), 
        //         1 + minCameraCover(r_rl) + minCameraCover(r_rr) + minCameraCover(r_l)
        //     )
        // );

        int tmpRootCover = min(
            1 + cover_r_ll + cover_r_lr + cover_r_rl + cover_r_rr,
            min(
                1 + cover_r_ll + cover_r_lr + cover_r_r,
                1 + cover_r_rl + cover_r_rr + cover_r_l
            )
        );

        // // choosing: right 
        // int tmpRightCover = min(
        //     // don't ignore, will not put cam on r_rl, r_rr
        //     1 + minCameraCover(r_rll) + minCameraCover(r_rlr) + minCameraCover(r_rrl) + minCameraCover(r_rrr) + minCameraCover(r_l),
        //     min(
        //         // partly ignore, will not put cam on r_rr, may on r_r
        //         1 + minCameraCover(r_rrl) + minCameraCover(r_rrr) + minCameraCover(r_rl) + minCameraCover(r_l),
        //         // partly ignore, will not put cam on r_rl, may on r_l
        //         1 + minCameraCover(r_rll) + minCameraCover(r_rlr) + minCameraCover(r_rr) + minCameraCover(r_l)
        //     )
        // );

        int tmpRightCover = min(
            1 + cover_r_rll + cover_r_rlr + cover_r_rrl + cover_r_rrr + cover_r_l,
            min(
                1 + cover_r_rrl + cover_r_rrr + cover_r_rl + cover_r_l,
                1 + cover_r_rll + cover_r_rlr + cover_r_rr +  cover_r_l
            )
        );

        // // choosing: left
        // int tmpLeftCover = min(
        //     1 + minCameraCover(r_lll) + minCameraCover(r_llr) + minCameraCover(r_lrl) + minCameraCover(r_lrr) + minCameraCover(r_r),
        //     min(
        //         1 + minCameraCover(r_ll) + minCameraCover(r_lrl) + minCameraCover(r_lrr) + minCameraCover(r_r),
        //         1 + minCameraCover(r_lr) + minCameraCover(r_lll) + minCameraCover(r_llr)  + minCameraCover(r_r)
        //     )
        // );
        int tmpLeftCover = min(
            1 + cover_r_lll + cover_r_llr + cover_r_lrl + cover_r_lrr + cover_r_r,
            min(
                1 + cover_r_ll + cover_r_lrl + cover_r_lrr + cover_r_r,
                1 + cover_r_lr + cover_r_lll + cover_r_llr + cover_r_r
            )
        );

        return min(tmpRootCover, min(tmpLeftCover, tmpRightCover));
    }

    TreeNode* getR(TreeNode* root) {
        if(nullptr == root) {
            return nullptr;
        } else {
            return root->right;
        }
    }
    TreeNode* getL(TreeNode* root) {
        if(nullptr == root) {
            return nullptr;
        } else {
            return root->left;
        }
    }

    int getFromMemo(TreeNode* root) {
        if(memo.end() == memo.find(root)) {
            memo[root] = minCameraCover(root);
        } 
        return memo[root];
    }
        
};
```