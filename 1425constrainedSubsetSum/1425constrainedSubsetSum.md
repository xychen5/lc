## 1425constrainedSubsetSum 带限制最大子序列和

### 1 题目
[https://leetcode.cn/problems/constrained-subsequence-sum/](https://leetcode.cn/problems/constrained-subsequence-sum/)

### 2 解题思路
- 1 解题思路:
  - 1.1 dp[i]表示以第i个数据结尾的带限制最大子序列和
  - 1.2 dp[i] = nums[i] + max(0, dp[i-k], dp[i-k+1], ..., dp[i-1])
  - 1.3 如何在i-1到i-k的数的集合中快速找到最大的满足限制要求的k？使用堆即可，只需要找到第一个满足要求的下标对应的值即可，不满足要求的下标可以pop掉（因为如果现在都无法满足要求，那么后面更加无法满足要求）

```cpp
class Solution {
public:
    using pii = pair<int, int>;
   

    int constrainedSubsetSum(vector<int>& nums, int k) {
        // Let dp[i] be the solution for the prefix of the array that ends at index i,
        //     if the element at index i is in the subsequence.
        // dp[i] = nums[i] + max(0, dp[i-k], dp[i-k+1], ..., dp[i-1])

        int n = nums.size();
        vector<int> dp(n, 0);
        dp[0] = nums[0];
        int curRes = dp[0];
        
        // <idx, value>
        auto cmp = [](const pii& a, const pii& b) {
            return a.second < b.second;
        };
        priority_queue<pii, vector<pii>, decltype(cmp)> maxHeap(cmp);
         
        maxHeap.push({0, dp[0]});

        auto findInWindow = [](int minIdx, decltype(maxHeap)& window) {
            bool foundInWin = false;
            while(!window.empty()) {
                auto node = window.top();
                if(minIdx <= node.first) {
                    // window.pop();
                    return max(0, node.second);
                } else {
                    window.pop();
                }
            }
            return 0;
        };

        for(int i = 1; i < n; ++i) {
            dp[i] = nums[i] + findInWindow(max(0, i - k), maxHeap);
            curRes = max(curRes, dp[i]);
            // cout << i << "->    " << dp[i] << endl;
            maxHeap.push({i, dp[i]});
        }
        return curRes;
    }
}
```