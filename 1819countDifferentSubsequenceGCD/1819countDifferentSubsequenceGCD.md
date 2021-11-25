## 1819countDifferentSubsequenceGCD 所有子序列不同最大公约数数目

### 1 题目
[https://leetcode-cn.com/problems/number-of-different-subsequences-gcds/](https://leetcode-cn.com/problems/number-of-different-subsequences-gcds/)


### 2 解题思路
- 1 自己的思路：对于所有的子序列求GCD，很慢，光GCD就没办法枚举
- 2 逆向思考，从结果出发，所有的GCD共有多少种？一共也就max(nums[0:n-1])这么多个吧？
- 3 那么对于任何一个可能的GCD称为i，如何判断是不是有一个子序列的GCD为i呢？
  - 解法： 对于i，先找出含有i作为因子的子序列(也就是nums中值等于i的整数倍的那些值)
  - 求GCD(greatest common divisor)，两两使用辗转相除即可
```cpp
    int gcd(int a, int b) {
        int modeRes = b;
        do {
            modeRes = a % b;
            a = b;
            b = modeRes;
        } while(modeRes != 0); 
        return a; 
```
main Ref: [https://leetcode-cn.com/problems/number-of-different-subsequences-gcds/solution/mei-ju-mei-ge-ke-neng-de-gong-yue-shu-by-rsd3/](https://leetcode-cn.com/problems/number-of-different-subsequences-gcds/solution/mei-ju-mei-ge-ke-neng-de-gong-yue-shu-by-rsd3/)
```cpp
class Solution {
public:
    
    int gcd(int a, int b) {
        int modeRes = b;
        do {
            modeRes = a % b;
            a = b;
            b = modeRes;
        } while(modeRes != 0); 
        return a; 
    }

    int countDifferentSubsequenceGCDs(vector<int>& nums) {
        int maxNum = *max_element(nums.begin(), nums.end());
        int n = nums.size();
        int ans = 0;
        // set速度可能不够快，使用普通的数组
        // unordered_set<int> set;
        // for(int i = 0; i < n; ++i) {
        //     if(set.count(nums[i]) == 0) {
        //         set.insert(nums[i]);
        //     }
        // }

        // array<bool, 200001> exist;
        vector<bool> exist(200005, false);
        // bool exist[200001];
        for(int i = 0; i < n; ++i) {
            exist[nums[i]] = true;
        }
        
        // 判断每一个可能的公因数 greatest common divisor
        for(int i = 1; i <= maxNum; ++i) {
            // 判断i是否为某个子序列的最大公因数:
            // 则需要判断所有含有i作为因数的位于nums中的数字组成的子序列的最大公因数是否为i
            // 比如当i = 3，而数组为 6 12，则3不是，因为不是最大公因数
            int curGCD = -1; 
            for(int j = i; j <= maxNum; j += i) {
                // j 为 k*i，若其出现在nums中的某个子序列，则对这个子序列两两求gcd
                if(exist[j]) {
                    if(curGCD == -1) {
                        curGCD = j;
                    } else {
                        curGCD = gcd(curGCD, j);
                    }
                }
            }
            if(curGCD == i) {
                ++ans;
            }
        }

        return ans;
    }
}
```