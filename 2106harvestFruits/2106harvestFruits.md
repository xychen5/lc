## 2106harvestFruits k步最多摘水果

### 1 题目
[https://leetcode.cn/problems/maximum-fruits-harvested-after-at-most-k-steps/](https://leetcode.cn/problems/maximum-fruits-harvested-after-at-most-k-steps/)

### 2 解题思路
- 1 解题思路:
  - 1.0 最关键的是要发现：最优路径一定只回头一次
  - 1.1 使用前缀和，这是O(n)，然后对于stPos看所有的可能区间
    - 注意：可能先向左走和先向右走，注意这两者的区间范围是略有不同的

```cpp
class Solution {
public:
    int maxTotalFruits(vector<vector<int>>& fruits, int startPos, int k) {
        for(auto& v : fruits) {
            ++v[0];
        }
        ++startPos;

        int maxPos = fruits.back()[0];

        // the optimal path must have only one turn
        // prefixSum[pos]: means form 0 to pos: the fruits u get
        vector<int> prefixSum(maxPos + 1, 0); 
        prefixSum[fruits.front()[0]] = fruits.front()[1];

        for(int i = 1; i < fruits.size(); ++i) {
            int pos = fruits[i][0];
            int amount = fruits[i][1];
            int acc = amount + prefixSum[fruits[i-1][0]];
            prefixSum[pos] = acc;
            for(int cur = fruits[i-1][0] + 1; cur < min(pos, maxPos); ++cur) {
                prefixSum[cur] = prefixSum[fruits[i-1][0]] ;
            }
        }

        int res = INT_MIN;
        // mv left first
        for(int mvLeft = k; mvLeft >= 0; --mvLeft) {
            int st = startPos;
            int ed = -1;
            ed = startPos + mvLeft;
            if(ed > maxPos) {
                continue;
            }
            st = max(1, min(st, ed - (k - mvLeft)));
            if(st > ed) {
                continue;
            }
            res = max(res, prefixSum[ed] - prefixSum[st-1]);
        }


        // mv right first
        for(int mvRight = k; mvRight >= 0; --mvRight) {
            int st = startPos - mvRight;
            if(st < 1) {
                continue;
            }
            int ed = min(maxPos, max(startPos, st + (k - mvRight)));
            if(ed < st) {
                continue;
            }
            res = max(res, prefixSum[ed] - prefixSum[st-1]);
        }

        return res == INT_MIN ? 0 : res;

    }
};
```