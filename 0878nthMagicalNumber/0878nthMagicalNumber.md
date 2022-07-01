## 0878nthMagicalNumber 第 N 个神奇数字

### 1 题目
[https://leetcode.cn/problems/nth-magical-number/](https://leetcode.cn/problems/nth-magical-number/)

### 2 解题思路
- 1 解题思路：
  - 1.1 经典二分：并不是遍历去搜索，而是在答案的范围内，去二分，对于每各数字判断它和最终要的结果的大小，决定下一个二分的范围
  - 1.2 具体来说，比如这道题：f(x)表示数字x是第几个magicnumber，很容易知道f(x)单调递增，则可以二分
  - 1.3 f(x) = x/a + x/b - x/LCM(a,b)

```cpp
class Solution {
public:
    long long getLCM(long long x, long long y) {
        return x * y / getGCD(x, y);
    }
    
    long long getGCD(long long x, long long y) {
        long long l = min(x, y);
        long long g = max(x, y);
        long long mod = g % l;
        while(mod != 0) {
            g = l;
            l = mod;
            mod = g % l;
        }
        return l;
    }
    
    constexpr static int MOD = 1'000'000'007;

    int nthMagicalNumber(int n, int a, int b) {
        long long lcm = getLCM(a, b);
        auto getMagicRank = [&](long long x) {
            return x / a + x / b - x / lcm;
        };
        long long st = 0;
        long long ed = 1e15;

        long long mid = -1;
        while(st != ed) {
            mid = (st + ed) >> 1;
            
            long long rank = getMagicRank(mid);
            // cout << "st/ed/mid: " << st << "/" << ed << "/" << mid << " | " << rank << endl;
            if(rank >= n) {
                ed = mid;
            } else {
                st = mid + 1;
            }
        }

        return st % MOD;
    }
};
```