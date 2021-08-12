#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <limits.h>
#include <numeric>

using namespace std;

class Solution {
public:
    int maxProfit(vector<int>& prices) {
        if(prices.size() <= 1) {
            return 0;
        }

        int b1 = -prices[0], s1 = 0, b2 = INT_MIN, s2 = 0;

        for(size_t dayIdx = 1; dayIdx < prices.size(); ++dayIdx) {
            b1 = max(b1, - prices[dayIdx]);
            s1 = max(s1, b1 + prices[dayIdx]);
            b2 = max(b2, s1 - prices[dayIdx]);
            s2 = max(s2, b2 + prices[dayIdx]);
        }
        return s2;
    }
};
int main() {
    // vector<int> nums = {1, 15, 5, 11};
    // vector<int> nums = {1, 3};
    // vector<int> nums = {1, 3};
    vector<int> nums = {1, 2, 2, 3};
    Solution sl;
    std::cout << sl.maxProfit(nums) << std::endl;

    // std::cout << ios::left << std::setw(20) << "Hello, World!" << std::setw(5) << "a s " << 1 << std::endl;
    return 0;
}
