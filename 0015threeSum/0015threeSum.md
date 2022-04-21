## 0015threeSum 三数之和

### 1 题目
[https://leetcode-cn.com/problems/3sum/](https://leetcode-cn.com/problems/3sum/)

### 2 解题思路
- 1 解题思路：
  - 1.1 使用hash思路：首选用hash<key, val>存起来所有两数之和的负数以及对应出现的次数，然后遍历一遍数组，对于每个数字nums[i]去查询nums[i]在hash中的出现次数，
  - 1.2 1.1中还是有问题，需要记录每个val对应的是哪些pair，不然最后要求返回三元组没办法，其次，三元组是不能重复的（这个好办，对于每个特定三元组，sort然后to_string即可）
- 2 使用排序+双指针的思路
  - 2.1 对于两数之和，也可以先排序，然后用双指针搜索，假设搜索目标为tar, num[st] + num[ed] > tar，就移动ed往左，否则st向右，如果相等，则将st和ed分别移动到和原来不相等的第一个位置即可
  - 2.2 那么对于三数之和，其实就是对于数组里面的每个数字，选定一个为tar，然后剩余的用作两数之和

```cpp
class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        // ervery time, choose one, treat them as twoSum
        sort(nums.begin(), nums.end(), std::less<int>());

        if(nums.size() < 3) {
            return {};
        }
        
        int n = nums.size();
        vector<vector<int>> res;
        for(auto i : nums) {
            cout << i << " ";
        }cout << "\n";
        unordered_set<string> dup;
        for(int i = 0; i < n; ++i) {
            int tar = -nums[i];
            int st = i == 0 ? 1 : 0;
            int ed = i == n-1 ? n-2 : n-1;

            // bin ptr
            int cur = nums[st] + nums[ed];
            do {
                
                if(ed == i) {
                    --ed;
                }
                if(st == i) {
                    ++st;
                }
                if(st >= ed) {
                    break;
                }
                cur = nums[st] + nums[ed];
                // cout << "--- i / st / ed" << i << "/" << st << "/" << ed << endl;
                // cout << nums[i] << " "  << nums[st] << " "  << nums[ed] << "\n";
                if(cur > tar) {
                    --ed;

                } else if(cur < tar){
                    ++st;

                } else {
                    vector<int> tmp = {nums[i], nums[st], nums[ed]};
                    sort(tmp.begin(), tmp.end());
                    string tupleStr = to_string(tmp[0]) + to_string(tmp[1]) + to_string(tmp[2]);
                    if(0 == dup.count(tupleStr)) {
                        dup.insert(tupleStr);
                        // cout << "--->>>> insert >>>> i / st / ed" << i << "/" << st << "/" << ed << endl;
                        // cout << nums[i] << " "  << nums[st] << " "  << nums[ed] << "\n";
                        res.push_back(std::move(tmp));
                    }
                    // move st right, ed left to first different num compared with origin ones
                    int oldEd = nums[ed];
                    int oldSt = nums[st];
                    while(ed >=0 && nums[ed] == oldEd) {
                        --ed;
                    }
                    while(st < n && nums[st] == oldSt) {
                        ++st;
                    }

                }
            } while(st < ed);
        }


        return res;
    }
};

```