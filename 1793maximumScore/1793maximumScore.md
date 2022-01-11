## 1793 好子数组的最大分数 maximumScore

### 1 题目：
[https://leetcode-cn.com/problems/maximum-score-of-a-good-subarray/](https://leetcode-cn.com/problems/maximum-score-of-a-good-subarray/)

类似题目： 
- 1 [https://leetcode-cn.com/problems/maximal-rectangle/submissions/](https://leetcode-cn.com/problems/maximal-rectangle/submissions/)
- 2 [https://leetcode-cn.com/problems/largest-rectangle-in-histogram/](https://leetcode-cn.com/problems/largest-rectangle-in-histogram/)

### 2 解题思路：
- 1 单调栈：
  - 1.1 想法很简单，遍历上述的柱状图的一列，栈顶总是最大，栈底最小，一旦有小于等于前栈的值，那么栈里面那些小于等于当前栈顶的值都不可能再在遍历的后续位置发生作用了，因为已经有小于等于它的值出现了，所以我们把这些值弹出然后算弹出的这一部分的体积，那么栈里面剩下的就是任然能够为后续遍历的位置贡献面积的值，所以就是这样，具体的看代码吧。
  - 1.2 计算过程中，我们只有当矩形的两边分别位于k的两边才会更新结果
- 2 强调单调栈的几个特性(以递增单调栈为例子)
  - 2.1 栈底一定是整个数组最小的
  - 2.2 弹出当前元素记其下标为j后，当前栈顶元素下标记为i，那么i是第一个下标满足： i < j && arr[i] <= arr[j]
  - 2.3 **TIPS: **注意单调栈会将所有元素都入栈，但并不会都出栈，很多时候我们要求arr中的每个元素都出栈，那么常见操作为在arr末尾加一个比所有元素都要小的值即可

```cpp
class Solution {
public:
    int maximumScore(vector<int>& nums, int k) {
        // k split nums into left and right
        vector<int> lPart(nums.begin(), nums.begin() + k + 1);
        
        // construct the monostack, abscending
        vector<int> mono;

        int res = nums[k];
        nums.emplace_back(0); // make sure all the heights are used for nums
        for(int r = 0; r < nums.size(); ++r) {
            while(!mono.empty() && nums[mono.back()] >= nums[r]) {
                int h = nums[mono.back()];
                // cout << "h: " << h << endl;
                mono.pop_back();
                int l = mono.empty() ? -1 : mono.back();
                int w = r - l - 1;
                cout << "w/r/l/h: " << w << "/" << r << "/" << l << "/" << h << endl;
                if(r - 1 >= k && l + 1 <= k) {
                    res = max(res, w * h);
                }
            }
            mono.emplace_back(r);
        }

        return res;
    }
}
```

