## 0041firstMissingPositive 缺失的第一个正数

### 1 题目
[https://leetcode.cn/problems/first-missing-positive/](https://leetcode.cn/problems/first-missing-positive/)

### 2 解题思路
- 1 解题思路:
  - 首先：设nums.size() == n
    - 则，答案必然在 [1, n+1]之中
    - 那么我们用一个长度为n的map：map[i] : bool类型 标记i+1是否出现
    - 然后找到第一个map中的false，下标就是答案
  - 但是要求我们o(1)
    - 那么首先：小于0的全部标记为n+2，在1到n之间的标记为0，找到第一个非0不就好啦？
      - 但是不行：你看：4 3 -1 1, 1本来也要贡献1处的位置为0，但是被4覆盖了，所以这个标记方式有点问题，那能否在保持其值的同时做上标记呢？
    - 将值变成负数即可，然后遍历到1改变为-1的时候，如果这个数字为负数，难么取绝对值去改变
  - 最后的结果就是，第一个不是负数的下标就是结果

```cpp
class Solution {
public:
    int firstMissingPositive(vector<int>& nums) {
        // ans must between: 1 and nums.size() + 1
        int n = nums.size();

        for(auto& num : nums) {
            if(num <= 0) {
                num = n + 2;
            }
        }

        for(int i = 0; i < n; ++i) {
            if(1 <= abs(nums[i]) && abs(nums[i]) <= n) {
                // for 4 3 -1 1, 
                //     4 3  6 -1
                //     4 3  -6 -1
                //     -4 3 -1 -1
                // to avoid 4 overwrite the 1, we use 1's negative to mark that we got 4 
                if(nums[abs(nums[i]) - 1] > 0) {
                    nums[abs(nums[i]) - 1] = -abs(nums[abs(nums[i]) - 1]);
                }
            }
        }

        // for(auto i : nums) {
        //     cout << i  << " " ;
        // }
        // cout << endl;

        // for i in 1 : n+1 : if map[i] == false? return
        int ans = 1;
        for(int i = 0; i < n; ++i) {
            if(nums[i] > 0) {
                return ans;
            }
            ++ans;
        }
        return ans;
    }
}
```