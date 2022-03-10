## 0354ruassianRepeatEnvelope_LongestIncreaseSequece 2d 最长递增序列

### 1 题目
基础：
[https://leetcode-cn.com/problems/longest-increasing-subsequence/](https://leetcode-cn.com/problems/longest-increasing-subsequence/)

[https://leetcode-cn.com/problems/russian-doll-envelopes/](https://leetcode-cn.com/problems/russian-doll-envelopes/)

### 2 解题思路
- 1 最开始的思路，很显然可以严格判断信封大小，那么就dp:
  - 1.0 下面思路要求最长递增子序列，那么必须将信封按照从小到大排序，先w再h即可
  - 1.1 dp[i] = max(dp[j] + 1) {j从0到i-1}，dp[i]表示以第i个信结尾的最长子序列长度
- 2 1会超时，然后考虑使用[https://leetcode-cn.com/problems/longest-increasing-subsequence/](https://leetcode-cn.com/problems/longest-increasing-subsequence/)的二分法加速，但是，二分法需要在某个严格递增信封组找到第一个大于输入信封，然后用输入信封替换，但是很显然有问题，比如[2,3],[3,4]是严格递增的，但是来了一个[2,5],那么[3,4]究竟还替换否？于是两维度一起考虑作罢
- 3 早就该想到，去用降维访问了，那么由于一个entry有w,h，先按照，w然后h都递增的方式，可以仅仅考虑h了，比如：[[2,100],[3,200],[4,300],[5,250],[5,400],[5,500],[6,370],[7,380]]，但是很显然有问题，由于w=5的有三个h，导致我们会发现仅仅考虑h的最长递增子序列的长度为7，于是如何解决，对于同一个w，在最后的递增子序列仅仅出现一个h呢？
  - **那就是将h的递增改为递减，这个时候就可以确保同一个w的h序列，在最终最长子序列中仅仅出现一次**

### 3 代码：
- o(n^2)两维度一起考虑，会超时
```cpp
class Solution {
public:
    int maxEnvelopes(vector<vector<int>>& envelopes) {
        int n = envelopes.size();
        if(n == 1) {
            return 1;
        }

        sort(envelopes.begin(), envelopes.end(), [&](vector<int>& a, vector<int>& b) {
            if(a[0] < b[0]) {
                return true;
            } else if(a[0] == b[0]) {
                return a[1] < b[1];
            } else {
                return false;
            }
        });

        // for(auto v : envelopes) {
        //     cout << v[0] << ", " << v[1] << "]  ";
        // }

        int len = 1;
        int res = 1;
        vector<int> dp(n, 1);
        for(int i = 1; i < n; ++i) {
            for(int j = 0; j < i; ++j) {
                if(lt(envelopes[j], envelopes[i])) {
                    dp[i] = max(dp[i], dp[j] + 1);
                    res = max(dp[i], res);
                }
            }
        }
        return res;
    }

    bool gt(vector<int>& a, vector<int> &b) {
        return a[0] > b[0] && a[1] > b[1];
    }

    bool lt(vector<int>& a, vector<int> &b) {
        return a[0] < b[0] && a[1] < b[1];
    }
};
```

- 降维，然后二分查找加速：
```cpp
class Solution {
public:
    int maxEnvelopes(vector<vector<int>>& envelopes) {
        int n = envelopes.size();
        if(n == 1) {
            return 1;
        }
        int len = 1;
        
        // by x, already increasing
        sort(envelopes.begin(), envelopes.end(), [&](vector<int>& a, vector<int>& b) {
            if(a[0] < b[0]) {
                return true;
            } else if(a[0] == b[0]) { // then, with same x, can only get one y, this is the core
                return a[1] > b[1];
            } else {
                return false;
            }
        });

        // only care about the y
        vector<int> minBitLIS = { envelopes[0][1] };
        for(int i = 1; i < n; ++i) {
            if(envelopes[i][1] > minBitLIS.back()) {
                ++len;
                minBitLIS.push_back(envelopes[i][1]);
            } else {
                *lower_bound(minBitLIS.begin(), minBitLIS.end(), envelopes[i][1]) = envelopes[i][1];
            }

        }
        return len;
    }
};
```