## 0413等差数列划分

### 1 题目
[https://leetcode-cn.com/problems/arithmetic-slices/](https://leetcode-cn.com/problems/arithmetic-slices/)

### 2 解题思路
很简单的o(n)解法，采用tmp记录当前的公差，不断向后遍历，当不能使用tmp作为公差，则更新tmp即可