## 0902atMostNGivenDigitSet 最大为 N 的数字组合

### 1 题目
[https://leetcode.cn/problems/numbers-at-most-n-given-digit-set/](https://leetcode.cn/problems/numbers-at-most-n-given-digit-set/)

### 2 解题思路
- 1 解题思路：
  - 1.1 数位dp： p[i] 表示小于等于 N 中最后 |N| - i 位数的合法数的个数，例如当 N = 2345 时，dp[0], dp[1], dp[2], dp[3] 分别表示小于等于 2345, 345, 45, 5 的合法数的个数。 且digits为1到9
  - 1.2 dp的过程:考虑dp[2]的情况：
    - 此时求小于345的合法个数
      - 当第一个位为1,2，则 dp[2] += pow(digits.size(), len(345) - 1)
      - 当第一位为3，则dp[2] += dp[3]

```cpp
class Solution {
public:
    int atMostNGivenDigitSet(vector<string>& digits, int n) {
        string sn = to_string(n);
        int len = sn.size();
        int bits = digits.size();
        // p[i] 表示小于等于 N 中最后 |N| - i 位数的合法数的个数，例如当 N = 2345 时，
        // dp[0], dp[1], dp[2], dp[3] 分别表示小于等于 2345, 345, 45, 5 的合法数的个数。
        // 且digits为1到9

        vector<int> dp(len + 1); 
        dp[len] = 1; // 方便当 i=len-1的时候使用
        
        for(int i = len - 1; i >= 0; --i) {
            int curDigit = sn[i] - '0';
            cout << curDigit << endl;
            for(auto& bit : digits) { // 取bit作为首位
                // 比如i = 1,那么dp[1]表示小于345的个数，第一个if中，bit可以取到1 和 2
                if(curDigit > bit[0] - '0') {  // 由于首位选择的数字比n的第i位置要小，于是剩下的每个位置的可能性为bits种
                    dp[i] += pow(bits, len - i - 1);
                } else if(curDigit == bit[0] - '0') {
                    dp[i] += dp[i+1];
                }
            }
            // cout << i << " | " << dp[i] << endl;
        }
        
        // dp[0]是小于2345的长度为4的所有数字的可能，然后把长度为1到3的可能全部加起来
        for(int i = 1; i < len; ++i) {
            dp[0] += pow(bits, i);
        }
        return dp[0];
    }
};
```