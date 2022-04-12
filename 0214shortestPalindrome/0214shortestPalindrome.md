## 0214shortestPalindrome 最短回文串

### 1 题目
[https://leetcode-cn.com/problems/shortest-palindrome/](https://leetcode-cn.com/problems/shortest-palindrome/)

### 2 解题思路
- 1 使用KMP算法，能够在text(n)字符串中搜索出tar(m)字符串的所有出现位置复杂度为o(m+n)，那么由于本题目求解的是最短回文串，也就是要求最少的头部添加，尽可能利用字符串本身的回文信息，于是这里看个例子：
  - 1.1 see: our target is to find the "b c c b"，so we use kmp
    - s =       b c c b a e
    - rs =  e a b c c b 
    - all = b c c b a e # e a b c c b 
  - 1.2 我们用s + 分隔符 + reverse_s得到all，对于all的最后一个前缀函数pi.back()，就说明了最长有多长的后缀和前缀相等，也就是b c c b这一个公共部分，那么吧剩余的拼上去就行了
```cpp
class Solution {
public:
    string shortestPalindrome(string s) {
        // prefix function && kmp: https://oi-wiki.org/string/kmp/#_10
        int len = s.size();
        string rs = s;
        reverse(rs.begin(), rs.end());

        string all = s + "#" + rs;
        vector<int> pi(all.size(), 0);
        
        // see: our target is to find the "b c c b"，so we use kmp
        // s =       b c c b a e
        // rs =  e a b c c b 
        // all = b c c b a e # e a b c c b 
        // 求解pi[i]
        for(int i = 1; i < all.size(); ++i) {
             // i - 1的前缀函数的值，有s[0:j] == s[i - j : i - 1]
            int j = pi[i - 1];
            // 当s[i] != s[j]，说明s[i]这个字符无法成为后缀的最后一个字符，此时pi[i] = 0，于是得一直找到下一个j，直到j = 0，或者s[i] == s[j]
            while(j > 0 && all[i] != all[j]) {
                j = pi[j - 1];
            }

            // 倘若s[i] == s[j]，那么就有s[0:i-1]这个字串的前缀函数的值为j，然后加上最后一个字符s[i]，所以j++
            if(all[i] == all[j]) {
                j++;
            }
            pi[i] = j;
        }

        int commonLen = pi.back();
        if(commonLen == len) {
            return s;
        }
        return rs.substr(0, len - commonLen) + s;
    }
};
```