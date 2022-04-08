## 0149maxPoints 直线上最多的点

### 1 题目
[https://leetcode-cn.com/problems/max-points-on-a-line/](https://leetcode-cn.com/problems/max-points-on-a-line/)

### 2 解题思路
- 1 对于每一个点，按照斜率统计所有和他组成点对的其它点，某个点的相同斜率对应的点数最大，即为最终结果
- 2 辗转相除法
  - a > b, mod = a % b, 然后将a,b中大的替换成mod，再接着上面的运算，直到mod == 0
  - 考虑 4 % 2这种特殊情况，也就是结果初始化为min(a,b)
```cpp
    int getGCD(int a, int b) {
        int mod = min(a, b);
        int last = min(a, b);
        do {
            if(a > b) {
                last = mod;
                mod = a % b;
                a = mod;
            } else {
                last = mod;
                mod = b % a;
                b = mod;
            }
        }while(mod != 0);
        return last;
    }
```

```cpp
class Solution {
public:
    int candy(vector<int>& ratings) {
        // statisfy the right and left rule
        int n = ratings.size();
        vector<int> candy1(n, 1);
        vector<int> candy2(n, 1);
        for(int i = n - 1; i >= 0; --i) {
            if(i < n-1 && ratings[i] > ratings[i + 1]) {
                candy1[i] = candy1[i + 1] + 1;
            }
        }
        
        for(int i = 0; i < n; ++i) {
            if(i > 0 && ratings[i] > ratings[i - 1]) {
                candy2[i] = candy2[i - 1] + 1;
            }
        }

        int res = 0;
        for(int i = 0; i < candy2.size(); ++i) {
            res += max(candy2[i], candy1[i]);
        }
        return res;
    }
};

```