// ConsoleApplication1.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <limits.h>
#include <numeric>
#include <list>
#include <queue>
#include <unordered_set>
#include <unordered_map>
#include <map>
#include <set>
#include <string>

using namespace std;

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

int main()
{
    // vector<int> nums = {1, 15, 5, 11};
    // vector<int> nums = {1, 3};
    // vector<int> nums = {1, 3};
    int n = 2;
    vector<int> nums1d = { 1, 0 };
    vector<vector<int>> nums2d1 = { {1}, {0} };
    vector<vector<int>> nums2d4 = { {1,1,3,3},{3,1,4,2},{3,2,4,4},{1,3,2,4},{2,3,3,4} };
    // Solution sl;
    // std::cout << sl.medianSlidingWindow(nums1d, 3) << std::endl;

    // std::cout << ios::left << std::setw(20) << "Hello, World!" << std::setw(5) << "a s " << 1 << std::endl;
    return 0;
    std::cout << "Hello World!\n";
}