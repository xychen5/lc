#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <limits.h>
#include <numeric>
class Solution {
public:
    int maximalRectangle(vector<vector<char>>& matrix) {
        if(matrix.size() == 0 || matrix[0].size() == 0) {
            return 0;
        }
        vector<vector<int>> left(matrix.size(), vector<int>(matrix[0].size(), 0));

        // caculate how many continuable 1 is at the left of [r][c] position
        for(size_t r = 0; r < matrix.size(); ++r) {
            int leftTmp = 0;
            for(size_t c = 0; c < matrix[0].size(); ++c) {
                if(matrix[r][c] == '1') {
                    ++leftTmp;
                    left[r][c]= leftTmp;
                } else {
                    leftTmp = 0;
                }
            }
        }

        // // caculate the max square
        // int ans = 0;
        // for(int c = 0; c < matrix[0].size(); ++c) {
        //     for(int r = 0; r < matrix.size(); ++r) {
        //         int tmpArea = 0;
        //         int minWidth = INT_MAX;
        //         for (int tmpR = r; tmpR >= 0; --tmpR) {
        //             minWidth = min(minWidth, left[tmpR][c]);
        //             tmpArea = std::max(tmpArea, minWidth * (r - tmpR + 1));
        //             ans = std::max(ans, tmpArea);
        //         }
        //     }
        // }

        // caculate the max square, optimized version using monotonous stack
        int ans = 0;
        for(int c = 0; c < matrix[0].size(); ++c) {
            vector<int> monoStack;
            for(int r = 0; r < matrix.size(); ++r) {
                while(monoStack.size() > 0 && left[monoStack.back()][c] >= left[r][c]) {
                    int curHeight = left[monoStack.back()][c];
                    monoStack.pop_back(); 
                    // then, the left[monoStack.back()] will not take part in this calculation
                    int smallIdx = monoStack.size() > 0 ? monoStack.back() : -1;
                    int width = r - smallIdx -1;
                    ans = max(ans, width * curHeight);
                }
                monoStack.emplace_back(r);
                // int tmpArea = 0;
                // int minWidth = INT_MAX;
                // for (int tmpR = r; tmpR >= 0; --tmpR) {
                //     minWidth = min(minWidth, left[tmpR][c]);
                //     tmpArea = std::max(tmpArea, minWidth * (r - tmpR + 1));
                //     ans = std::max(ans, tmpArea);
                // }
            }
            int maxWidth = matrix.size();
            // the left monoStack must be a increasing stack, so calculate then done!
            while(monoStack.size() > 0) {
                int curHeight = left[monoStack.back()][c];
                monoStack.pop_back();
                int width = monoStack.size() == 0 ? maxWidth : maxWidth - monoStack.back() - 1;
                ans = max(ans, width * curHeight);
            }
        }       
        return ans;
    }
};

int main() {    
    
    vector<vector<int>> nums = {
        {0, 1, 1, 0}, 
        {0, 0, 0, 0}
    };
    Solution sl;
    std::cout << sl.maximalRectangle(nums) << std::endl;
    std::cout << "Hello, World!" << std::endl;
    return 0;
}
