## 0992 k个不同元素的子数组个数

### 1 题目
[https://leetcode-cn.com/problems/subarrays-with-k-different-integers/submissions/](https://leetcode-cn.com/problems/subarrays-with-k-different-integers/submissions/)

### 2 解题思路
- 1 正常思路：
  - 1.1 首先窗口是必须的，即为[st, ed]，那么保证这个窗口时刻含有k个不同变量，然后求出来每个以ed为结尾的子数组的个数求和即可
  - 1.2 那么以ed为结尾的窗口[st, ed]的子数组个数求法，假设k=2，窗口为1,2，1,2,那么以ed为结尾，st就向前移动，直到窗口内的不同元素个数减少到了k-1，此时st移动到第二个2的位置，一共移动了3次，也就是说以ed为结尾的含有k个不同变量的子数组个数为3。
  - 1.3 其中的复杂之地在于：如何判断窗口内不同元素的个数，我们采用经典的空间换时间的方法(因为所有元素的值不会大于数组本身长度),用freq[val]记录val出现的次数， 倘若长度不限呢？那就需要使用unordered_map来记录当前窗口所有元素的出现次数，然后每移动一次st需要遍历一遍这个map来判断当前窗口内不同元素的个数，那么整体复杂度为： o(n * k * k)
- 2 官方题解：
  - 2.1 不同元素为k的子数组的个数为： 不同元素最多为k的子数组个数 - 不同元素最多为k-1的子数组个数，那么问题转为求不同元素最多为k的一个数组它子数组的个数
  - 2.2 求法： 还是滑动窗口的思想，始终保持窗口中最多元素的个数不超过k（方式为每次移动ed，直到第一次超过k，然后移动st直到小于k），然后对于每个ed，ed - st就是以ed为窗口结尾对应的不同元素不超过k的子数组的个数，举个例子：(官方例子)：
> 用具体的例子理解：最多包含 3 种不同整数的子区间 [1, 3, 2, 3] （双指针算法是在左边界固定的前提下，让右边界走到最右边），当前可以确定 1 开始的满足最多包含 3 种不同整数的子区间有 [1]、[1, 3]、[1, 3, 2]、[1, 3, 2, 3]。

```cpp
class Solution {
public:
    int subarraysWithKDistinct(vector<int>& nums, int k) {
        return maxSubArrayNumForKDiff(nums, k) - maxSubArrayNumForKDiff(nums, k - 1);

    }

    int maxSubArrayNumForKDiff(vector<int>& nums, int k) {
        vector<int> freq(nums.size() + 1);
        long long res = 0;
        int st = 0;
        int ed = 0;
        int curCnt = 0;
        while(ed < nums.size()) {
            // 求每个ed对应得到的最多k个不同元素的子数组个数
            if(freq[nums[ed]] == 0) {
                curCnt ++;
            }
            freq[nums[ed]]++;
            ++ed;

            // 减小窗口到窗口内元素种类第一次为k-1个
            while(curCnt > k) {
                freq[nums[st]]--;
                if(freq[nums[st]] == 0) {
                    curCnt--;
                }
                ++st;
            }
            res += ed - st;
        }
        return res;
    }
};
```
