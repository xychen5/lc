## 0479largestPalindrome 最大回文数乘积

### 1 题目
[https://leetcode-cn.com/problems/largest-palindrome-product/](https://leetcode-cn.com/problems/largest-palindrome-product/)

### 2 解题思路
- 1 解题思路： 逆向思维，不要想着对每一个n位数乘以n位数的数对去判断，而是从2n位的回文结果中，看是否有两个数字乘积等于该回文
- 2 对于n位乘以n位，为何不考虑2*n - 1的回文，因为确定能够从2n位回文中找到结果
```cpp
class Solution {
public:

    int largestPalindrome(int n) {
        if(n == 1) {
            return 9;
        }
        // reverse thinking
        // traverse all Palindrome from big to small, if this num can be acuired through 2 nbit num's mul
        // return
        set<long long, std::greater<long long>> res;
        long long max = pow(10, n);
        for(long long tar = max - 1; tar >= max / 10; --tar) {
            string pali1 = to_string(tar);
            int oriLen = pali1.length();
            for(int i = pali1.length() - 1; i >= 0; --i) {
                pali1.push_back(pali1[i]);
            }
            // cout << pali1 << " " << pali2 << endl;

            long long revNum = stol(pali1);

            // check factor, cause a * b == revNum, then we travel the big one such as a, then when a * a < revNum
            // there will be no answer
            for(long long factor = max; factor * factor > revNum; --factor) {
                if(revNum % factor == 0) {
                    return revNum % 1337;
                }
            }

        }
        
        return -1;

    }
};
```