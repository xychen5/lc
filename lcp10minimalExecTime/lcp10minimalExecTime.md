## lcp10minimalExecTime 二叉树任务调度

### 1 题目
[https://leetcode.cn/problems/er-cha-shu-ren-wu-diao-du/](https://leetcode.cn/problems/er-cha-shu-ren-wu-diao-du/)

### 2 解题思路
- 1 解题思路：
  - 1.1 主要是，将整个子树一起去考虑，将一整颗子树的时间，分成：总时间，和最大可并行时间
  - 1.2 则结果为： 总时间 - 最大可并行时间
  - 1.3 对于一个root，其左和右子树的总时间以及最大可并行时间分别记作sa/pa,sb/pb,则有以下两种情况：
    - 1.3.1 当sa >= sb的情况：
      - 什么时候两个子树可以完全并行？
        - 当 sa - sb <= 2 * pa，也就是sa - 2 * pa为左侧子树的串行的时间，串行时间小于sb，则，可以将：左子树的并行部分中的 ( sa - sb ) / 2 部分并行执行（之所以可以有这么多并行的部分， 是因为确保了： pa >= (sa - sb) / 2），然后左子树和 右子树剩下的部分分别在两个cpu上串行执行即可
      - 什么时候会有一个子树多出来一部分？
        - 当 sa - sb > 2 * pa, 也就是两个子树的差距大于pa的并行部分的2倍，导致左子树必然多出来一些，只能最后自己串行，多出来的串行部分的大小为：sa - sb - 2 * pa,然后最并行时间 = （总时间 - 串行） / 2 = (sa + sb - (sa - sb - 2 * pa)) / 2 = sb + pa

```cpp
class Solution {
public:

    // return <sum of all time, max parallel>
    pair<int, double> DFS(TreeNode* root) {
        if(nullptr == root) {
            return {0, 0.0};
        }

        auto lc = DFS(root->left);
        auto rc = DFS(root->right);
        int sa = lc.first; // sum of a
        double pa = lc.second; // parallel of a

        int sb = rc.first;
        double pb = rc.second;

        double tot = root->val + sa + sb;
        // cout << "sa/pa/sb/pb: " << sa << "/" << pa << "/" << sb << "/" << pb << "\n";
        // 能够全部并行，所以p = (sa + sb) / 2
        if((sa - sb <= 2*pa && sa >= sb) || \
           (sb - sa <= 2*pb && sb >= sa)) {
            double p = (sa + sb) / 2.0;
            return {tot, p};
        } 
        if(sa - sb > 2 * pa) {
        // 无法全部并行，需要将sa - sb - 2 * pa,也就是sa的串行就比sb大，所以多出来的这部分需要串行
        // 那么并行时间为： t = (sa + sb - (sa - sb - 2*pa)) / 2 = sb + pa;
            return {tot, sb + pa};
        } else {
            return {tot, sa + pb};
        }
    }


    double minimalExecTime(TreeNode* root) {
        auto res = DFS(root);
        return res.first - res.second;
    }
};
```