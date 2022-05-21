## 01402cookOrder 做菜顺序

### 1 题目
[https://leetcode.cn/problems/reducing-dishes/](https://leetcode.cn/problems/reducing-dishes/)

### 2 解题思路
- 1 解题思路：
  - 1.1 dp[i]表示做前i道菜能够取得的最大收益
  - 1.2 那么在dp[i]能够正式使用之前，我们需要先对数组排序：从大到小降序
    - [-1,-8,0,5,-7] -> [5,0,-1,-7,-8]
    - 那么dp[0] = 5
    - dp[1] = max(5, 5 + 5 + 0 == 5*2 + 1*0)
    - dp[2] = max(dp[1], dp[1] + 5 + 0 + (-1))
  - 所以我们还能够发现，其实只要上面max的右边的dp[i] + preSum中的preSum > 0,我们就能够一直累加结果

```cpp
class Solution {
public:
    int maxSatisfaction(vector<int>& satisfaction) {
        // dp[i] 做前i道菜能够取得的最大喜欢时间
        sort(satisfaction.begin(), satisfaction.end(), std::greater<int>());
        if(satisfaction.front() <= 0) {
            return 0;
        }
        int n = satisfaction.size();
        vector<int> dp(n, 0);
        dp[0] = satisfaction.front();
        int preSum = satisfaction.front();
        for(int i = 1; i < n; ++i) {
            preSum += satisfaction[i];
            dp[i] = max(dp[i-1], dp[i-1] + preSum);
        }

        return dp[n-1];
    }
};
```