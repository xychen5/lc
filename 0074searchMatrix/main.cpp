#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <limits.h>
#include <numeric>

class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        // find suitable raw
        int tarRawIdx = 0;
        int stIdx = 0, edIdx = matrix.size()-1;
        while(1) {
            int curIdx = (stIdx + edIdx) / 2;
            if(matrix[curIdx][0] > target) {
                edIdx = curIdx;
            } else if (matrix[curIdx][0] < target) {
                stIdx = curIdx;
            } else {
                return true;
            }
            if(edIdx - stIdx == 1 && curIdx == stIdx) {
                if(matrix[edIdx][0] == target) {
                    return true;
                } else {
                    tarRawIdx = (matrix[edIdx][0] < target) ? edIdx : stIdx;
                    break;
                }
            } else if (edIdx == stIdx) {
                if(matrix[edIdx][0] == target) {
                    return true;
                } else {
                    tarRawIdx = stIdx;
                    break;
                }
            }
        }

        int res = binSearch(matrix[tarRawIdx], target);
        return res < 0 ? false : true;

    }

    int binSearch(vector<int>& vec, int tar) const {
        int stIdx = 0, edIdx = vec.size()-1;
        while(1) {
            int curIdx = (stIdx + edIdx) / 2;
            if(vec[curIdx] > tar) {
                edIdx = curIdx;
            } else if (vec[curIdx] < tar) {
                stIdx = curIdx;
            } else {
                return curIdx;
            }
            if((edIdx - stIdx == 1 && curIdx == stIdx)
                || edIdx == stIdx) {
                if(vec[edIdx] == tar) {
                    return edIdx;
                } else {
                    return -1; // not find
                }
            }
        }
    }
};

using namespace std;
int main() {    
    
    vector<vector<int>> nums = {
        {0, 1, 1, 0}, 
        {0, 0, 0, 0}
    };
    Solution sl;
    std::cout << sl.searchMatrix(nums) << std::endl;
    std::cout << "Hello, World!" << std::endl;
    return 0;
}
