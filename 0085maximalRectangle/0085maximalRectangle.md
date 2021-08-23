## 0085最大矩形

### 1 题目：
[https://leetcode-cn.com/problems/maximal-rectangle/submissions/](https://leetcode-cn.com/problems/maximal-rectangle/submissions/)

[https://leetcode-cn.com/problems/largest-rectangle-in-histogram/](https://leetcode-cn.com/problems/largest-rectangle-in-histogram/)

### 2 解题思路：
- 1 暴力法：
  - 1.1 枚举矩阵中的两两点对，然后统计其中1的个数是否和等于这两个点对的矩形的面积，复杂度O(N^3)
  - 1.2 优化：
    - 参考[https://leetcode-cn.com/problems/largest-rectangle-in-histogram/](https://leetcode-cn.com/problems/largest-rectangle-in-histogram/)改题目的暴力解法，也就是，对于矩阵形成后柱状图的每一列，从每一个点开始枚举，然后求出该列的最大矩形，复杂度 O(N^3)
- 2 单调栈：
  - 2.1 想法很简单，遍历上述的柱状图的一列，栈顶总是最大，栈底最小，一旦有小于等于前栈的值，那么栈里面那些小于等于当前栈顶的值都不可能再在遍历的后续位置发生作用了，因为已经有小于等于它的值出现了，所以我们把这些值弹出然后算弹出的这一部分的体积，那么栈里面剩下的就是任然能够为后续遍历的位置贡献面积的值，所以就是这样，具体的看代码吧。

