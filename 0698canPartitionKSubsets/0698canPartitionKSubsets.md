## 0698canPartitionKSubsets 可以划分为k个等和子集

### 1 题目
[https://leetcode.cn/problems/partition-to-k-equal-sum-subsets/](https://leetcode.cn/problems/partition-to-k-equal-sum-subsets/)

### 2 解题思路
- 1 解题思路：
  - 1.1 首先，我们之前的回溯都是最多一个搜索目标，比如8皇后，那就是一个棋盘作为搜索目标，比如划分成2个等和子集，那就是搜索一个子集的值为sum/2，那么这种多目标如何考虑？其实就是，这样想，多个等和子集对吧？那不就是对于数组的每一个数组，在0到k-1号集合里面嘛，这样去回溯就好了
  - 1.2 那么需要写成： 每一个数字在每一个桶里面的情况吗？不需要，为啥？因为对于第i个数字，我们会尝试每一个桶，写成双层for循环智慧带来多余的计算：
  - 1.3 什么时候能进入下一层？当前桶能够放下没被用过的最小的数字，那么没被用过的数字是否需要标记，不需要，为什么，因为我们回溯的时候，每个数字就是下一层，然后每一层不过有4个选择罢了
  - 1.4 考虑使用记忆化加速？
    - 比如：当nums[i]放入通bucket[buc]，失败了，那么后面所有桶值为bucket[buc]，那么就不再去搜索就行
    - 那么需要注意：这是考虑在所有nums[0 : i-1]都相同的情况下才能用这个记忆，一旦第i号所有搜索都失败了，那么我们需要将memo[i]清除，以便后续操作

- 2 1.2的时机例子如下：典型的多余的for循环：1取到1，2取到2，那么当最外层的2取到2，1又取到1，那不就是重复计算了嘛
```cpp
// for every number, try bucket from 0 to k-1
    void backTrack(vector<int>& nums, vector<int>& buckets, int tar) {
        if(fin) {
            return ;
        }

        bool tmp = true;
        for(auto& buc : buckets) {
            tmp = tmp && (buc == tar);
        }
        if(tmp) {
            fin = true;
        }

        for(int i = 0; i < nums.size(); ++i) {
            if(!used[i]) {
                for(int buc = 0; buc < buckets.size(); ++buc) {
                    buckets[buc] += nums[i]; // put it into buc
                    used[i] = true;
                    if(buckets[buc] <= tar) {
                        backTrack(nums, buckets, tar);
                    }
                    buckets[buc] -= nums[i];
                    used[i] = false;
                }
            }
        }

    }
```

标准的带有返回值的写法：

```cpp
class Solution {
public:
    vector<int> used;
    bool canPartitionKSubsets(vector<int>& nums, int k) {
        vector<int> buckets(k, 0);
        used.resize(nums.size(), false);

        sort(nums.rbegin(), nums.rend());

        int sum = accumulate(nums.begin(), nums.end(), 0);
        if(sum % k != 0) {
            return false;
        }

        int tar = sum / k;
        if(nums[0] > tar) {
            return 0;
        }

        vector<unordered_set<int>> memo(nums.size()); // for node[i], memo[i][j]means： node[i] put into a bucket with value j will failed
       
        return backTrack(nums, buckets, 0, tar, memo);
    }

    // for every number, try bucket from 0 to k-1
    bool backTrack(vector<int>& nums, vector<int>& buckets, int st, int tar, vector<unordered_set<int>>& memo) {
        
        // 所有数字都放进去了，成功了
        if(st == nums.size()) {
            return true;
        }
        
        for(int buc = 0; buc < buckets.size(); ++buc) {
            if(0 == memo[st].count(buckets[buc])) {
            // if(buckets[i]) {
                buckets[buc] += nums[st]; // put it into buc
                // used[st] = true;
                if(buckets[buc] == tar || (tar - buckets[buc] >= nums.back())) {
                    // cout << "to buc: " << buc << endl;
                    if(backTrack(nums, buckets, st + 1, tar, memo)) {
                        return true; // 提前返回，因为已经找到一个结果
                    }
                }
                buckets[buc] -= nums[st];
                
                // 如果nums[st] 放入 buckets[buc]失败了，那么后面值相同的桶都会失败，就不用放了
                memo[st].insert(buckets[buc]);
            }
        }

        // 说明放错桶的不是st，而是nums[0 : st-1]中的某个，于是把memo清除掉
        memo[st].clear();

        return false;
    }
}
```
我写的回溯不喜欢带返回值，后面是带有返回值的：

```cpp
class Solution {
public:
    vector<int> used;
    bool fin = false;
    bool canPartitionKSubsets(vector<int>& nums, int k) {
        vector<int> buckets(k, 0);
        used.resize(nums.size(), false);

        sort(nums.rbegin(), nums.rend());

        int sum = accumulate(nums.begin(), nums.end(), 0);
        if(sum % k != 0) {
            return false;
        }

        int tar = sum / k;
        if(nums[0] > tar) {
            return 0;
        }
       
        int useCnt = 0; 

        vector<unordered_set<int>> memo(nums.size());
        backTrack(nums, buckets, 0, tar, useCnt, memo);

        return fin;
    }

    // for every number, try bucket from 0 to k-1
    void backTrack(vector<int>& nums, vector<int>& buckets, int st, int tar, int& useCnt,  vector<unordered_set<int>>& memo) {
        if(fin) {
            return ;
        }

        if(useCnt == nums.size()) {
            bool tmp = true;
            for(auto& buc : buckets) {
                tmp = tmp && (buc == tar);
            }
            if(tmp) {
                fin = true;
                return;
            }
        }

        if(useCnt == nums.size()) {
            return; // return true就行
        }
        

        for(int buc = 0; buc < buckets.size(); ++buc) {
            if(0 == memo[st].count(buckets[buc])) {
                buckets[buc] += nums[st]; // put it into buc
                ++useCnt;
                if(buckets[buc] == tar || (tar - buckets[buc] >= nums.back())) {
                    // cout << "to buc: " << buc << endl;
                    backTrack(nums, buckets, st + 1, tar, useCnt, memo); 
                }

                buckets[buc] -= nums[st];
                
                // 如果nums[st] 放入 buckets[buc]失败了，那么后面值相同的桶都会失败，就不用放了
                memo[st].insert(buckets[buc]);
                
                --useCnt;    
            }
        }

        // 说明放错桶的不是st，而是nums[0 : st-1]中的某个，于是把memo清除掉
        memo[st].clear();


    }
}
```
