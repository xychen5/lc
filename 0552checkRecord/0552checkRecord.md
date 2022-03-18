## 0552checkRecord 学生出勤记录

### 1 题目
[https://leetcode-cn.com/problems/student-attendance-record-ii/](https://leetcode-cn.com/problems/student-attendance-record-ii/)

### 2 解题思路
- 1 初步思路 dp[i][j]作为直到i天，以j为出勤记录的所有记录数，但是会发现无法处理连续的L的情况
- 2 更改，采用官方题解思路： dp[i][j]为以连续j个l为结尾的记录数，首先只考虑PL，但是此方法不行，因为，A可以隔断两个L，所以，如果先算出所有PL的方法，然后将A插入，那么结果一定会比用A去隔断两个L少。
- 3 官方接单： dp[i][j][k]是含有j个A的k个L为结尾的记录数


```cpp
class Solution {
public:

    int bigInt = 1000000007;
    int checkRecord(int n) {
        if(n <= 2) {
            return n == 1 ? 3 : 8;
        }
        
        // we can use A to interrupt the LLL, so we calculate A after only PL
        // // n's day without 'A'
        // vector<vector<long long>> dp(n + 1, vector<long long>(3, 0));
        
        // // dp[i][j], j means end with n's L
        // dp[1][0] = 1; dp[1][1] = 1; dp[1][2] = 0;


        // for(int i = 2; i <= n; ++i) {
        //     // end with p
        //     dp[i][0] = dp[i - 1][0] + dp[i - 1][1] + dp[i - 1][2];
            
        //     // ent with l
        //     dp[i][1] = (dp[i - 1][0]) % bigInt;

        //     // end with ll
        //     dp[i][2] = dp[i - 1][1] % bigInt;
        //     cout << i << " th: P/L: " << dp[i][1] << " " << dp[i][0] << endl;
        // }

        // // when there is a A:
        // long long res = 0;
        // res += ((dp[n][0] + dp[n][1]) % bigInt + dp[n][2]) % bigInt;
        // res += (((dp[n-1][0] + dp[n-1][1]) % bigInt + dp[n-1][2]) % bigInt * n) % bigInt;
       

        // n's day without 'A'
        vector<vector<vector<long long>>> dp(n + 1, vector<vector<long long>>(2, vector<long long>(3, 0)));
        
        // dp[i][j], j means end with n's L
        dp[0][0][0] = 1;

        for(int i = 1; i <= n; ++i) {
            // end with p
            for(int j = 0; j < 2; ++j) {
                for(int k = 0; k <= 2; ++k) {
                    dp[i][j][0] = (dp[i][j][0] + dp[i - 1][j][k]) % bigInt;
                }
            }

            // end with a
            for(int k = 0; k <= 2; ++k) {
                dp[i][1][0] = (dp[i][1][0] + dp[i-1][0][k]) % bigInt;
            }
            
            // ent with l
            for(int j = 0; j < 2; ++j) {
                for(int k = 1; k <= 2; ++k) {
                    dp[i][j][k] = (dp[i][j][k] + dp[i - 1][j][k-1]) % bigInt;
                }
            }
        }

        int res = 0;

        for(int j = 0; j < 2; ++j) {
            for(int k = 0; k < 3; ++k) {
                res = (res + dp[n][j][k]) % bigInt;
            }
        }


        return res;
    }
};
```