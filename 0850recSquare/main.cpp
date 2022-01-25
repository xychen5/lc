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
    vector<int> fallingSquares(vector<vector<int>>& positions) {
        // coordinate compression
        set<int, std::less<int>> coords;
        for(vector<int>& coord : positions) {
            coords.insert(coord[0]);
            coords.insert(coord[0] + coord[1] - 1);
        }

        unordered_map<int, int> borderToIdx;
        int t = 0;
        for(auto& i : coords) {
            borderToIdx[i] = t++;
        }

        // cal heights
        vector<int> heights(t);
        vector<int> res;
        int curHeightest = INT_MIN;
        for(vector<int>& square : positions) {
            int l = borderToIdx[square[0]];
            int r = borderToIdx[square[0] + square[1] - 1];
            int h = square[1];
            int updatedHeight = update(l, r, h, heights);
            curHeightest = max(curHeightest, updatedHeight);
            res.emplace_back(curHeightest);
        }
        return res;
    }

    // update and return updated height of [l, r]
    int update(int l, int r, int h, vector<int>& heights) {
        int oldHeight = INT_MIN;
        for(int i = l; i <= r; ++i) {
            oldHeight = max(oldHeight, heights[i]);
        }
        int newHeight = INT_MIN;
        for(int i = l; i <= r; ++i) {
            heights[i] = oldHeight + h;
        }
        return oldHeight + h;
    } 
};



int main() {
    // vector<int> nums = {1, 15, 5, 11};
    // vector<int> nums = {1, 3};
    // vector<int> nums = {1, 3};
    vector<int> nums = {1, 2, 2, 3};
    Solution sl;
    // std::cout << sl.largestRectangleArea(nums) << std::endl;
    std::cout << "Hello, World!" << std::endl;
    return 0;
}
