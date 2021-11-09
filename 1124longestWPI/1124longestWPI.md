## 1124 良好表现的最长时间段

### 1 题目
[https://leetcode-cn.com/problems/longest-well-performing-interval/](https://leetcode-cn.com/problems/longest-well-performing-interval/)

### 2 解题思路
较为容易想到前缀和思路：
不好想的地方在于第1和3条，思路如下：
- 1 对于这种良好费良好的判断，我们需要把数组转换成 -1, 1的数组
- 2 对上述数组作前缀和
- 3 那么对于每个到来的j，只需要找到最小的i，满足 preSum[j] - preSum[i] == 1即可
  - 3.1 如何理解最小的i，也就是说，对于同一个preSum值的下标，我们总是去最小的i即可
  - 3.2 对于 9 9 9 9 9这种全正常的思路，如何判断？ 前缀和的值本身就可以判断，大于零的下标都可以是良好工作区间

```cpp
class Solution {
public:
    int longestWPI(vector<int>& hours) {
        vector<int> preSum = {0};
        for(int i = 0; i < hours.size(); ++i) {
            preSum.emplace_back((hours[i] > 8 ? 1 : -1) + preSum.back());
        }
          
        int st = 0;
        int ed = 0;
        int res = INT_MIN;
        // key: presum's value, value: presum's index
        map<int, int> m;
        m[0] = 0;
        int lastPop = 0;
        vector<int> mono = {0};
        for(; ed < hours.size(); ++ed) {
            if (preSum[ed + 1] > 0) {
                res = std::max(res, ed + 1);
                continue;
            }
            map<int, int>::iterator it = m.find(preSum[ed + 1] - 1);
            if(it != m.end()) {
                res = std::max(ed - it->second, res);
            } 
            if (m.find(preSum[ed + 1]) == m.end()) {
                m[preSum[ed + 1]] = ed; 
            }
            
        }
        return res < 0 ? 0 : res;

    }
};
```
