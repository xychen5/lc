## 0668findKthNumber 乘法表中第k小的数

### 1 题目
[https://leetcode.cn/problems/kth-smallest-number-in-multiplication-table/](https://leetcode.cn/problems/kth-smallest-number-in-multiplication-table/)

### 2 解题思路
- 1 解题思路：
  - 1.1 找乘法表中的第k个数字，应该考虑在1到m*n中，找一个最小的数字mid，小于等于mid的数字，刚好有k个
  - 1.2 为何能够保证，比如对于3*3的乘法表展开：（12233 4669），找的是第7个或者第8个数字，那么二分搜索的过程如下：
  - 1.3 从过程中可以发现，当目前的mid满足了大于等于k个的时候，每次ed = mid，下一个mid就会减小，比如从st/ed的6,9变成6,7,最后搜索到6，也就是，找一个最小的数字，乘法表中有k个小于等于他，最后一定会搜索到它，我们可以反证法：
  - 1.4 假设从1到m*n，找到一个数字有k个小于等于他，记作x，他出现在这个乘法表中，假设它不是最小的，那么也就是说存在一个数字y，y < x出现在乘法表中，且有k个数字小于等于他，很显然是错的，因为这样x，就至少是有k+1个数字小于等于他，和前提相反！
  - 
st/ed/cnt: 1/9/6 | 5
st/ed/cnt: 6/9/8 | 7
st/ed/cnt: 6/7/8 | 6

```cpp
class Solution {
public:
    int findKthNumber(int m, int n, int k) {
        // 对于每一个数字x，他在乘法表中是多大的？
        // 那么求解方案就变成了：
        // 找到最小的数字，这个数字有k个小于等于他
        int st = 1, ed = m*n, mid;
        while(st != ed) {
            // 小于等于mid的个数为cnt
            mid = (st + ed) >> 1;
            int cnt = 0;
            for(int line = 1; line <= m; ++line) {
                cnt += min(mid / line, n);
            }
            
            cout << "st/ed/cnt: " << st << "/" << ed << "/" << cnt << " | " << mid  << endl;
            if(cnt >= k) {
                ed = mid;
            } else {
                st = mid + 1;
            }
        }
        return st;

    }
};
```