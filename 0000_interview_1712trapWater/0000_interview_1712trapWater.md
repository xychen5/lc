## 0000_interview_1712trapWater 接雨水

### 1 题目：
[https://leetcode-cn.com/problems/volume-of-histogram-lcci/](https://leetcode-cn.com/problems/volume-of-histogram-lcci/)

### 2 解题思路：
- 1 参照提示的一句话：
> 每个长方形的顶部都有水，水的高度应与左侧最高长方形和右侧最高长方形的较小值相匹配，也就是说，water_on_top[i] = min(tallest_ bar(0->i), tallest_bar(i, n))。
- 2 使用单调栈计算当前节点左侧(右侧)最大值
  - 2.1 很简单： 考虑单调栈的性质，单调递减栈的第一个字符为**目前**最大的元素，单调递增栈则相反，为最小元素
  - 2.2 关于目前的解释，由于单调栈是遍历整个数组出栈入栈的过程，遍历到节点i，则arr[:i]为目前单调栈遍历过的元素们，单调栈递增递减栈的第一个数字分别为arr[:i]的最大最小值
  - 2.3 由于需要统计右侧最大值，则我们只需要逆序遍历数组即可，最大值可以使用单调递减获得

```cpp
class Solution {
public:
    int trap(vector<int>& height) {
        // using descending mono stack to find maxValue in left or right
        vector<int> normalOrderMono;
        vector<int> reverseOrderMono;
        int n = height.size();
        vector<int> leftMax(n);
        vector<int> rightMax(n);
        for(int i = n - 1; i >= 0; --i){
            while(!reverseOrderMono.empty() && height[reverseOrderMono.back()] <= height[i]) {
                reverseOrderMono.pop_back();
            }
            rightMax[i] = reverseOrderMono.empty() ? height[i] : height[reverseOrderMono[0]];
            reverseOrderMono.emplace_back(i);
        }
        
        for(int i = 0; i < n; ++i){
            while(!normalOrderMono.empty() && height[normalOrderMono.back()] <= height[i]) {
                normalOrderMono.pop_back();
            }
            leftMax[i] = normalOrderMono.empty() ? height[i] : height[normalOrderMono[0]];
            normalOrderMono.emplace_back(i);
        }
        
        int res = 0;
        for(int i = 0; i < n; i++) {
            res += max(min(leftMax[i], rightMax[i]) - height[i], 0);
        }

        return res;
    }
};
```