## 0982countTriple 按位与为1的三元组个数

### 1 题目
[https://leetcode-cn.com/problems/triples-with-bitwise-and-equal-to-zero/submissions/](https://leetcode-cn.com/problems/triples-with-bitwise-and-equal-to-zero/submissions/)

### 2 解题思路
- 1 解题思路：
  - 1.1 首先很容易想到n^3的解法
  - 1.2 我们注意到，n^3的解法中，我们对每两个数的按位与进行了n次重复计算，于是用hash存起来优化
  - 具体优化思路：首先and2中存取了两两数字的按位与的出现个数，然后对于每一个数字x，我们遍历所有与x按位与为0的数字，然后再and2中查找他们出现的次数，最后将这些次数加起来即可
  - 如何获取所有与x按位与为0的数字？
  - 从 maxNum = (!x & 0x0000ffff)一直遍历到1即可，因为数字最大为16位，不可能超过maxNum


```cpp
class Solution {
public:
    int countTriplets(vector<int>& nums) {
        unordered_map<int, int> and2;
        int n = nums.size();
        for(int i = 0; i < n; ++i) {
            for(int j = 0; j < n; ++j) {
                ++ and2[nums[i] & nums[j]];
            }
        }
        
        int res = 0;
        for(int i = 0; i < n; ++i) {
            // construct the max num which do bit and with num[i] that equals 0
            int maxNum = (~nums[i]) & 0x0000FFFF;
            
            // then we enums all numbers that smaller then maxNum
            for(int tar = maxNum; tar > 0; tar = (tar-1)&(maxNum)) {
                res += and2[tar];
            }

            res += and2[0];
        }

        return res;

    }
};
```