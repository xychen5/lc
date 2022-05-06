## 0689maxSumOfThreeSubarray 三个无重叠子数组的最大和

### 1 题目
[https://leetcode-cn.com/problems/maximum-sum-of-3-non-overlapping-subarrays/](https://leetcode-cn.com/problems/maximum-sum-of-3-non-overlapping-subarrays/)

### 2 解题思路
- 1 解题思路：dp 参考官方解答
  - 1.1 这里概括总结一下：dp[i][j] 表示对于nums[0:i-1]的子数组，不重叠个数为j个长度为k的子数组的最大值
  - 1.2 它的更新方程：dp[i][j] = max(dp[i - 1][j], dp[i - k][j - 1] + preSum[i] - preSum[i - k]);
  - 1.3 如和根据dp[n][3]找到下标？我们可以知道dp[n][3]肯定是由两个转移过来的，我们找他的前级就行，注意两个前级相同的时候我们取下标小的前级

```cpp
class Solution {
public:
    vector<int> maxSumOfThreeSubarrays(vector<int>& nums, int k) {
        vector<int> ans;

        vector<int> preSum = {0};

        for(auto a : nums) {
            preSum.push_back(a + preSum.back());
        }

        int n = nums.size();

        vector<vector<int>> dp(n+1, vector<int>(4));

        // dp[i][j] 表示对于nums[0:i-1]的子数组，不重叠个数为j个长度为k的子数组的最大值
        for(int i = k; i <= n; ++i) {
            for(int j = 1; j <= 3; ++j) {
                dp[i][j] = max(dp[i - 1][j], dp[i - k][j - 1] + preSum[i] - preSum[i - k]);
            }
        }

        // 考虑dp[n-1][3]的上一跳，找到最小对应的下标，记为i3，然后考虑dp[i3][2]的上一跳记为i2，考虑dp[i2][1]的上一跳记为i1
        // 最终答案就是{i1，i2，i3}
        int i = n;
        int j = 3;
        ans.resize(3, -1);

        int lastSum = dp[i][j];
        while(i >= 0) {
            if(dp[i][j] == lastSum) {
                --i;
                cout << i << " ";
            } else {
                // cout << "done! with lastSum = " << lastSum << endl;;
                ans[j-1] = i + 1 - k;
                i = i - k + 1; // 下一个数组的起始下标，注意，dp[i][j]是计算 的nums[0:i-1]的子数组，所以将上一个数组的下标作为找下一个数组下标的dp的开始
                --j;
                lastSum = dp[i][j];
                // cout << "nextSum is " << lastSum << " nextSt is " << i << endl;
            }
        }
        return ans;
    }
};
```