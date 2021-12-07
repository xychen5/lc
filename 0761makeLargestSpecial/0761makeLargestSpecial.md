## 0761 makeLargestSpecial 特殊的二进制序列

### 1 题目
[https://leetcode-cn.com/problems/special-binary-string](https://leetcode-cn.com/problems/special-binary-string)

### 2 解题思路
- 1 个人思路：
  - 首先这个特殊子序列，采用合理的括号串去理解特殊子序列就好了
  - 然后大致的递归思路：
    - 1.1 首先找到原来串里所有特殊的子序列
    - 1.2 将这些子序列按照字典序排序
    - 1.3 排序后加起来得到结果
    - 1.4 eg： 10 1100 111000，这个串可以分成三个特殊子序列：那么最大字典序显然就是 111000 1100 10
  - 上面的还有其他问题，若子串一开始不能分为特殊子序列呢？
    - eg：1 10 1100 0， 那么首先剥去外壳，然后再递归进去，对10 1100采用上述子序列方法
  - 递归返回？当子序列长度小于等于2，就直接返回字符串北盛即可
  - 
有个很容易出错误的示例需要注意：
> we shall reArrange first and then sort,
> because when we reArrage, we my produce bigger subStr, 
> if we sort first and reArrange all subpart we could get false res: eg: 
> input:        "11100011010101100100"
> false Result: "111000 11100101010100" // part2 is bigger subStr, so we shall reArrange all sub first and then sort
> std result:   "11100101010100 111000" 
```cpp
class Solution {
public:
    string makeLargestSpecial(string s) {
        string res = reArrange(s);
        // string lastRes = "";
        // while(res != reArrange(res)){
        //     res = reArrange(res);
        // };
        return res;
    }

    string reArrange(string s) {
        // cout << "c1->"  << s << endl;
        int n = s.size();
        if(s.size() <= 2) {
            // cout << "less than 2: " << s << endl;
            return s;
        }

        // firstly, get all special subStr and sort as the lexical order
        vector<string> subStr;

        int st = 0;
        int cntRedundantNumberOne = 1;
        for(int i = st + 1; i < n; ++i) {
            cntRedundantNumberOne += (s[i] == '1' ? 1 : -1);
            if(0 == cntRedundantNumberOne) {
                subStr.emplace_back(s.substr(st, i - st + 1));
                st = i + 1;
                cntRedundantNumberOne = 0;
            }
        }

        if(1 == subStr.size()) {

            return s.substr(0, 1) + reArrange(s.substr(1, n-2)) + s.substr(n-2, 1);
        }

        // for(auto i : subStr) {
        //     cout << i << endl;
        // }
        
        
        // secondly, sort all sub part and sum up
        // cout << "a" << endl;
        for(int i = 0; i < subStr.size(); ++i) {
            subStr[i] = reArrange(subStr[i]);
        }
        // we shall reArrange first and then sort,
        // because when we reArrage, we my produce bigger subStr, 
        // if we sort first and reArrange all subpart we could get false res: eg: 
        // input:        "11100011010101100100"
        // false Result: "111000 11100101010100" // part2 is bigger subStr, so we shall reArrange all sub first and then sort
        // std result:   "11100101010100 111000" 
        sort(subStr.begin(), subStr.end(), std::greater<string>());

        string res = "";
        for(auto s : subStr) {
            res += s;
        }

        // cout << "c2" << endl;
        return res;
    }
};
```
