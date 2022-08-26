## 1301maxScorePathCount 最大得分的路径数目

### 1 题目
[https://leetcode.cn/problems/number-of-paths-with-max-score/](https://leetcode.cn/problems/number-of-paths-with-max-score/)

### 2 解题思路
- 1 解题思路
  - dp[i][j] 存一个pair，<max leng, way count>
  - 那么dp[i][j]分成3中情况，一种：只能从下方来，一种，只能从右方来，一种：三个方向都行
  - 关于三个方向都行的时候，我们要的方法总数是，那三个方向中的路径最大值对应的方法数，如果三个里面有最大路径值相同的，则累加他们的方法数
  - 那么第三种情况的处理
    - 1 求出最大方法数，如果为负数（我们初始化方法数为INT_MIN，如果最大方法数位负数，则说明不能达到）
    - 2 对于所有和最大长度相同的方向，累加他们的方法数
- 2 斜着遍历的技巧：
  - for sum 0 -> m + n - 3
    - for j : 0 -> m - 1
      - i = sum - j, 检测ij合法性，不合法跳过即可

```cpp
class Solution {
public:
    static constexpr int bigInt = 1'000'000'007;
    vector<int> pathsWithMaxScore(vector<string>& board) {
        int n = board.size();
        int m = board[0].size();
        // cout << n << "-" << m << endl;
        
        // dp
        using pii = pair<long, long>;
        vector<vector<pii>> dp(m, vector<pii>(n, {0, INT_MIN}));

        // <path length, ways>
        dp[n-1][m-1] = {0, 1};
        
        // len: dp[i][j] = max(dp[i-1][j] + board[i][j], dp[i][j-1] + board[i][j], dp[i-1][j-1] + board[i][j]);
        // way: dp[i][j] = 
        
        
        for(int sum = m + n - 3; sum >= 0; --sum) {
            for(int j = m - 1; j >= 0; --j) {
                int i = sum - j;
                if(!(0 <= i && i < n && 0 <= j && j < m)) {
                    continue;
                }
                
                // cout << "doing: sum: i/j: " << sum << " : " << i << "/" << j ;
                if('X' == board[i][j]) {
                    // cout << "cotinue\n";
                    continue;
                }

                // suppose from r
                dp[i][j].second = 0;
                if(i == n - 1) {
                    // 只能从右侧来
                    dp[i][j].first = dp[i][j + 1].first + board[i][j] - '0';
                    dp[i][j].second = dp[i][j + 1].second;
                    dp[i][j].second %= bigInt;
                    // cout << " [r] ";
                } else if( j == m - 1) {
                    // 只能从下侧来
                    dp[i][j].first = dp[i + 1][j].first + board[i][j] - '0';
                    dp[i][j].second = dp[i + 1][j].second;
                    dp[i][j].second %= bigInt;
                    // cout << " [d] ";
                } else {
                    // cout << " [rdl] ";
                    // 可以从三面来，优先考虑最大的路径值
                    int maxPath = max(max(dp[i+1][j].first, dp[i][j+1].first), dp[i+1][j+1].first);
                    if(maxPath < 0) {
                        continue;
                    }

                    if(0 == i && 0 == j) {
                        dp[i][j].first = maxPath;
                    } else {
                        dp[i][j].first = maxPath + board[i][j] - '0';
                    }

                    dp[i][j].second = 0;
                    if(maxPath == dp[i+1][j].first && dp[i+1][j].second >= 0) {
                        dp[i][j].second += dp[i+1][j].second;
                        dp[i][j].second %= bigInt;
                    }
                    if(maxPath == dp[i][j+1].first && dp[i][j+1].second >= 0) {
                        dp[i][j].second += dp[i][j+1].second;
                        dp[i][j].second %= bigInt;
                    }
                    if(maxPath == dp[i+1][j+1].first && dp[i+1][j+1].second >= 0) {
                        dp[i][j].second += dp[i+1][j+1].second;
                        dp[i][j].second %= bigInt;
                    }

                }
                // cout << " : " << dp[i][j].first << " ways: " << dp[i][j].second << endl;
            }
        }

        vector<int> res(2, 0);
        if(dp[0][0].second <= 0 ) {
            return res;
        }

        res[0] = dp[0][0].first;
        res[1] = dp[0][0].second;
        // cout <<"has res!\n";
        return res;
    }
}
```