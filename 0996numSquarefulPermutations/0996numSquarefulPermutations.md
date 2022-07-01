## 0996numSquarefulPermutations 正方形数组的排列个数

### 1 题目
[https://leetcode.cn/problems/number-of-squareful-arrays/](https://leetcode.cn/problems/number-of-squareful-arrays/)

### 2 解题思路
- 1 解题思路：
  - 回溯获取全排列，backTrack带st参数，表示正在放第st个数字，注意此时nums[:st-1]是已经放好的排列，只需要在nums[st:]后半部分填充到st位置即可，也就是交换一下
  - 剪枝：若nums[st]和nums[st-1]的和不是完全平方数，则直接不进入下一个st
  - 记忆化搜索：考虑例子：2 2 2 2 2 2 2，使用memo[st][num]，表示，在当前nums[:st-1]作为排列前缀的时候，num值放在st是否被搜索过，搜索过则标记一下，下一次不搜了
    - 需要注意一点：memo[st][num]，表示在当前nums[:st-1]作为排列前缀在st放值时刻的num值的搜索情况，所以当st位置所有num值搜索完成，要返回进入下一个排列前缀搜索之前，记得clear掉，这个和0698这道题很像

```cpp
class Solution {
public:
    void swap(int& a, int& b) {
        int c = a;
        a = b;
        b = c;
    }

    bool judge(double tar) {
        double x = sqrt(tar);
        if(floor(x) == x) {
            return true;
        }
        return false;
    }

    void print(vector<int>& vec) {
        for(auto i : vec) {
            cout << i <<" ";
        }cout <<"\n";
    }

    unordered_set<string> rmDup;
    
    // memo thah: cal[st][num] in pos st, whethter num has been visited
    unordered_map<int, unordered_map<int, bool>> cal;

    // st means : we are choosing a num for nums[st]
    // and we should be sure that: nums[st] and nums[st-1] is able to sqrt 
    int permutationCheck(vector<int>& nums, int st) {
        if(st == nums.size()) {
            string tmp = "";
            for(auto& i : nums) {
                tmp += to_string(i);
            }
            if(rmDup.insert(tmp).second) {
                return 1;
            }
            return 0;
        }

        int res = 0;
        for(int i = st; i < nums.size(); ++i) {
            swap(nums[i], nums[st]);
            // cout << "level: " << st << " ";
            // print(nums);
            if(st == 0) {
                if(!cal[st][nums[st]]) {
                    res += permutationCheck(nums, st + 1);
                    cal[st][nums[st]] = true;
                }
            } else {
                if(judge(nums[st-1] + nums[st])) {
                    if(!cal[st][nums[st]]) {
                        res += permutationCheck(nums, st + 1);
                        cal[st][nums[st]] = true;
                    }
                }
            }
            swap(nums[i], nums[st]);
        }

        // when return, the permutated prefix: nums[:st-1] will change, so we clear the memo
        cal[st].clear(); 
        return res;
    }

    int numSquarefulPerms(vector<int>& nums) {
        int n = nums.size();
        if(1 == n) {
            return judge(nums.front());
        }

        // all sequence(permutation) and check each
        return permutationCheck(nums, 0);
    }
};
```
