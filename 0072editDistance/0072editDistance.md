## 0072editDistance 编辑距离

### 1 题目
[https://leetcode.cn/problems/edit-distance/submissions/](https://leetcode.cn/problems/edit-distance/submissions/)

### 2 解题思路
- 1 解题思路
  - 首先：暴力搜索：对于当前offset位置的字符，有4种选择，插入，删除，替换，啥也不干（替换如果是相同的字符，那就是当前case）
  - 但是太慢了：
  - 注意到：其实每一次对A的操作有三种，可以将A的删除替换成B的插入来达到同样的效果，比如A:acdd，B:add，那么offset等于1的时候，A删除C等于B插入c，只不过一个offset不后移，一个后移动
  - 想到动态规划的方案，因为我们仅仅关心A[:i]和B[:j]达到最小所用代价，那么转义方程就是：
```cpp
  dp[i][j] = min(
                    1 + dp[i][j - 1], // word2 insert == word1 del
                    min(
                        1 + dp[i - 1][j], // word1 insert
                        dp[i - 1][j - 1] + (word1[i - 1] != word2[j - 1]) // word1 replace
                    )
                );
```

```cpp

```
