## 0060kthPermutation 排列序列

### 1 题目
[https://leetcode.cn/problems/permutation-sequence/](https://leetcode.cn/problems/permutation-sequence)

### 2 解题思路
- 1 解题思路
  - 获取第k个排序序列，然后有n个候选项，我们考虑这样最高位置：
  - 最高位置加1，那么后面的n-1位置提供(n-1)!个方法，所以，最高位为：vec[k / ((n-1)!)]，vec为候选子项，比如改题目：就是1到9，然后由于元素不能重复，我们需要喊出vec中刚用的那个数字，然后递归下去
  - 当剩下的K为0或者1的时候，为0，意味着上一次我们的最高位选定后，剩余的直接最大就行，也就是vec逆序返回即可
  - 当为1的时候，意味着上一次最高位能达到的最大值为第k-1个，则直接返回vec
  - 注意vec一开始是增序排序的


```cpp
class Solution {
public:
    static constexpr int f[10] = {
        1,
        1,
        1*2,
        1*2*3,
        1*2*3*4,
        1*2*3*4*5,
        1*2*3*4*5*6,
        1*2*3*4*5*6*7,
        1*2*3*4*5*6*7*8,
        1*2*3*4*5*6*7*8*9
    };

    string getPermu(string& vec, int leftBits, int leftK) {
        if(leftK == 1) {
            return vec;
        } else if(leftK == 0) {
            sort(vec.rbegin(), vec.rend());
            return vec;
        }
        int curBit = leftK / f[leftBits - 1];
        int newLeftK = leftK % f[leftBits - 1];
        if(newLeftK == 0) {
            curBit = max(0, curBit - 1);
        }
        string tmp;
        tmp.push_back(vec[curBit]);

        vec.erase(vec.begin() + curBit);
        return tmp + getPermu(vec, leftBits - 1, newLeftK);
    }

    string getPermutation(int n, int k) {
        string vec;
        for(int i = 1; i <= n; ++i) {
            vec.push_back(i + '0');
        }
         
        return getPermu(vec, n, k);
    }
};
```
