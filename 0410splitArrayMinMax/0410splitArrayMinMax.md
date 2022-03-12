## 0410splitArrayMinMax 分割出最小的子数组最大值

### 1 题目
[https://leetcode-cn.com/problems/split-array-largest-sum/](https://leetcode-cn.com/problems/split-array-largest-sum/)

### 2 解题思路
参考官方解答：[https://leetcode-cn.com/problems/split-array-largest-sum/solution/fen-ge-shu-zu-de-zui-da-zhi-by-leetcode-solution/](https://leetcode-cn.com/problems/split-array-largest-sum/solution/fen-ge-shu-zu-de-zui-da-zhi-by-leetcode-solution/)
- 1 dp: 首先搞明白动态规划的单元，注意，不仅仅是说增加一个元素，对分割造成了什么影响，而且还要考虑，不通的分割数目，本题目是分割，那么一定是分割数目以及分割对象带来的变化为dp的状态迁移， dp[i][j] means: res of: nums[:i] to be splited in j's segments, dp[i][j] = max {dp[k][j-1], sum[k+1, i] | j <= k <= i - 1}，所以
- 2 二分查找法：这样，判断一个数字能否作为分割m个子数组的方案？应该很好判断，顺序遍历即可
  - 2.1 那么记录该数字为x，最小就是数组里的最大值，最大即为数组和，于是仅仅需要用二分法，从这个范围中找出该数字即可
  - 2.2 具体如何二分？若x过于小了，会导致分割数目太大，然后我们就知道往大处搜索，反之同理
- 3 二分法的标准写法：
  - 3.1 注意用>>代表除2，尤其是考虑负数时候有区别
  - 3.2 注意当往大地方搜，st = mid+1，往小地方则不用，不然可能导致ed漏搜索
```cpp
        bool lastCheck = false;
        while(st < ed) {
            x = (st + ed) >> 1; // means: floor of (st + ed)
            lastCheck = xIsLarge(x, nums, m);
            if(lastCheck) {
                ed = x; // when ed - st = 1, (st + ed) >> 1 == st
            } else {
                st = x + 1;
            }
        }
        return st;
 

```

```cpp
class Solution {
public:
    int splitArray(vector<int>& nums, int m) {
        int n = nums.size();
        vector<int> preSum = { 0 };
        for(int i = 0; i < n; ++i) {
            preSum.push_back(preSum.back() + nums[i]);
        }
        // // dp[i][j] means: res of: nums[:i] to be splited in j's segments
        // // dp[i][j] = max {dp[k][j-1], sum[k+1, i] | j <= k <= i - 1}
        // vector<vector<int>> dp(n+1, vector<int>(m+1, INT_MAX));
        
        // dp[1][1] = nums[0];
        // for(int i = 1; i <= n; ++i) {
        //     for(int j = 1; j <= min(m, i); ++j) {
        //         if(j == 1) {
        //             dp[i][1] = preSum[i] - preSum[0];
        //             continue;
        //         }
        //         int tmpMaxMin = 0;
        //         for(int k = j - 1; k < i; ++k) {
        //             tmpMaxMin = max(dp[k][j-1], preSum[i] - preSum[k]);
        //             dp[i][j] = min(dp[i][j], tmpMaxMin);
        //         }
        //     }
        // }
        // return dp[n][m];
        
        // binsearch x as the min max res
        int st = *max_element(nums.begin(), nums.end());
        int ed = preSum[n];
        int x = -1;


        bool lastCheck = false;
        while(st < ed) {
            x = (st + ed) >> 1;
            lastCheck = xIsLarge(x, nums, m);
            if(lastCheck) {
                ed = x; // when ed - st = 1, (st + ed) >> 1 == st
            } else {
                st = x + 1;
            }
        }
        
        // at last, st == ed
        return st;
    }

    bool xIsLarge(int x, vector<int>& nums, int m) {
        int cnt = 1;
        int curSum = 0;
        for(int i = 0; i < nums.size(); ++i) {
            if(curSum + nums[i] > x)  {
                ++cnt;
                curSum = nums[i];
            } else {
                curSum += nums[i];
            }
        }
        // cout << ">> x/cnt is" << x << "/" << cnt << endl;
        return cnt <= m;
    }
};
```
