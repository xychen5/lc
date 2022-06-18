## 1755minAbsDiff 最接近目标值的子序列和

### 1 题目
[https://leetcode.cn/problems/closest-subsequence-sum/](https://leetcode.cn/problems/closest-subsequence-sum/)

### 2 解题思路
- 1 解题思路：
  - 1.1 注意求的是子序列，那么我们可以用状态压缩码中的每个bit表示当前数字是否存在，从而求得所有子序列的和
  - 1.2 为了快，我们将数组一分为2，左边和右边求所有子序列的和记作ls，rs，然后都升序排列
  - 1.3 结果就是，在ls[i] + rs[j]中找最接近goal的数字，那不就是杨氏矩阵吗，从左到右从上到下都递增的杨氏矩阵，搜所一个数字的最快方案是O(m + n)，而不是mlog(n)
  - 1.4 看一个例子：l = 1 1 4 4, r = 2 5 6 9, 其中xi表示的是第i步剪裁掉的解空间
```cpp
        /** 
        search target: 7, start form l = 4, r = 2
        l :  1  1  4  4 
        r: 2 x1 x1 x1 6
           5 x4 6  8  9
           6    7  x3 x2
           9       x3 x2
        */
```

```cpp
class Solution {
public:
    vector<int> makeSubSeqSum(vector<int> nums) {
        int n = nums.size();
        vector<int> ans(1 << n);
        for(int bits = (1 << n) - 1; bits >= 0; --bits) {
            int curState = bits;
            while(curState != 0) {
                int pos = ffs(curState) - 1;
                ans[bits] += nums[pos];
                curState -= (1 << pos);
            }
        }
        return ans;
    }

    //  vector<int> makeSubSeqSum(vector<int> nums){
    //     vector<int> ans(1 << nums.size());
    //     for(int i = 0; i < nums.size(); ++i){
    //         for(int j = 0; j < (1 << i); ++j){
    //             ans[j + (1 << i)] = ans[j] + nums[i];
    //         }
    //     }
    //     return ans;
    // }



    void binSearchAdjTwoAndUpdate(int tar, int r, int goal, vector<int>& leftSet, int& minAbs) {
        auto it1 = lower_bound(leftSet.begin(), leftSet.end(), tar);   
        if(it1 == leftSet.end()) {
            int l = *(it1 - 1);
            minAbs = min(abs(l + r - goal), minAbs);
        } else if(it1 == leftSet.begin()) {
            int l = *(it1);
            minAbs = min(abs(l + r - goal), minAbs);
        } else {
            int l1 = *it1;
            int l2 = *(it1 - 1);
            minAbs = min(abs(l1 + r - goal), minAbs);
            minAbs = min(abs(l2 + r - goal), minAbs);
        }
    }

    // 注意题目说的是子序列，而不是子数组
    // 考虑复杂度：如果枚举所有子序列，2^40，那么将数组分成两半去枚举：2^20 * 2
    int minAbsDifference(vector<int>& nums, int goal) {
        int n = nums.size();
        int mid = n >> 1;
        auto leftSet = makeSubSeqSum(vector<int>{nums.begin(), nums.begin() + mid});
        auto rightSet = makeSubSeqSum(vector<int>{nums.begin() + mid, nums.end()});

        if(n == 1) {
            return min(abs(nums[0] - goal), abs(goal));
        }
        
        sort(leftSet.begin(), leftSet.end());
        sort(rightSet.begin(), rightSet.end());

        int minAbs = INT_MAX;
        // // 对于每一个r部分，使用二分找到最近的两个l， nlogn
        // for(auto r : rightSet) {
        //     // |r + l| == |goal| => l = |goal| - r or l = - |goal| - r
        //     int tar1 = abs(goal) - r;
        //     int tar2 = - abs(goal) - r;
        //     binSearchAdjTwoAndUpdate(tar1, r, goal, leftSet, minAbs);
        //     binSearchAdjTwoAndUpdate(tar2, r, goal, leftSet, minAbs);
        // }

        // 直接使用双指针，比二分快, o(n)
        int ptr1 = leftSet.size() - 1; // 杨氏矩阵的i行 // left升序
        int ptr2 = 0; // 央视矩阵的j列 // right升序
        // 则 ptr2为r的最大，ptr1为l的最小
        /** 
        search target: 7, start form l = 4, r = 2
        l :  1  1  4  4 
        r: 2 x1 x1 x1 6
           5 x4 6  8  9
           6    7  x3 x2
           9       x3 x2
        */
        while(ptr1 >= 0 && ptr2 < rightSet.size()) {
            // cout << leftSet[ptr1] << " " << rightSet[ptr2] << endl;
            int curRes = leftSet[ptr1] + rightSet[ptr2];
            minAbs = min(minAbs, abs(curRes - goal));
            if(curRes < goal) {
                // 因为所有的 leftSet[ptr1] + rSet[: ptr2-1]都不可能是答案，于是增加ptr1
                ++ptr2;
            } else if(curRes > goal) {
                // leftSet[ptr2: ] + leftSet[ptr1] 不可能是答案
                --ptr1;
            } else {
                return 0;
            }
        }

        return min(minAbs, abs(goal));
    }
};
```