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
    vector<double> medianSlidingWindow(vector<int>& nums, int k) {
        long long n = nums.size();
        std::multiset<long long, std::less<long long>> mySet(nums.begin(), nums.begin() + k);

        vector<double> res;
        multiset<long long>::iterator mid = mySet.begin();
        std::advance(mid, (k-1)/2);

        for(long long i = k; i <= n; ++i) {
            res.emplace_back((*mid + *next(mid, 1 - k%2))*1.0L/2);
            if(i == n) break;

            mySet.insert(nums[i]);
            if (nums[i] > *mid && nums[i - k] < *mid) {
                mid++;
                mySet.erase(mySet.lower_bound(nums[i-k]));
                continue;
                // std::advance(mid, 1);
            }

            if (nums[i] < *mid && nums[i - k] > *mid) {
                mid--;
                mySet.erase(mySet.lower_bound(nums[i-k]));
                continue;
                // std::advance(mid, -1);
            }
            // 7 3 7 7 4, k = 4
            // 7 8 7 7 4, k = 4
            if(nums[i-k] == *mid) {
                if(nums[i] >= *mid)  ++mid;
                else {
                    if(*prev(mid) != *mid) {
                        --mid;
                    }
                }
                mySet.erase(mySet.lower_bound(nums[i-k]));
                continue;
            } 

            if(nums[i] == *mid) {// 相当于一个比mid大的数字插入到了mid的前面
                if(nums[i-k] <= *mid)  ++mid;
                mySet.erase(mySet.lower_bound(nums[i-k]));
                continue;
            }
        }
        return res;
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