## 10 isMatch 正则表达式匹配

### 1 题目
[https://leetcode-cn.com/problems/regular-expression-matching](https://leetcode-cn.com/problems/regular-expression-matching)

### 2 解题思路
- 0 心得：
  - 递归适用于减小规模后问题的处理方式不会发生改变的场景
  - 对于递归，得明白当层递归处理会如何将问题规模减小
- 1 个人思路：
  - 首先这个字符串匹配，需要理解每一次能够用p去匹配什么？然后怎么匹配
  - 1.1 首先每次递归，p的规模减小肯定是在p的头部： 对于p的匹配类型，有3种：
    - 1.1.1 s = ab, p = ab, 那么就用p的第一个字母去匹配
    - 1.1.2 s = a, p = ., 同样需要用p的第一个字幕去匹配
    - 1.1.3 带*的，这个需要将p的头两个拿去和s匹配：
      - s = a, p1 = .\*, p2 = a*,这两种情况，都是满足需要的
      - s = a, p1 = c*.\*，**那么第一个c*是不匹配的，同样的还有.\*是否需要匹配的问题**
  - 然后大致的递归思路：
    - 1.1 首先从p的头部分析是哪种子模式
    - 1.2 按照该种子模式匹配
    - 1.3 递归到下层的p和s，这样p和s都因为1.1~1.2的过程中变小了，完成了使用递归解决问题的思路
  - 递归返回？
    - 1.1 s的长度为0？
    - 1.2 p的长度为0？
  - 对于上述过程不清楚的请以下面两个结果作为例子：
```log  
"bcabac"
"a*a*.*b*b*"
return: true

"a"
".*..a*"
return false
```

```cpp
class Solution {
public:
    bool isMatch(string s, string p) {
        return greadyMatch(s, p);
    }

    bool greadyMatch(string s, string p) {
        int sLen = s.size();
        int pLen = p.size();
        // cout << "sLen & pLen => " << sLen << " " << pLen << s << " " << p << endl;
        if(pLen == 2 && p[0] == '.' && p[1] == '*') {
            return true;
        }

        if(pLen == 1) {
            if(sLen != 1) {
                return false;
            }
            return p[0] == '.' ? true : p[0] == s[0];
        }
        
        if(sLen == 0) {
            if(pLen == 0) {
                return true;
            }
            if(pLen == 2) {
                if(p[1] == '*') {
                    return true;
                }else {
                    return false;
                }
            } else {
                if(p[1] == '*') {
                    return greadyMatch(s, p.substr(2));
                } else {
                    return false;
                }
            }
        }

        if(pLen == 0) {
            return sLen == 0;
        }

        // match as much as possible
        char head0 = p[0];
        char head1 = p[1];
        bool res = false;

        if(p[0] == '.') {
            if(p[1] == '*') {
                // match any len >= 1 of s, when len == 0, then not match
                for(int len = 0; len <= sLen; ++len) {
                    res = res || greadyMatch(s.substr(len), p.substr(2));
                    // cout << "tried: " << s.substr(len) << " " << p.substr(2) << endl;
                }
                return res;
            } else { 
                return greadyMatch(s.substr(1), p.substr(1));
            }
        } else {
            // p[0] = a~z
            if(p[0] != s[0]) {
                if(p[1] == '*') {
                    // cout << p.substr(2) << "\nculled!" <<endl;
                    return greadyMatch(s, p.substr(2));
                } else {
                    return false;
                }
            } else {

                if(p[1] == '*') {
                    int sameLen = s.find_first_not_of(p[0]);
                    if(sameLen == -1) {
                        sameLen = sLen;
                    }
                    // cout << "sameLen2 -> " << sameLen << s.substr(1) << p.substr(2) << endl;
                    // when len = 0, not use this * to match
                    for(int len = 0; len <= sameLen; ++len) {
                        res = res || greadyMatch(s.substr(len), p.substr(2));
                    }
                    return res;
                } else {
                    return greadyMatch(s.substr(1), p.substr(1));
                }
            }
            
        }
        
        // never be executed
        return res;
    }
};
```
