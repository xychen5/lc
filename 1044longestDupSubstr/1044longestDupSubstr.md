## 1044. 最长重复子串 longestDupSubstring

### 1 题目
[https://leetcode-cn.com/problems/longest-duplicate-substring/](https://leetcode-cn.com/problems/longest-duplicate-substring/)

### 2 解题思路
- 0 使用官方思路： [rabin-karp + binarySearch](https://leetcode-cn.com/problems/longest-duplicate-substring/solution/zui-chang-zhong-fu-zi-chuan-by-leetcode-0i9rd/)
- 1 这里需要使用rabin-karp算法，在长度为n的text中寻找长度为m的模式串，其复杂度为o(m)，然后用二分法去确定最长字符串的长度，故整体复杂度为O(n logn)，拉宾-卡普算法参考：[https://xychen5.github.io/2021/12/28/rabinKarp/](https://xychen5.github.io/2021/12/28/rabinKarp/)
``` cpp

typedef pair<long long, long long> pll;
class Solution {
public:
    static constexpr int big = 1000000006;
    // cal: a^m % mod, when m = 1000, a = 26, there will be overflow
    long long pow(int a, int m, int mod) {
        long long ans = 1;
        long long curNum = a;
        while(m > 0) {
            if(m % 2 == 1) {
                ans = ans * curNum % mod;       
                // overflow
                if(ans < 0) { 
                    ans += mod;
                }
            }
            curNum = curNum * curNum % mod;
            // overflow
            if(curNum < 0) {
                curNum += mod;
            }
            m /= 2;
        }
        return ans;
    }

    // return st of substr with len = len
    int check(vector<int>& arr, int len, int a1, int a2, int mod1, int mod2) {
        int n = arr.size();
        long long powA1 = pow(a1, len, mod1);
        long long powA2 = pow(a2, len, mod2);
        long long hashA1 = 0, hashA2 = 0;

        // cout << "d2.5" << endl;
        // cal hash of the first substr
        // hashA1 = arr[0] * a1^(len-1) + arr[1] * a1^(len-2) + ... + arr[len-1]
        for(int i = 0; i < len; ++i) {
            hashA1 = (hashA1 * a1 % mod1 + arr[i]) % mod1;
            hashA2 = (hashA2 * a2 % mod2 + arr[i]) % mod2;
            hashA1 += hashA1 >= 0 ? 0 : mod1;
            hashA2 += hashA2 >= 0 ? 0 : mod2;
        }

        // cout << "d3" << endl;
        // calculate all substr's hash with len = len
        set<pll> seen;
        seen.emplace(hashA1, hashA2);
        for(int st = 1; st <= n - len; ++st) {
            // cout << "d4" << endl;
            // O(1) to cal next hash
            hashA1 = (hashA1 * a1 % mod1 - arr[st - 1] * powA1 % mod1 + arr[st + len - 1]) % mod1;
            hashA2 = (hashA2 * a2 % mod2 - arr[st - 1] * powA2 % mod2 + arr[st + len - 1]) % mod2;
            hashA1 += hashA1 >= 0 ? 0 : mod1;
            hashA2 += hashA2 >= 0 ? 0 : mod2;
            // before cursubstr, there is a same one
            if(seen.count(make_pair(hashA1, hashA2))) {
                return st;
            }
            seen.emplace(hashA1, hashA2);
        }

        return -1;
    }

    string longestDupSubstring(string s) {
        int n = s.size();

        // code the string
        vector<int> arr(n);
        for(int i = 0; i < n; ++i) {
            arr[i] = s[i] - 'a';
        }

        // two random base and mod
        srand((unsigned)time(NULL));
        int a1 = random()%75 + 26;
        int a2 = random()%75 + 26;
        int mod1 = random()%(INT_MAX - big) + big;
        int mod2 = random()%(INT_MAX - big) + big;
        
        // bin search the length of longest dup substr
        int l = 1, r = n - 1;
        int finalSt = -1, finalLen = -1;
        while(l <= r) {
            // m represents target len
            // int m = (l + r) / 2; 
            int m = l + (r - l + 1) / 2; 
            // cout << "d1" << endl;
            int st = check(arr, m, a1, a2, mod1, mod2);
            // cout << "d2" << endl;
            if(st != -1) {
                finalLen = m;
                l = m + 1;
                finalSt = st;
            } else {
                r = m - 1;
            }
        }
        return finalLen == -1 ? "" : s.substr(finalSt, finalLen);
    }
}

```