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
    int minKBitFlips(vector<int>& nums, int k) {
        vector<long long> preSum = {0};
        for(long long num : nums) {
            preSum.emplace_back(preSum.back() + num);
        }

        long long st = 0;
        long long ed = st + k - 1;
        long long n = nums.size();
        long long res = 0;

        vector<long long> diff(n+1);
        long long flipCnt = 0;
        // while(st < n - k + 1) {
            // 模拟思路会超时
            // if(nums[st] == 1) {
            //     ++st;
            //     continue;
            // }
            // int newSt = flipKBit(nums, k, st, preSum);
            // if(newSt == -1) {
            //     st = st + k;
            // } else {
            //     st = newSt;
            //     res += 1;
            // }
        // }
        // if(find(nums.end() - k, nums.end(), 0) == (nums.end())) {
        //     return res;
        // } 

        while(st < n) {
            // 采用查分数组记录每个元素应该翻转的次数
            // 这启发我们用差分数组的思想来计算当前数字需要翻转的次数。我们可以维护一个差分数组 \textit{diff}diff，其中 \textit{diff}[i]diff[i] 表示两个相邻元素 
            // \textit{nums}[i-1]nums[i−1] 和 \textit{nums}[i]nums[i] 的翻转次数的差，对于区间 [l,r][l,r]，将其元素全部加 11，只会影响到 ll 和 r+1r+1 处的差分值，
            // 故 \textit{diff}[l]diff[l] 增加 11，\textit{diff}[r+1]diff[r+1] 减少 11。
            flipCnt += diff[st];
            if((flipCnt + nums[st]) % 2 == 0) {
                if(st + k > n) {
                    return -1;
                }
                diff[st] ++;
                diff[st + k] --;
                res++;
                flipCnt ++;
            }
            ++st;
        }
        return res;
    }

    // 翻转kbit，返回第一个翻转窗口中反转后值不等于1的下标，否则返回-1
    int flipKBit(vector<int>& nums, int k, int st, vector<int>& preSum) {
        int firstNot1 = INT_MAX;
        // 需要O(k)时间的复杂度
        bool needFlip = find(nums.begin() + st, nums.begin() + st + k, 0) != (nums.begin() + st + k);
        // 使用前缀和优化，由于实地翻转了数组，于是会改变对应的前缀和，所以此方法行不通
        // bool needFlip = ((preSum[st + k] - preSum[st]) != k);

        // for(int i = st; i < k; ++i) {
        //     if(nums[st + i] != 1) {
        //         needFlip = true;
        //     }
        // }
        if(needFlip) {
            for(int i = 0; i < k; ++i) {
                nums[st + i] = abs(nums[st + i] - 1);
                if(nums[st + i] != 1) {
                    firstNot1 = min(firstNot1, st + i);
                }
            }
            return firstNot1 > nums.size() ? st + k : firstNot1 ;
        }
        

        return -1;
    }
};

int main() {
    // vector<int> nums = {1, 15, 5, 11};
    // vector<int> nums = {1, 3};
    // vector<int> nums = {1, 3};
    int n = 2;
    vector<int> nums1d = {1, 0};
    vector<vector<int>> nums2d1 = {{1}, {0}};
    vector<vector<int>> nums2d2 = {
        {1,0}
    };
    Solution sl;
    std::cout << sl.minKBitFlips(nums1d, 2) << std::endl;

    // std::cout << ios::left << std::setw(20) << "Hello, World!" << std::setw(5) << "a s " << 1 << std::endl;
    return 0;
}
