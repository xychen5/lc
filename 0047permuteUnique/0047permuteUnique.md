## 0046 全排列

### 1 题目
[https://leetcode-cn.com/problems/permutations-ii/](https://leetcode-cn.com/problems/permutations-ii/)

### 2 解题思路
```cpp
class Solution {
public:
    unordered_set<string> hash;

    vector<vector<int>> permuteUnique(vector<int>& nums) {
        // vector<vector<int>> res;
        // vector<int> tmp;
        // string tmpStr = "";
        // chooseN(nums, nums.size(), res, tmp, tmpStr);
        // vector<vector<int>> res;
        // vector<int> tmp;
        // string tmpStr = "";
        // chooseN2(nums, 0, nums.size(), res, tmpStr);
        vector<vector<int>> res;
        vector<int> tmp;
        vector<bool> vis(nums.size(), false);
        sort(nums.begin(), nums.end());
        chooseN3(nums, 0, nums.size(), res, vis, tmp);
        return res;
    }

    // 160ms
    void chooseN(vector<int>& nums, int n, vector<vector<int>>& res, vector<int>& tmp, string tmpStr) {
        if(n == 0) {
            if(hash.count(tmpStr) == 0) {
                std::cout << tmpStr << std::endl;
                hash.insert(tmpStr);
                res.emplace_back(tmp);
            }
        }

        for(int i = 0; i < nums.size(); ++i) {
            
            vector<int> tmpNums;
            tmpNums.insert(tmpNums.end(), nums.begin(), nums.begin() + i);
            tmpNums.insert(tmpNums.end(), nums.begin() + i + 1, nums.end());
            tmp.emplace_back(nums[i]);
            tmpStr.push_back(static_cast<char>(nums[i] + 107));
            chooseN(tmpNums, n-1, res, tmp, tmpStr);
            tmpStr.pop_back();
            tmp.pop_back();
        }
    }


   
    // chooseN由于每次构造新的串子，这样降低了速度，只用swap到最左边就行了
    // 32ms
    void chooseN2(vector<int>& nums, int st, int n, vector<vector<int>>& res, string tmpStr) {
        if(st == nums.size()) {
            if(hash.count(tmpStr) == 0) {
                std::cout << tmpStr << std::endl;
                hash.insert(tmpStr);
                res.emplace_back(nums);
            }
        }

        for(int i = st; i < nums.size(); ++i) {
            
            vector<int> tmpNums;
            tmpStr.push_back(static_cast<char>(nums[i] + 107));
            swap(nums[st], nums[i]);
                      
            chooseN2(nums, st + 1, nums.size(),  res, tmpStr);

            swap(nums[st], nums[i]);
            tmpStr.pop_back();
        }
    }

    // 由于使用string来判断还是降低了速度，于是在搜索过程中判断是否能够压入
    void chooseN3(vector<int>& nums, int st, int n, vector<vector<int>>& res, vector<bool>& vis, vector<int>& tmp) {
        if(st == nums.size()) {
                res.emplace_back(tmp);
        }

        for(int i = 0; i < nums.size(); ++i) {
            // 如果当前数作为第st层的回溯已经用过了，则不再使用 || 若当前数字和st层上一次使用数字相同，则也不再使用
            if(vis[i] || (i > 0 && nums[i] == nums[i - 1] && !vis[i - 1])) {
                continue;
            }
            // if (vis[i] || (i > 0 && nums[i] == nums[i - 1] && !vis[i - 1])) {
            //     continue;
            // }
            vector<int> tmpNums;
            tmp.emplace_back(nums[i]);
            vis[i] = 1;
                      
            chooseN3(nums, st + 1, nums.size(),  res, vis, tmp);

            vis[i] = 0;
            tmp.pop_back();
            // swap(nums[st], nums[i]);
        }
    }
};
```
