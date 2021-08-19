## 1 题目：

[https://leetcode-cn.com/problems/beautiful-arrangement](https://leetcode-cn.com/problems/beautiful-arrangement)

## 2 解题思路：
回溯即可，遍历每一个位置上的每一个数字，遍历方式：
对于第i位，尝试剩下的n-i个数，若其中有些合适，则遍历下一层的第i+1位，不合适则返回上一层，也就是第i-1位的遍历。
