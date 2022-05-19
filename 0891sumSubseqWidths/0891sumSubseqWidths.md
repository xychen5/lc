## 0891sumSubseqWidths 子序列宽度和

### 1 题目
[https://leetcode.cn/problems/sum-of-subsequence-widths/](https://leetcode.cn/problems/sum-of-subsequence-widths/)

### 2 解题思路
- 1 解题思路：首先排个序
  - 1.1 考虑以A[i]和以A[j]作为最大值和最小值的序列个数有多少个？很显然： 2 ^(j - i - 1)， 遍历所有i,j的pair然后求和即可，但是记得化简这个式子

```cpp
class Solution {
public:
    constexpr static int mod = 1000000007;
    int sumSubseqWidths(vector<int>& nums) {
        // consider max as A[j], min as A[i]
        // cosider how many subarrays who has A[i]A[j]

        sort(nums.begin(), nums.end(), std::less<int>());

        // cal pow2
        int n = nums.size();
        vector<long long > pow2(n, 1);
        for(int i = 1; i < n; ++i) {
            pow2[i] = 2 * pow2[i - 1] % mod;
        }

        // count res
        long long res = 0;
        for(int i = 0; i < n; ++i) {
            res += static_cast<long long>(nums[i]) * (pow2[i] - pow2[n - i - 1]) % mod;
            res %= mod;
        }

        return res;
    }
};
```