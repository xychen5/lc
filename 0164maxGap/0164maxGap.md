## 0164maxGap 最大间距

### 1 题目
[https://leetcode-cn.com/problems/maximum-gap/](https://leetcode-cn.com/problems/maximum-gap/)

### 2 解题思路
- 1 使用桶排序
  - 1.1 平均时间复杂度o(n + k)，最烂：o(n**2)
- 2 桶排序算
  - 2.1 根据最大最小值算桶的大小
  - 2.2 将桶排列好，将每个值放入(桶内部插入排序)
  - 2.3 将所有的值从桶里取出来，然后形成排序后的数组

```cpp
class Solution {
public:
    int len = -1;
    int maximumGap(vector<int>& nums) {
        len = nums.size();
        if(len <= 1) {
            return 0;
        }
        // bucket sort
        bucketSort(nums);

        // getMaxGap
        int gap = INT_MIN;
        int last = nums[0];
        for(auto i : nums) {
            gap = max(i - last, gap);
            last = i;
        } 
        return gap;
    }

    void bucketSort(vector<int>& nums) {
        int maxNum = *max_element(nums.begin(), nums.end());
        int bucketSize = maxNum / len + 1;
        int bucketNum = len + 1;
        vector<list<int>> buckets(bucketNum, list<int>(0));

        // put to buckets
        for(int i = 0; i < len; ++i) {
            insertSort(buckets[nums[i] / bucketSize], nums[i]);
        }
        
        // merge
        int idx = 0;
        for(auto& l : buckets) {
            for(auto num : l) {
                nums[idx++] = num;
            }
        }
    }
    
    void insertSort(std::list<int>& l, int num) {
        for(list<int>::iterator it = l.begin(); it != l.end(); ++it) {
            if(*it > num) {
                l.insert(it, num);
                return;
            }
        }

        l.push_back(num);
    }
};
```