## 0516 最长回文子序列

### 1 题目：
[https://leetcode-cn.com/problems/longest-palindromic-subsequence/](https://leetcode-cn.com/problems/longest-palindromic-subsequence/)

### 2 解题思路
采用动态规划，记录： s[i][j]为从 char[i] 到char[j]的最大回文串的值。
- 1 若： char[i-1] == char[j+1]， 则s[i-1][j+1] = s[i][j] + 2,

- 2 若： char[i-1] != char[j+1]， 则无法扩展长度，则： s[i-1][j+1] = max(s[i][j+1], s[i-1][j+1]);
- 3 初始化时候，需要从 i = j处全部初始化为1，然后遍历方式为斜着遍历：
for(i: n-1 -> 0){
    for(j: 0-> i){
        k = j+1;
        ...
    }
}
之所以可以这样更新的原因是，这个回文串不需要连续。

### 2.1 我的思路
假设有a f g h e g c g e h这么一串：
首先遍历char的数组到第i个，然后每遍历到一个位置，就建立一个数组，得到一个历史二维数组。 当遍历的第i个时候，搜索每一个历史二维数组，当能够和栈顶的1个或者2个（之所以是栈顶的1个or2个的原因是： gg， ghg都是回文串）形成字符串的时候，就弹出能够形成回文串的字符串，更新当前最大结果，比如：
i  建立的数组
0  a
1  a f
2  a f g
3  a f g h 
...
4  a f g h e
5  a f g h e g, 因为当前字符为e，则搜索上面0到4的历史数组，发现2,3可以形成gg和ghg的回文串，将他们弹出来，然后更新最大的回文串作为结果。
显然这个复杂度，为： O(n ^ 2), 空间复杂度为O(n ^ 2)

### 2.2 处理回文串，创造一个反序列找公共子串即可
