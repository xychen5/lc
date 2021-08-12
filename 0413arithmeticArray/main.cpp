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
    int numberOfArithmeticSlices(vector<int>& nums) {
        if(nums.size() <= 2) {
            return 0;
        }
        // sort
        // sort(nums.begin(), nums.end(), [](int a, int b){return a < b;});

        // get all arithemetic slices length and sum it
        int curItv = 0;
        bool interupted = true;
        int curLen = 0;
        int res = 0;
        for(int i = 1; i < nums.size(); ++i) {
            if(interupted) {
                curItv = nums[i] - nums[i-1];
                curLen = 2;
                interupted = false;
                continue;
            }
            if(nums[i] - nums[i-1] == curItv) {
                curLen++;
            } else {
                --i;
                res += subSlicesNum(curLen);
                interupted = true;
            }
        }
        res += subSlicesNum(curLen);
        return res;
    }

    int subSlicesNum(int n) {
        if(n <= 2) {
            return 0;
        }
        return ((n-2) * (n-1))/2;
    }
};

int main() {
    // vector<int> nums = {1, 15, 5, 11};
    // vector<int> nums = {1, 3};
    // vector<int> nums = {1, 3};
    vector<int> nums = {1, 2, 2, 3};
    Solution sl;
    std::cout << sl.numberOfArithmeticSlices(nums) << std::endl;

    // std::cout << ios::left << std::setw(20) << "Hello, World!" << std::setw(5) << "a s " << 1 << std::endl;
    return 0;
}
