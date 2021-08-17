## 1583 统计不开心的朋友的个数

### 1 题目
[https://leetcode-cn.com/problems/count-unhappy-friends/](https://leetcode-cn.com/problems/count-unhappy-friends/)

### 2 解题思路
很普通，如下：
```go
res = 0
for each person p1:
    for each(name as betterThanP2) in p1's better matched ones than p2(p1's paired one):
        if(p1 is a better match for betterThanP2)：
	    ++res
return res;
```

关键有两点：

- 1 给定一个p1，如何快速找他的match？
  - 使用unnordered_map作为hash
- 2 如何快速判定p1对pi和pj谁是更好的match？
  - 使用二维数组rank，rank[i][j]表示i对j的打分，实际上简单的写成j在i里面的喜欢列表里的第几位就好了，那么rank[i][j]越低，就说明i对j越满意
