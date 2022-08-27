## 0322coinChange 零钱

### 1 题目
[https://leetcode.cn/problems/coin-change/](https://leetcode.cn/problems/coin-change/)

### 2 解题思路
- 1 解题思路
  - dp[sum][i]表示利用前i个coins得到sum的最少coins数，那么我们可以遍历最后一个coin用了几次
    - dp[sum][i] = min(dp[sum][i], min(dp[sum][i-1], useCnt + dp[sum - useCnt * coins[i-1]][i-1]));
  - 但是注意题目，问的是用上所有的coins，也就是我不关心前i的情况
  - 那么考虑最后一个硬币用的是谁，也就是遍历最后一个硬币即可： i : 1->n
  - dp[sum][coins.size()] = min(dp[sum][coins.size()], 1 + dp[sum - coins[i-1]][coins.size()]);
  - 也就是一维dp即可：
    - dp[sum] = min(dp[sum], 1 + dp[sum - coins[i-1]]);

```cpp
class Solution {
public:
    int coinChange(vector<int>& coins, int amount) {

        // dp[sum][i]: 表示可以用前i种硬币凑成sum的最少硬币数目，i用不上，直接简化成固定值，为一维dp
        vector<vector<long>> dp(amount + 1, vector<long>(coins.size() + 1, INT_MAX));
        for(int i = 0; i <= coins.size(); ++i) {
            dp[0][i] = 0;
        }

        for(int sum = 1; sum <= amount; ++sum) {
            for(int i = 1; i <= coins.size(); ++i) { // 枚举最后用的一个硬币的所有可能性
                if(sum >= coins[i - 1]) {
                    dp[sum][coins.size()] = min(dp[sum][coins.size()], 1 + dp[sum - coins[i-1]][coins.size()]);
                }
                
                // 这个for循环，可以发现，当coins大于
                // 考虑conins[i-1]用的个数的所有情况
                // for(int useCnt = 0; useCnt * coins[i-1] <= sum; ++useCnt) {
                //     dp[sum][i] = min(dp[sum][i], min(dp[sum][i-1], useCnt + dp[sum - useCnt * coins[i-1]][i-1]));
                // }
                // cout << "sum/i: " << sum << "/" << i << " " << dp[sum][i] << endl;
            }
        }
        return dp[amount][coins.size()] == INT_MAX ? -1 : dp[amount][coins.size()];
    }
};
```

## 3 考虑一个今天的题目
有技能skills，然后总蓝是MP，问你，MP最多打出多少伤害？
- dp[MP]表示伤害，用所有的skills
- 同样的，只需要考虑最后一个技能用的什么伤害即可
- if(MP > skill[i].mp)
-     dp[MP] = max(dp[MP], dp[MP - skill[i].mp] + skill[i].damage)

如果说是，是不是能够刚好装满？和2很像
dp[MP] = dp[MP] || dp[MP - skill[i].mp]
