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
using namespace std;
class Solution {
public:
    int maxSideLength(vector<vector<int>>& mat, int threshold) {
        // mat.row >= m > i >= 0, mat.col >= n > j >= 0
        // preSum[m][n] -> preSum[i][j] = preSum[m][n] - preSum[m][j] - preSum[i][n] + preSum[i][j];
        int m = mat.size();
        int n = mat[0].size();
        vector<vector<int>> preSum(m+1, vector<int>(n+1, 0));
        for(int i = 1; i < m+1; ++i) {
            for(int j = 1; j < n+1; ++j) {
                preSum[i][j] = preSum[i-1][j] + preSum[i][j-1] - preSum[i-1][j-1] + mat[i-1][j-1];
            }
        }

        // traverse all square
        int maxSquareLen = std::min(m, n);
    //    for(int len = maxSquareLen; len >= 1; --len) { // len could be binary search
    //         for(int i = 0; i <= m - len; ++i) {
    //             for(int j = 0; j <= n - len; ++j) {
    //                 if(getRec(preSum, i+1, j+1, i + len, j + len) <= threshold) {
    //                     return len;
    //                 };
    //             }
    //         }
    //    }
        int stLen = 1;
        int edLen = maxSquareLen;
        int ans = 0;
        while(stLen <= edLen) {
            int len = (stLen + edLen) / 2;
            bool found = false;
            for(int i = 0; i <= m - len; ++i) {
                for(int j = 0; j <= n - len; ++j) {
                    if(getRec(preSum, i+1, j+1, i + len, j + len) <= threshold) {
                        found = true;
                    };
                }
            }
          
            if(found) { // len too small
                stLen = len+1;
                ans = len;
            } else { // len too big
                edLen = len-1;
            }
          
        }

        return ans;
    }

    int getRec(vector<vector<int>>& preSum, int i, int j, int m, int n) {
        return preSum[m][n] - preSum[m][j-1] - preSum[i-1][n] + preSum[i-1][j-1];
    }
};
int main() {
    // vector<int> nums = {1, 15, 5, 11};
    // vector<int> nums = {1, 3};
    // vector<int> nums = {1, 3};
    int n = 2;
    vector<int> nums1d = {1, 3};
    vector<vector<int>> nums2d1 = {{1}, {0}};
    vector<vector<int>> nums2d2 = {
        {1,0}
    };
    Solution sl;

    // std::cout << ios::left << std::setw(20) << "Hello, World!" << std::setw(5) << "a s " << 1 << std::endl;
    return 0;
}
