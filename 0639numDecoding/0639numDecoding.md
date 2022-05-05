## 0639numDecoding 解码方法数

### 1 题目
[https://leetcode-cn.com/problems/decode-ways-ii/](https://leetcode-cn.com/problems/decode-ways-ii/)

### 2 解题思路
- 1 解题思路：dp 参考官方解答
  - 1.1 这里概括总结一下：dp[i] 表示字符串 s 的前 i 个字符 s[1:i] 的解码方法数
  - 1.2 那么就会产生一个问题，dp[i]会被哪些数字影响？（这个思考过程本身很重要）
    - 不言而喻：当最后一次匹配用一个字符完成，就是被dp[i-1]影响，若最后一次解码用了两个方法，则被dp[i-2]影响
    - 很显然 dp[i] = a * dp[i-1] + b * dp[i-2]，a代表最后一次解码仅用一个字符（即s[i]）的方法数，b代表最后一次解码用二个字符（s[i-1]s[i]这两个字符）的方法数
  - 1.3 最后注意到，上述dp总是只有三个变量，于是空间复杂度可以到o1，然后注意一下dp启动需要2个已知值，这就是dp的初始化
```cpp
class Solution {
public:
    static constexpr int mod = 1000000007;
    int use1Bit(char c) {
        if('*' == c) {
            return 9;
        }

        if('0' == c) {
            return 0;
        }
        return 1;
    }
    
    // string: ........c1c2
    int use2Bit(char c1, char c2) {
        if('*' == c1 && '*' == c2) {
            return 15;
        } else if('*' != c1 && '*' == c2) {
            if('1' == c1) {
                return 9;
            } else if('2' == c1) {
                return 6;
            } else {
                return 0;
            }
        } else if('*' == c1 && '*' != c2) {
            if(c2 <= '6') {
                return 2;
            }
            return 1;
        } else {
            if('1' == c1 || ('2' == c1 && ('0' <= c2 && '6' >= c2))) {
                return 1;
            }
            return 0;
        }
        return -1;
    }

    int numDecodings(string s) {
        int n = s.size();

        // dp[i] 表示字符串 s 的前 i 个字符 s[1:i] 的解码方法数
        vector<long long> dp(n+1, 0);

        dp[0] = 1;
        dp[1] = use1Bit(s[0]);
        for(int i = 1; i < n; ++i) {
            dp[i+1] = (dp[i] * use1Bit(s[i]) % mod + dp[i-1] * use2Bit(s[i-1], s[i]) % mod) % mod; 
        }

        return dp[n];
    }
};
```