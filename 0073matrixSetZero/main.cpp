#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <limits.h>
#include <numeric>

using namespace std;

class Solution {
public:
    void setZeroes(vector<vector<int>>& matrix) {
        bool columFlag = false;
        bool rowFlag = false;
        for(size_t i = 0; i < matrix[0].size(); ++i) {
            if(matrix[0][i] == 0) {
                columFlag = true;
            }
        }
        for(size_t j = 0; j < matrix.size(); ++j) {
            if(matrix[j][0] == 0) {
                rowFlag = true;
            }
        }

        // row: form j = 1 -> m
        // colum: form i = 1 -> n
        for(size_t i = 1; i < matrix[0].size(); ++i) {
            for(size_t j = 1; j < matrix.size(); ++j) {
                if(matrix[j][i] == 0) {
                    matrix[0][i] = 0;
                    matrix[j][0] = 0;
                }
            }
        }

        // change the row and the colum
        for(size_t i = 1; i < matrix[0].size(); ++i) {
            if(matrix[0][i] == 0) {
                for (size_t k = 1; k < matrix.size(); ++k) {
                    matrix[k][i] = 0;
                }
            }
        }
        for(size_t j = 1; j < matrix.size(); ++j) {
            if(matrix[j][0] == 0) {
                for (size_t k = 1; k < matrix[0].size(); ++k) {
                    matrix[j][k] = 0;
                }
            }
        }

        
        if(columFlag) {
            for (size_t k = 0; k < matrix[0].size(); ++k) {
                matrix[0][k] = 0;
            }
        }
        if(rowFlag) {
            for (size_t k = 0; k < matrix.size(); ++k) {
                matrix[k][0] = 0;
            }
        }

    }
};

int main() {
    // vector<int> nums = {1, 15, 5, 11};
    // vector<int> nums = {1, 3};
    // vector<int> nums = {1, 3};
    // vector<int> nums = {1, 2, 5, 7};
    vector<int> nums = {2, 2, 3, 4};
    Solution sl;
    vector<vector<int>> nums2d1 = {
        {0, 1, 1, 0}, 
        {0, 0, 0, 0}
    };

    // std::cout << sl.setZeroes(nums2d1) << std::endl;
    
    // std::cout << ios::left << std::setw(20) << "Hello, World!" << std::setw(5) << "a s " << 1 << std::endl;
    return 0;
}
