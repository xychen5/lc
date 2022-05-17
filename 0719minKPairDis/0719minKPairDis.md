## 0719minKPairDis 第k小的数对距离

### 1 题目
[https://leetcode.cn/problems/find-k-th-smallest-pair-distance/](https://leetcode.cn/problems/find-k-th-smallest-pair-distance/)

### 2 解题思路
- 1 解题思路：
  - 1.2 用二分去找第k小的数对距离，初始化
    - int ed = nums.back() - nums.front();
    - int st = 0;
  - 1.3 对于每次二分猜测的距离guess，使用双指针去判断有多少个数对比他小：
    - 方法：对于每一个right，移动left向右，直到nums[r] - nums[l] > guess，那么这个l，r能够贡献的比guess小的数对个数为：r - l
- 2 疑问？为何二分出来的结果，就一定存在于数中的某个数对距离呢？
  - 2.1 考虑这么一个问题：算出来的mid，必然保证，有k个数对的距离 <= mid
  - 那么，你会考虑，假设数据为1,3,7,14，然后数对距离的数组为 2 4 6 7 11，那么为什么 k = 2二分出来的一定是4，而不是5？5也能保证啊，因为如果是5，会继续二分，到4，因为二分中的cnt >= k，保证了最终二分结果一定是最小的能够满足cnt >= k的情况，那么为什么最小的能够保证cnt>=k的数会在所有数对的距离里面？因为假设不在数对距离里，那么要满足cnt>=k,那么二分结果是5，那么二分结果为5，它就不是最小的能够满足cnt>=k，这和二分的过程相悖,所以反证法证明了最小的cnt>=k的那个距离一定在数对距离数组里面

```cpp
class Solution {
public:
    int smallestDistancePair(vector<int>& nums, int k) {
        sort(nums.begin(), nums.end());

        int ed = nums.back() - nums.front();
        int st = 0;
        while(st < ed) {
            // cur gussed ans
            int tmpAns = (ed + st) >> 1;
            // cout << tmpAns << endl;

            // pair dis <= tmpAns's cnt
            int cnt = 0;

            // cal cnt
            int l = 0, r;
            for(r = 1; r < nums.size(); ++r) {
                // for each r, find first l where nums[r] - nums[l] < tmpAns
                while(nums[r] - nums[l] > tmpAns) {
                    ++l;
                }
                // then: nums[r] - nums[l] >= tmpAns
                cnt += r - l;
            }

            // cout << " <= tmpAns's cnt is  " << cnt << endl;

            
            // bin search
            if(cnt >= k) {
                ed = tmpAns;
            } else {
                st = tmpAns + 1;
            }
        }
        
        return st;
    }
};
```