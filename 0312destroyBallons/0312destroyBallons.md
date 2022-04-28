## 0312destroyBallons 戳气球获得最大硬币

### 1 题目
[https://leetcode-cn.com/problems/dungeon-game/](https://leetcode-cn.com/problems/dungeon-game/)

### 2 解题思路
- 1 解题思路：dp 参考官方解答
  - 1.1 dp[i][j]表示，不包含i,j，对于i,j的开区间添加气球能够获得的最大硬币数目：
    - dp[i][j] = for k = i+1 -> j-1: max{ val[i]*val[k]*val[j] + dp[i][k] + dp[k][j] }
  - 1.2 从上面的动态规划的式子，我们可以知道，对于i,j这个区间它需要所有i，k和k,j的子数据，所以，区间长度应该从小到大，那么我们首先定义j的移动方向，从小到大，然后i从大到小（从小区间开始遍历的约束导致i需要从大到小），最后k从小到大即可 
```cpp
class Solution {
public:
    int maxCoins(vector<int>& nums) {
        int n = nums.size();
        vector<vector<int>> dp(n+2, vector<int>(n+2, 0));
        vector<int> val(n+2);
        val[0] = val[n+1] = 1;
        for(int i = 0; i < n; ++i) {
            val[i+1] = nums[i];
        }

        for(int j = 2; j <= n + 1; ++j) {
            for(int i = j - 2; i >= 0; --i) {
                for(int k = i+1; k <= j-1; ++k) {
                    int sum = val[i] * val[k] * val[j];
                    sum += dp[i][k] + dp[k][j];
                    dp[i][j] = max(dp[i][j], sum);
                }
            }
        }
        
        return dp[0][n+1];
    }
};
```