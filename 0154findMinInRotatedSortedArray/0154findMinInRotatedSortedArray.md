## 0154findMinInRotatedSortedArray 旋转后的排序数组找最小值

### 1 题目
[https://leetcode.cn/problems/find-minimum-in-rotated-sorted-array-ii/](https://leetcode.cn/problems/find-minimum-in-rotated-sorted-array-ii/)

### 2 解题思路
- 1 解题思路:
  - 首先：一定要注意到：考虑旋转a1 + a2 + ... + an = sum次，其实最终还是等于旋转了sum % nums.size()次，也就是说，数组的形状一定是 上升，从起点上升这么两段
  - 那么就二分法即可：
  - 若：nums[mid] < nums[ed]：则说明答案在左边侧，
  - nums[mid] > nums[ed]，在右半侧
  - nums[mid] = nums[ed]，则答案，一定不在ed的右侧，所以--ed，也就是说mid可能是答案呢

```cpp
class Solution {
public:
    int findMin(vector<int>& nums) {
        int n = nums.size();
        int st = 0, ed = n - 1;
        int pivot;
        while(st < ed) {
            pivot = (st + ed) >> 1;
            if(nums[pivot] < nums[ed]) {
                ed = pivot;
            } else if(nums[pivot] > nums[ed]) {
                st = pivot+1;
            } else {
                ed -= 1;
            }
        }

        return nums[st];

    }
}
```