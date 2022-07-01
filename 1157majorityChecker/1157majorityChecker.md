## 1157majorityChecker 子数组中占绝大多数的元素

### 1 题目
[https://leetcode.cn/problems/online-majority-element-in-subarray/](https://leetcode.cn/problems/online-majority-element-in-subarray/)

### 2 解题思路
- 1 解题思路：
  - 1.1 首先统计所有元素的下标
  - 1.2 对于l,r,thres的一个搜索，对所有元素遍历，找出第一个满足要求的元素返回即可：
    - 1.2.1 首先该元素的个数要大于等于thres
    - 1.2.2 在该元素的出现下标的列表中二分搜索，找到第一个大于等于l的下标，和第一个大于r的下标，分别对应到lower_bound和upper_bound

```cpp
class MajorityChecker {
public:
    vector<int> vec;
    unordered_map<int, vector<int>> toPos;
    MajorityChecker(vector<int>& arr) {
        int pos = 0;
        for(auto& num : arr) {
            toPos[num].push_back(pos++);;
        }
    }
    
    int query(int left, int right, int threshold) {
        int res = -1;
        for(auto& [num, positions] : toPos) {
            if(positions.size() < threshold) {
                continue;
            }
            // for num : find the min and max pos in [left, right]
            auto minPos = lower_bound(positions.begin(), positions.end(), left);
            auto maxPos = upper_bound(positions.begin(), positions.end(), right);
            if (maxPos - minPos >= threshold) {
                return num;
            }
        }

        return res;
        
    }
};

```