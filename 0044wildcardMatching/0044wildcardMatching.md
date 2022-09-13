## 0044wildcardMatching 通配符匹配

### 1 题目
[https://leetcode.cn/problems/wildcard-matching/](https://leetcode.cn/problems/wildcard-matching/)

### 2 解题思路
- 1 解题思路
  - dp[i][j] 表示s[:i]和s[:j]是否match
  - 然后讨论：p[j]的三种可能，我们主要是看：为*的情况
  - *：
    - dp[i][j] ||= dp[i][j-1] *当成空的串
    - dp[i][j] ||= dp[i-k][j-1] *去匹配i-k到i的字符串
      - 但是这里我们可以换一种想法：
        - p[j]如果匹配掉了s[i]，那么就是：dp[i][j] ||= dp[i-1][j]
        - p[j]如果没有匹配掉了s[i]，那么就是：dp[i][j] ||= dp[i][j-1]


```cpp
class Solution {
public:
    bool isMatch(string s, string p) {
        int sLen = s.size();
        int pLen = p.size();
        vector<vector<int>> dp(sLen + 1, vector<int>(pLen + 1, false));

        dp[0][0] = true;

        bool allStar = true;
        for(int i = 1; i <= pLen; ++i) {
            if((p[i - 1] == '*') && allStar) {
                dp[0][i] = true;
            } else {
                dp[0][i] = false;
                allStar = false;
            }
        }

        for(int i = 1; i <= sLen; ++i) {
            dp[i][0] = false;
        }

        // dp[i][j]: wether s[:i] match p[:j] ?
        for(int len = 2; len <= sLen + pLen; ++len) {
            for(int j = 1; j <= pLen; ++j) {
                int i = len - j;
                if(!(1 <= i && i <= sLen)) {
                    continue;
                }

                if('?' == p[j - 1]) {
                    dp[i][j] = dp[i - 1][j - 1];
                } else if('*' == p[j - 1]) {
                    // * match nothing
                    dp[i][j] = dp[i][j] || dp[i][j - 1];
                    // * match k's substr from i - k to i in s
                    dp[i][j] = dp[i][j] || dp[i - 1][j];
                    // for(int k = 1; k <= i; ++k) {
                    //     dp[i][j] = dp[i][j] || dp[i - k][j - 1];
                    //     // cout << "- i - k/j - 1: " << i - k << "/" << j - 1 << endl;
                    // }
                } else { // 'a' - 'z'
                    dp[i][j] = dp[i - 1][j - 1] && (s[i - 1] == p[j - 1]);
                }

                // cout << "i/j: " << i << "/" << j << " " << dp[i][j] << endl;
            }
        }
        
        return dp[sLen][pLen];
    }
}
```
