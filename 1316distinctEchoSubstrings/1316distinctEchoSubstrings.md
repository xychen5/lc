## 1316 distinctEchoSubstrings 不同的循环子字符串

### 1 题目
[https://leetcode-cn.com/problems/distinct-echo-substrings/](https://leetcode-cn.com/problems/distinct-echo-substrings/)

### 2 解题思路
- 1 注意一点，abcabcabc，其中三个abc连在一起其实它的链接单元也是abc，和两个abc链接在一起是没有区别的，并不是让你求将连接体连接以后的子串究竟有多少
- 2 普通思路：暴力解法
- 4 注意string_view本身和string的区别
> 由于string需要动态分配内存而string_view不需要，string_view仅仅将字符串复制到静态数据区，而表示一个string_view也只<br>需要一个地址和字符串的长度，且其substr函数的时间是常数级别，而string的substr则是和子串大小成线性相关的
- 3 优化思路：
  - 字符串匹配使用rabin-karp算法： [https://xychen5.github.io/2021/12/28/rabinKarp/](https://xychen5.github.io/2021/12/28/rabinKarp/)
``` cpp
class Solution {
public:
    int distinctEchoSubstrings(string text) {
        // for each len's substr from 0 to text.size - 1
        // check if we could find a solution
        int n = text.size();
        unordered_set<string_view> ans;
        string_view text2(text);
        for(int len = 1; len < n; ++len) {
            for(int l = 0; l < n - len + 1; ++l) {
                // curSubStr: text[l, l + len - 1], then, check if curSubStr equal text[l + len, l + 2*len - 1]
                string_view curSubStr(text2.substr(l, len));
                // cout << curSubStr << " " << text.substr(l + len, len) << " " << l + 2 * len - 1 << endl;
                if(l + 2 * len - 1 < n && curSubStr == text2.substr(l + len, len) && 0 == ans.count(curSubStr)) {
                    ans.insert(curSubStr);
                }
            }
        }
        return ans.size();
    }
};
```
