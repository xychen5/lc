## 1703 最小和为k的连续1的移动次数

### 1 题目
[https://leetcode-cn.com/problems/minimum-adjacent-swaps-for-k-consecutive-ones](https://leetcode-cn.com/problems/minimum-adjacent-swaps-for-k-consecutive-ones)

### 2 解题思路
首先：
- 1 了解到和为k的连续1的最小移动次数必然形成于有k个1的窗口中，则遍历所有的窗口即可;
- 2 必须认识到每个窗口最小移动次数形成时，中间的1不动才能带来最小的移动次数;

```cpp
class Solution {
public:
    int minMoves(vector<int>& nums, int k) {
        // main ref: https://leetcode-cn.com/problems/minimum-adjacent-swaps-for-k-consecutive-ones/solution/de-dao-lian-xu-k-ge-1-de-zui-shao-xiang-lpa9i/

        vector<int> g;
        vector<int> gPreSum;
        gPreSum.emplace_back(0);
        for(int i = 0; i < nums.size(); ++i) {
            if(1 == nums[i]) {
                g.emplace_back(i - g.size());
                gPreSum.emplace_back(gPreSum.back() + g.back());
            }
        }

        // moving window with len = k
        int minMov = INT_MAX;
        int st = 0;
        while(st <= g.size() - k) {
            int midIdxInG = (st + st + k - 1) / 2;
            int midIdxInNums = g[midIdxInG];
            int movCnt = (2*(midIdxInG - st) - k + 1) * midIdxInNums + gPreSum[st + k] - gPreSum[midIdxInG + 1] - (gPreSum[midIdxInG] - gPreSum[st]);
            minMov = std::min(movCnt, minMov);

            ++st;
        }
        return minMov;
    }
};
```