## 0899orderlyQueue 有序队列

### 1 题目
[https://leetcode.cn/problems/orderly-queue/](https://leetcode.cn/problems/orderly-queue/)

### 2 解题思路
- 1 解题思路：
  - 1.1 当k=1，循环移动第一个char，找出字典序最小即可
  - 1.2 当k>=2，你会发现可以得到任意字典序的字符串，其实就是i,j位置的字符可以交换，那直接把字符串sort就行

```cpp
class Solution {
public:
    string orderlyQueue(string s, int k) {
        string res = s;
        if(1 == k) {
            for(int i = 0; i < s.length(); ++i) {
                char tmp = s.front();
                s = std::move(s.substr(1));
                s.push_back(tmp);
                res = min(s, res);
            }
            return res;
        } else {
            sort(s.begin(), s.end(), std::less<char>());
            res = std::move(s);
        }

        return res;
    }
};
```