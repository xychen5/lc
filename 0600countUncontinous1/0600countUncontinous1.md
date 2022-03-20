## 0600countUncontinous1 不含连续1的非负整数

### 1 题目
[https://leetcode-cn.com/problems/non-negative-integers-without-consecutive-ones/](https://leetcode-cn.com/problems/non-negative-integers-without-consecutive-ones/)

### 2 解题思路
- 1 解题思路：
  - 1.1 很显然的动态规划，首先考虑问题： 给你一个二进制数字a = 2^n，判断从0到a有多少个数字不含有连续的两个1？动态规划即可：
    - dp[len][0] = dp[len - 1][1] + dp[len - 1][0];
    - dp[len][1] = dp[len - 1][0];
    - 其中dp[len][0]表示长度为len然后以0开始的二进制数字的集合中，含有多少个不连续为1的数字
  - 1.2 有了上述的思考，那么对于1024，32这种数字的解答就很显而易见了，比如32 = 100000，那么答案就是：首先假设最高位为0，然后res += dp[5][0] + dp[5][1]，这是所有： 0xxxx和1xxxx组成的答案，但是32是6位数字，还需要加上32本身即可
  - 1.3 更近一步，对于a = 101010 和 b = 110000 这样的呢？
    - 以每一个1对结果的贡献来思考，从高位到低位这样去思考： 
    - 首先拿a来说，我们看最高位，和32一样的解法，接下来我们找到下一个1，那么就是变成，找以前缀为10，后缀为 0xxx 的有多少种，那么动态规划直接找出来就行，那么为什么不是1xxx，因为1xxx加上前缀10可能就大于a了，就超出了范围，那么我们接着找到下一个1，也就是前缀为1010，找0x有多少种，然后最后找不到1，看看a本身是否合理加上即可
    - 对于b，首先第一个1对最终结果的贡献都是和32一样的，那么第二个1呢？很显然，**遇到了连续的第二个1，意味着后面的1对答案都不会有贡献，因为以11为前缀的都是不合法的**，所以仅仅需要考虑，将第二个连续的1变成0，以10为前缀，xxxx有多少中方案，很简单，就是 dp[4][0] + dp[4][1]


```cpp
class Solution {
public:
    int findIntegers(int n) {
        int tmp = n;
        int bit = -1;
        vector<int> bits = {};

        while(tmp > 0) {
            bits.push_back(tmp & 1);
            tmp = tmp >> 1;
        }

        int k = bits.size();
        vector<vector<int>> dp(k, vector<int>(2, 0));

        if(k <= 1) {
            return 2;
        }

        dp[0][0] = 1; // mainly for the last bit is 1
        dp[0][1] = 0;

        dp[1][0] = 1;
        dp[1][1] = 1;

        for(int len = 2; len <= k - 1; ++len){
            dp[len][0] = dp[len - 1][1] + dp[len - 1][0];
            dp[len][1] = dp[len - 1][0];
            // cout << "dp " << len << "/0,1 = " << dp[len][0] << "," << dp[len][1] << endl;
        }

        int lastOneBitIdx = k - 1;

        // assume the biggest bit starts with 0
        int res = dp[lastOneBitIdx][0] + dp[lastOneBitIdx][1];
        // cout << "assume biggest bit = 0's res : " << res << endl;

        bool mySelfOk = true;
        while(lastOneBitIdx > 0) {
            int nextOneBitIdx = lastOneBitIdx - 1;
            cout << ">> last/next: " << lastOneBitIdx << "/" << nextOneBitIdx << endl;
            cout << "bits[next] " << bits[nextOneBitIdx] << endl;

            // find next one bit
            while(bits[nextOneBitIdx] != 1) {
                cout << "not 1 bit: " << nextOneBitIdx << endl;
                -- nextOneBitIdx;
                if(nextOneBitIdx == -1) {
                    return res + mySelfOk;
                }
            }

            cout << "last/next: " << lastOneBitIdx << "/" << nextOneBitIdx << endl;
            if(lastOneBitIdx - nextOneBitIdx < 2) {
                // view the bits[nextOneBitIdx] as 0
                res += dp[nextOneBitIdx][0] + dp[nextOneBitIdx][1];
                mySelfOk = false;
 
                // cout << "+ dp " << nextOneBitIdx << "," << 0 << " break!!!" << endl;
                break;
            } else {
                // view the bits[nextOneBitIdx] as 0
                res += dp[nextOneBitIdx][0] + dp[nextOneBitIdx][1];
                lastOneBitIdx = nextOneBitIdx;
                // cout << "+ dp " << nextOneBitIdx << "," << 0 << endl;
                // cout << "lastOneBitIdx is " << lastOneBitIdx << endl;
                // cout << "curRes = " << res;

            }
        }

        cout << "me ok: " << mySelfOk << endl;

        return res + mySelfOk;
    }
};
```