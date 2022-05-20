## 0436findRightInterval 寻找右区间

### 1 题目
[https://leetcode.cn/problems/find-right-interval/](https://leetcode.cn/problems/minimum-moves-to-equal-array-elements-ii/)

### 2 解题思路
- 1 解题思路：
  - 1.1 容易想到，找一个东西记录区间到下标的映射，然后把区间排序，对于每个区间，在右边找到第一个st大于等于他的ed的区间即可
  - 1.2 具体我们注意到st是不重复的，于是使用map记录st和idx的区别，查找直接在map中利用默认的key的排序查找即可，也就是map.lower_bound()

```cpp
class Solution {
public:
    vector<int> findRightInterval(vector<vector<int>>& intervals) {
        // map<int, int> se;
        map<int, int> si;
        int i = 0;
        for(auto& vec : intervals) {
            // se[vec[0]] = vec[1];
            si[vec[0]] = i++;
        }

        vector<int> res;

        for(auto& v : intervals) {
            int ed = v[1];
            int st = v[0];
            
            auto pair = si.lower_bound(ed);
            if(pair == si.end()) {
                res.push_back(-1);
                continue;
            }
            res.push_back(pair->second);
        }

        return res;

    }
};
```