// ConsoleApplication1.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

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

using namespace std;
class Solution {
public:
    unordered_set<string> hash;

    vector<vector<int>> permute(vector<int>& nums) {
        vector<vector<int>> res;
        vector<int> tmp;
        chooseN(nums, nums.size(), res, tmp);
        return res;
    }

    void chooseN(vector<int>& nums, int n, vector<vector<int>>& res, vector<int>& tmp) {
        if(n == 0) {
            res.emplace_back(tmp);
        }

        for(int i = 0; i < nums.size(); ++i) {
            
            vector<int> tmpNums;
            tmpNums.insert(tmpNums.end(), nums.begin(), nums.begin() + i);
            tmpNums.insert(tmpNums.end(), nums.begin() + i + 1, nums.end());
            tmp.emplace_back(nums[i]);
            chooseN(tmpNums, n-1, res, tmp);
            tmp.pop_back();
        }
    }

};

int main()
{
    // vector<int> nums = {1, 15, 5, 11};
    // vector<int> nums = {1, 3};
    // vector<int> nums = {1, 3};
    int n = 2;
    vector<int> nums1d = { 1, 0 };
    vector<vector<int>> nums2d1 = { {1}, {0} };
    vector<vector<int>> nums2d4 = { {1,1,3,3},{3,1,4,2},{3,2,4,4},{1,3,2,4},{2,3,3,4} };
    Solution sl;
    // std::cout << sl.medianSlidingWindow(nums1d, 3) << std::endl;

    // std::cout << ios::left << std::setw(20) << "Hello, World!" << std::setw(5) << "a s " << 1 << std::endl;
    return 0;
    std::cout << "Hello World!\n";
}