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
    class BIT {
    public: 
        vector<int> tree;
        int n;
        BIT(int _n): n(_n) , tree(_n + 1){cout << "init Done!" << endl;};

        // find prefixSum with index x
        int query(int x) {
            int sum = 0;
            while(x > 0) {
                sum += tree[x];
                x -= (x&(-x));
            }
            return sum;
        }

        // update x with delta val v
        void update(int x, int v) {
            cout << "d1"<< endl;
            while(x <= n) {
                tree[x] += v;
                x += (x&(-x));
            }
            cout << "d2"<< endl;
        }
    };

    int reversePairs(vector<int>& nums) {
        // desrialization, using sort no to denote the value
        vector<int> sortNoNums = nums;
        sort(sortNoNums.begin(), sortNoNums.end(), std::less<int>());
        
        for(auto& num : nums) {
            num = lower_bound(sortNoNums.begin(), sortNoNums.end(), num) - sortNoNums.begin() + 1;
        }

        // using binary indexed tree to statistic the reversePair num
        // start from the end of nums, so that the prefix in BIT means the reversePiar num
        int ans = 0;
        BIT bit(nums.size());
        for(int i = nums.size() - 1; i >= 0; --i) {
            ans += bit.query(nums[i] - 1); // cause only elements right than current num[i] will contribute to the ans
            cout << ans << endl;
            // statistic frequence of nums[i]
            bit.update(nums[i], 1);
        }

        return ans;
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