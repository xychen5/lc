## 0632smallestRange 最小区间

### 1 题目
[https://leetcode-cn.com/problems/smallest-range-covering-elements-from-k-lists/](https://leetcode-cn.com/problems/smallest-range-covering-elements-from-k-lists/)

### 2 解题思路
- 1 解题思路：首先问题转换为，从每个列表中选择一个数据，使得构成的区间最小
  - 1.1 具体的贪心策略：初始化heap为列表所有最小值，记录当前所有最小值对应的下标，每次将最小值对应的列表的下标向右移动一下，更新heap(存了最小值，最大值也用heap获得)，然后获得一个区间作为结果
  - 1.2 将所有区间取最小区间即可
  - 1.3 退出循环的方式就是，有一个列表的指针将要移动到自己的范围外

```cpp
class Solution {
public:
    vector<int> smallestRange(vector<vector<int>>& nums) {
        auto cmp1 = [](const pair<int, int>& a, const pair<int, int>& b) {
            return a.first > b.first;
        };
        auto cmp2 = [](const pair<int, int>& a, const pair<int, int>& b) {
            return a.first < b.first;
        };
        priority_queue<pair<int, int>, vector<pair<int, int>>, decltype(cmp1)> left(cmp1);
        priority_queue<pair<int, int>, vector<pair<int, int>>, decltype(cmp2)> right(cmp2);

        auto cmp = [](const pair<int, int>& a, const pair<int, int>& b) {
            return !(a.second - a.first < b.second - b.first || \
             (a.second - a.first == b.second - b.first && a.first < b.first));
        };
        priority_queue<pair<int, int>, vector<pair<int, int>>, decltype(cmp)> res(cmp);
        

        int k = nums.size();
        vector<int> choosedNums;
        for(int i = 0; i < k; ++i) {
            choosedNums.push_back(0);
            left.push({nums[i][0], i});
            right.push({nums[i][0], i});
        }
        res.push({left.top().first, right.top().first});
        
        int curMaxChoosedIdx = 0;
        while(1) {

            int l = left.top().first;
            int lIdx = left.top().second;

            left.pop();
            
            if(choosedNums[lIdx] == nums[lIdx].size() - 1) {
                break;
            }

            left.push({nums[lIdx][++choosedNums[lIdx]], lIdx});
            right.push({nums[lIdx][choosedNums[lIdx]], lIdx});

            res.push({left.top().first, right.top().first});            

        } 

        return {res.top().first, res.top().second};
    }

};
```