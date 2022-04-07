## 0135candy 分发糖果

### 1 题目
[https://leetcode-cn.com/problems/candy/](https://leetcode-cn.com/problems/candy/)

### 2 解题思路
- 1 将规则拆分成为左规则和右规则，因为要求糖果最少但是需要同时满足左右规则，于是选择左规则和有规则下最大的那个就行
  - 1.1 注意的点：左规则时：rate[i] > rate[i-1]， 那么遍历rate[i]的时候需要rate[0：i-1]的值（因为这一部分子序列会影响rate[i]的值），于是我们需要从左到右遍历，同理对于右规则，rate[i] > rate[i + 1]，我们需要rate[i]右侧的所有值，于是从有到左遍历

```cpp
class Solution {
public:
    int candy(vector<int>& ratings) {
        // statisfy the right and left rule
        int n = ratings.size();
        vector<int> candy1(n, 1);
        vector<int> candy2(n, 1);
        for(int i = n - 1; i >= 0; --i) {
            if(i < n-1 && ratings[i] > ratings[i + 1]) {
                candy1[i] = candy1[i + 1] + 1;
            }
        }
        
        for(int i = 0; i < n; ++i) {
            if(i > 0 && ratings[i] > ratings[i - 1]) {
                candy2[i] = candy2[i - 1] + 1;
            }
        }

        int res = 0;
        for(int i = 0; i < candy2.size(); ++i) {
            res += max(candy2[i], candy1[i]);
        }
        return res;
    }
};

```