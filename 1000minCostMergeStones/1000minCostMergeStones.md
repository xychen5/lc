## 1000minCostMergeStones 合并石头最低成本

### 1 题目
[https://leetcode.cn/problems/minimum-cost-to-merge-stones/](https://leetcode.cn/problems/minimum-cost-to-merge-stones/)

### 2 解题思路
- 1 解题思路:
  - 首先考虑：区间dp
    - dp[i][j]表示合并i到j的最小代价是多少，且合并完成以后最多的堆数目为k
    - dp[i][j] = min(dp[i][m] + dp[m + 1][j], dp[i][j]);
    - m就是ij中的所有可能的分割点
    - 如果i,j能够合并，那么就是说，dp[i][j]需要再加上从左边一堆和右边k-1堆合并成一堆的代价
  - 注意最关键的，从区间长度小的开始dp，所以dp应该是从：len，i，和p（区间长度，起点，分割点）做dp
  - 需要观察到：1）合并少于K堆石头的成本是0； 2）合并K堆石头的成本是石头数量总和
```cpp
class Solution {
public:
    int mergeStones(vector<int>& stones, int k) {
        // 每次合并，数目减少 k - 1，也就是说：个数必须能够模k-1 = 1
        // interval dp: 因为merge的必须能够和左边merge
        // dp[i, j] = min({ dp[i][m] + cost(merge(m with len = k)) + dp[m + k][j] | i <= m <= j - k }), j - i >= k - 1   
        // =>
        // dp[i, j] = min({ dp[i][m] + dp[m + 1][j] | i <= m <= j - k, m是分界点，}), j - i >= k - 1   

        int n = stones.size();
        vector<vector<int>> dp(n, vector<int>(n, 0));

        // init
        vector<int> preSum = {0};
        for(auto s : stones) {
            preSum.push_back(preSum.back() + s);
            // cout << preSum.back() << "\n";
        }

        auto getSum = [&] (int st, int ed, vector<int>& stones) {
            return preSum[ed + 1] - preSum[st];
        };

        if(1 != n % (k-1) && k != 2) {
            return -1;
        }
        // 定义dp[i][j]为尽可能多的合并区间[i, j] 所需的成本，不一定能合并成一堆，但合并完成后剩下的堆数一定小于k，更具体地，剩余的堆数一定是(n - 1) % (k - 1) + 1。
        // 一定是从长度小的开始dp
        for(int len = k; len <= n; ++len) {
            for(int i = 0; i < n - len + 1; ++i) {
                int j = i + len - 1;
                dp[i][j] = INT_MAX;

                // cout << "--------- i/j: " << i << " " << j << endl;
                for(int m = i; m < j ; m += (k - 1)) {
                    // cout << "m : " << i << "->" << j - k + 1 << endl;
                    // cout << "before: relaxing: i/j: " << m << " ] " << dp[m + 1][j] << endl;
                    // dp[i][j] = min(dp[i][m] + getSum(m, m + k - 1, stones) + dp[m + k][j], dp[i][j]);
                    dp[i][j] = min(dp[i][m] + dp[m + 1][j], dp[i][j]);
                    // cout << "relaxing: i/j: " << i << " " << j << " : " << dp[i][m] << " " << dp[m+1][j] << endl;
                }

                // 上面求出来，怎么样找一个中间点，让所有的求和最小，但是没考虑最后的最后合并成一个的代价
                // i, j 必须为能够合并的区间
                if(1 == (j - i + 1) % (k - 1) || 2 == k) {
                    dp[i][j] += getSum(i, j, stones);
                }
            }
        }

        return dp[0][n-1];
    }
}
```