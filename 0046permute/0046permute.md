## 0046 全排列

### 1 题目
[https://leetcode-cn.com/problems/permutations/](https://leetcode-cn.com/problems/permutations/)

### 2 解题思路
```cpp
class Solution {
public:
    unordered_set<string> hash;

    vector<vector<int>> permute(vector<int>& nums) {
        vector<vector<int>> res;
        vector<int> tmp;
        chooseN(nums, nums.size(), res, tmp);
        return res;
    }

    void chooseN(vector<int>& nums, int n, vector<vector<int>>& res, vector<int>& tmp) {
        if(n == 0) {
            res.emplace_back(tmp);
        }

        for(int i = 0; i < nums.size(); ++i) {
            
            vector<int> tmpNums;
            tmpNums.insert(tmpNums.end(), nums.begin(), nums.begin() + i);
            tmpNums.insert(tmpNums.end(), nums.begin() + i + 1, nums.end());
            tmp.emplace_back(nums[i]);
            chooseN(tmpNums, n-1, res, tmp);
            tmp.pop_back();
        }
    }

};
```
