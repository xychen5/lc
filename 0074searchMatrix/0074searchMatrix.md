## 0074搜索二维矩阵

### 1 题目：
[https://leetcode-cn.com/problems/search-a-2d-matrix/](https://leetcode-cn.com/problems/search-a-2d-matrix/)

### 2 解题思路：
可以联想到跳跃表[https://en.wikipedia.org/wiki/Skip_list](https://en.wikipedia.org/wiki/Skip_list)
- 1 首先搜索位于哪一列，可以采用二分法搜索。
- 2 得到目标列以后，在目标行内采用二分法搜索。