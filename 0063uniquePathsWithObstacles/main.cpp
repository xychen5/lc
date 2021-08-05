#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <limits.h>
#include <numeric>

using namespace std;


class Solution {
public:
    int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {
        // m rows n colums's board
        size_t m = obstacleGrid.size(), n = obstacleGrid[0].size();
        
        vector<vector<int>> res = vector<vector<int>>(m, vector<int>(n, 0));
        
        for(int p = 0; p < m; ++p) {
            if(obstacleGrid[p][0] == 1) {
                break;
            } else {
                res[p][0] = 1;
            }
        }
        
        for(int q = 0; q < n; ++q) {
            if(obstacleGrid[0][q] == 1) {
                break;
            } else {
                res[0][q] = 1;
            }
        }
        
        for(int p = 1; p < m; ++p) {
            for(int q = 1; q < n; ++q) {
                if(obstacleGrid[p][q] == 1){
                    res[p][q] = 0;
                    continue;
                }
                res[p][q] = 
                    (obstacleGrid[p-1][q] == 0 ? res[p-1][q] : 0) +
                    (obstacleGrid[p][q-1] == 0 ? res[p][q-1] : 0);
            }
        }
        
        return res[m-1][n-1];
        
    }
};

int main() {
    // vector<int> nums = {1, 15, 5, 11};
    // vector<int> nums = {1, 3};
    // vector<int> nums = {1, 3};
    // vector<int> nums = {1, 2, 5, 7};
    vector<vector<int>> nums = {
        {0, 1, 1, 0}, 
        {0, 0, 0, 0}
    };
    Solution sl;
    std::cout << sl.uniquePathsWithObstacles(nums) << std::endl;
    
    // std::cout << ios::left << std::setw(20) << "Hello, World!" << std::setw(5) << "a s " << 1 << std::endl;
    return 0;
}