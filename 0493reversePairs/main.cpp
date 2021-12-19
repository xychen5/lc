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

    class BITree {
    public:
        long long n;
        vector<long long> tree;
        BITree(long long _n) : n(_n), tree(_n + 1) {}
        
        long long lowBit(long long x) {
            return x & (-x);
        }

        long long query(long long x) {
            long long sum = 0;
            while(x > 0) {
                sum += tree[x];
                x -= lowBit(x);
            }
            return sum;
        }

        void update(long long x, long long val) {
            while(x <= n) {
                tree[x] += val;
                x += lowBit(x);
            }
        }
    };

    int reversePairs(vector<int>& nums) {
        // deserialization
        vector<long long> tmpNums;
        for(auto num : nums) {
            tmpNums.emplace_back(num);
            tmpNums.emplace_back(num * 2LL);
        }
        sort(tmpNums.begin(), tmpNums.end(), [](long a, long b) {
            return a < b;
        });

        // for(auto& num : tmpNums) { cout << "tmp: " << num << endl;}
        
        // for(auto& num : nums) {
        //     num = lower_bound(tmpNums.begin(), tmpNums.end(), num) - tmpNums.begin() + 1; //  +1 to avoid update(0, 1) failure
        // }

        for(auto& num : nums) { cout << "num No: " << num << endl;}

        // deserialization
        int idx = 1;
        unordered_map<long long,long long> numToIdx;
        for(auto num : tmpNums) {
            numToIdx[num] = idx ++;
        }

        int n = nums.size();
        int ans = 0;
        BITree tree(2 * n);
        // for each j, find those nums[i]:
        // which satisty: i < j && nums[i] > 2*nums[j]
        // 
        // so, we can get this by: using all to sub those nums[i] <= nums[j] * 2 to get the res
        // preSum[1 -> 2*n] - preSum[1 -> 2*nums[j]]
        for(int i = 0; i < n; ++i) {
            // cout << "counting: " << nums[i] << endl;
            // attention the diff between 2LL and 2
            ans += (tree.query( 2LL*n ) - tree.query(numToIdx[2LL * nums[i]]));
            tree.update(numToIdx[nums[i]], 1);
        }

        return ans;
    }
}

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