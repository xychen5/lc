#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <limits.h>
#include <numeric>

using namespace std;

class Solution {
public:
    int uniquePaths(int m, int n) {
        std::vector<std::vector<int>> board(m, std::vector<int>(n, 0));
        
        for(size_t i = 0; i < m; ++i) {
            board[i][0] = 1;
        }
        for(size_t j = 0; j < n; ++j) {
            board[0][j] = 1;
        }

        for(size_t i = 1; i < m; ++i) {
            for(size_t j = 1; j < n; ++j) {
                board[i][j] = board[i][j-1] + board[i-1][j];
            }
        }
        
        return board[m-1][n-1];
    }
};


int main() {
    // vector<int> nums = {1, 15, 5, 11};
    // vector<int> nums = {1, 3};
    // vector<int> nums = {1, 3};
    // vector<int> nums = {1, 2, 5, 7};
    vector<int> nums = {2, 2, 3, 4};
    Solution sl;
    std::cout << sl.uniquePaths(2, 5) << std::endl;
    
    // std::cout << ios::left << std::setw(20) << "Hello, World!" << std::setw(5) << "a s " << 1 << std::endl;
    return 0;
}
