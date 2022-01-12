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
    int trap(vector<int>& height) {
        // using descending mono stack to find maxValue in left or right
        vector<int> normalOrderMono;
        vector<int> reverseOrderMono;
        int n = height.size();
        vector<int> leftMax(n);
        vector<int> rightMax(n);
        for(int i = n - 1; i >= 0; --i){
            while(!reverseOrderMono.empty() && height[reverseOrderMono.back()] <= height[i]) {
                reverseOrderMono.pop_back();
            }
            rightMax[i] = reverseOrderMono.empty() ? height[i] : height[reverseOrderMono[0]];
            reverseOrderMono.emplace_back(i);
        }
        
        for(int i = 0; i < n; ++i){
            while(!normalOrderMono.empty() && height[normalOrderMono.back()] <= height[i]) {
                normalOrderMono.pop_back();
            }
            leftMax[i] = normalOrderMono.empty() ? height[i] : height[normalOrderMono[0]];
            normalOrderMono.emplace_back(i);
        }
        
        int res = 0;
        for(int i = 0; i < n; i++) {
            res += max(min(leftMax[i], rightMax[i]) - height[i], 0);
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
    // std::cout << sl.largestRectangleArea(nums) << std::endl;
    std::cout << "Hello, World!" << std::endl;
    return 0;
}
