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
    static constexpr long long largePrime = 1000000007;
    
    vector<long long> factorial;
    
    vector<vector<int>> c;

    int numOfWays(vector<int>& nums) {
        long long ans = 0;
        int n = nums.size();
        factorial.resize(1000, 1);
        // for(long long i = 1; i < 1000; ++i) {
        //     factorial[i] = i * (factorial[i-1] % largePrime);
        //     // cout << i << "->" << factorial[i] << endl;
        //     factorial[i] %= largePrime;
        // }
        
        c.assign(n, vector<int>(n));
        c[0][0] = 1;
        // cal c(n, m) = c(n-1, m) + c(n-1, m-1);
        for(int i = 1; i < n; ++i) {
            c[i][0] = 1;
            for(int j = 1; j < n; ++j) {
                c[i][j] = (c[i-1][j] + c[i-1][j-1]) % largePrime;
            }
        }
        
        ans = findWays(nums);

        return ans - 1;
    }

    long long findWays(vector<int>& nums) {
        int n = nums.size();
        if(n <= 2) {
            return 1;
        }
        
        int root = nums[0];
        vector<int> left;
        vector<int> right;
        for(int i = 1; i < nums.size(); ++i) {
            if(nums[i] < root) {
                left.emplace_back(nums[i]);
            } else {
                right.emplace_back(nums[i]);
            }
        }
        
        // that means:
        // for the left tree, all nodes shall seat in the other places(and not change the relative order)
        // except root pos find the way out(the way shall equal: 
        //     pick nodes size seat from all seats, that is c(n, m-1);
        // ) and mutiply the two subTree arrange way num
        int seats = n - 1;
        int nodesToSeat = left.size();
        // cout << "c(n, k) " << seats << " -> " << nodesToSeat << " = " << c[seats][nodesToSeat] << endl;
        // cout << "l r : " << findWays(left) << "  " << findWays(right) << endl;
        // return ((findWays(left)  % largePrime )* (findWays(right) % largePrime)) * (getWaysForCurLevel(seats, nodesToSeat) % largePrime);
        return findWays(left)  % largePrime * findWays(right) % largePrime * c[seats][nodesToSeat] % largePrime;
    }

    long long getWaysForCurLevel(int seats, int nodesToSeat) {
        cout << "c(n, k)2 :" << factorial[seats] << " " << factorial[nodesToSeat] << " " << factorial[seats - nodesToSeat] << endl;; 
        return factorial[seats] / factorial[nodesToSeat] / factorial[seats - nodesToSeat];
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