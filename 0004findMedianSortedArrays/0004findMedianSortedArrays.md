## 0004findMedianSortedArrays 寻找两个正序数组的中位数

### 1 题目
[https://leetcode.cn/problems/median-of-two-sorted-arrays/](https://leetcode.cn/problems/median-of-two-sorted-arrays/)

### 2 解题思路
- 1 解题思路：
  - 1.1 将直接二分找目标数的思路转换一下，找两个数组中第k大的数字
  - 1.2 那么通过比较 A[k/2 - 1]和B[k/2 - 1]这两个数字，我们能发现，在这两个数字左侧（不包含这两个数字）最多有k - 2个，这样最答案一定不在前面的AB段里面，可以去掉A的或者B的[:k/2 - 1]这个部分的数字，然后更新k(k代表着我们还要去掉多少个数字)，同时更新stA和stB标记AB的起点
  - 1.3 退出的过程：当 1 = k的时候，意味着从AB当前的起点，仅需要找一个数字即可，那么自然是两个的最小值
  - 1.4 考虑，肯定会出现A或者B的下标溢出情况，那么由于我们知道还有多少个数字要数，那么直接在另一个不溢出的数组里返回结果即可！

```cpp
class Solution {
public:
    int getKthElement(vector<int>& nums1, vector<int>& nums2, int k) {
        // cout <<"------------" << endl;
        int idx1 = k / 2 - 1;
        int m = nums1.size();
        int n = nums2.size();
        int st1 = 0;
        int st2 = 0;

        while(true) {
            // 当k消耗殆尽，则直接返回结果
            // cout << "m/n" << m << " " << n << endl;
            if(st1 == m) {
                // cout <<"aa" << endl;
                return nums2[st2 + k - 1];
            }
            if(st2 == n) {
                return nums1[st1 + k - 1];
            }
            if(k == 1) {
                // cout << st1 << " | " << st2 << endl;
                return min(nums1[st1], nums2[st2]);
            }

            int nextSt1 = min(st1 + k / 2 - 1, m - 1);
            int nextSt2 = min(st2 + k / 2 - 1, n - 1);
            if(nums1[nextSt1] > nums2[nextSt2]) {
                k = k - (nextSt2 + 1 - st2); // 排除了这么些个数字
                st2 = nextSt2 + 1;
                // cout << "st2: " << st2 << endl;
            } else {
                k = k - (nextSt1 + 1 - st1);
                st1 = nextSt1 + 1;
                // cout << "st1: " << st1 << endl;
            }
        }

        return -1;
    }


    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        int len = nums1.size() + nums2.size();
        if(len % 2 == 1) {
            return getKthElement(nums1, nums2, len / 2 + 1);
        }
        return static_cast<double>(getKthElement(nums1, nums2, len / 2 + 1) + getKthElement(nums1, nums2, len / 2)) / 2;

    }
};
```