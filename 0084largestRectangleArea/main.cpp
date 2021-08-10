#include <iostream>
#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <limits.h>
#include <numeric>
class Solution {
public:
    int largestRectangleArea(vector<int>& heights) {
        int res = 0;
        heights.emplace_back(0); // for the monotonous stack to pop of all the elements

        vector<int> monoStack;
        for(int i = 0; i < heights.size(); ++i) {
            while(monoStack.size() > 0 && heights[monoStack.back()] >= heights[i]) {
                int h = heights[monoStack.back()];
                monoStack.pop_back();
                int smallIdx = monoStack.size() > 0 ? monoStack.back() : -1;
                int width = i - smallIdx - 1;
                res = std::max(res, width * h);
            }
            monoStack.emplace_back(i);
        }

        return res;

    }
};

int main() {
    // vector<int> nums = {1, 15, 5, 11};
    // vector<int> nums = {1, 3};
    // vector<int> nums = {1, 3};
    vector<int> nums = {1, 2, 2, 3};
    Solution sl;
    std::cout << sl.largestRectangleArea(nums) << std::endl;
    std::cout << "Hello, World!" << std::endl;
    return 0;
}
