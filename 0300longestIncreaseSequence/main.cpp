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
    int lengthOfLIS(vector<int>& nums) {
        // official way 2:
        if(1 == nums.size()) {
            return 1;
        }
        vector<int> minBitLIS = {nums[0]};
        
        int len = 1;
        int n = nums.size();
        for(int i = 1; i < n; ++i) {
            if(minBitLIS.back() < nums[i]) {
                minBitLIS.push_back(nums[i]);
                ++len;
            } else {
                // bin search the first num bigger than nums[i] in minBitLIS
                // to update the min bit of LIS
                updateMinBit(minBitLIS, nums[i]);
            }
        }
         
        return len;
        
    }

    void updateMinBit(vector<int>& minBitVec, int num) {
        int n = minBitVec.size();
        int st = 0, ed = n-1;
        int mid = -1;
        while(st <= ed) {
            mid = (st + ed) / 2;
            if(minBitVec[mid] > num) {
                ed = mid - 1;
            } else if(minBitVec[mid] < num) {
                st = mid + 1;
            } else {
                break;
            }
        }
        if(minBitVec[mid] > num) {
            minBitVec[mid] = num;
        } else if(minBitVec[mid] < num){
            minBitVec[min(mid + 1, n-1)] = num;
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
    // Solution sl;
    // std::cout << sl.medianSlidingWindow(nums1d, 3) << std::endl;

    // std::cout << ios::left << std::setw(20) << "Hello, World!" << std::setw(5) << "a s " << 1 << std::endl;
    return 0;
    std::cout << "Hello World!\n";
}