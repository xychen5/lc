## 0480 滑动窗口中位数

### 1 题目
[https://leetcode-cn.com/problems/sliding-window-median/](https://leetcode-cn.com/problems/sliding-window-median/)


### 2 解题思路
- 1 使用一个multiset维护当前窗口，
  - 1.1 不使用priority_queue的原因，无法删除元素
  - 1.2 不使用map/set的原因，不能含有重复元素
- 2 对于窗口，维护一个中位数指针，注意到中位数指针在每一次窗口移动只会发生几种情况
  - 2.1 向左，向右，不动
  - 2.2 分类讨论清除即可

```cpp
class Solution {
public:
    vector<double> medianSlidingWindow(vector<int>& nums, int k) {
        long long n = nums.size();
        std::multiset<long long, std::less<long long>> mySet(nums.begin(), nums.begin() + k);

        vector<double> res;
        multiset<long long>::iterator mid = mySet.begin();
        std::advance(mid, (k-1)/2);

        for(long long i = k; i <= n; ++i) {
            res.emplace_back((*mid + *next(mid, 1 - k%2))*1.0L/2);
            if(i == n) break;

            mySet.insert(nums[i]);
            if (nums[i] > *mid && nums[i - k] < *mid) {
                mid++;
                mySet.erase(mySet.lower_bound(nums[i-k]));
                continue;
                // std::advance(mid, 1);
            }

            if (nums[i] < *mid && nums[i - k] > *mid) {
                mid--;
                mySet.erase(mySet.lower_bound(nums[i-k]));
                continue;
                // std::advance(mid, -1);
            }
            // 7 3 7 7 4, k = 4
            // 7 8 7 7 4, k = 4
            if(nums[i-k] == *mid) {
                if(nums[i] >= *mid)  ++mid;
                else {
                    if(*prev(mid) != *mid) {
                        --mid;
                    }
                }
                mySet.erase(mySet.lower_bound(nums[i-k]));
                continue;
            } 

            if(nums[i] == *mid) {// 相当于一个比mid大的数字插入到了mid的前面
                if(nums[i-k] <= *mid)  ++mid;
                mySet.erase(mySet.lower_bound(nums[i-k]));
                continue;
            }
        }
        return res;
    }
};

```
