## 1163maxDicOrderStr 最大字典序字串

### 1 题目
[https://leetcode.cn/problems/last-substring-in-lexicographical-order/](https://leetcode.cn/problems/last-substring-in-lexicographical-order/)

### 2 解题思路
- 1 解题思路：
  - 1.1 首先就是，起点必须为最大字符，终点一定是末尾
  - 1.2 那么如何快速搜索:
    - 当出现搜索终止（从前面的z追上后面的z，这个过程的字串一样或者从后面的z开始直接到了末尾都一样），那么直接将搜索下标移动到后面的z搜索的停止位置，因为都是一样的字串，答案一定不会在后面的z的搜索过程的字串里

```cpp
class Solution {
public:
    string lastSubstring(string s) {
        // find max in subffix array
        
        int maxChar = s.back();
        int n = s.size();
        int maxPos = n-1;
        for(int i = n-1; i >= 0; --i) {
            if(s[i] >= maxChar) {
                maxChar = s[i];
                maxPos = i;
            }
        }

        int st = maxPos+1;
        // cout << "init maxPos: " <<maxPos << endl;
        while(st < n) {
            if(s[st] == maxChar) {
                // cmp st and maxPos
                int newSt = st;
                int oldSt = maxPos;
                // cout << "old/new: " << oldSt <<"/" << st << endl;
                while((newSt < n && oldSt < st) && (s[newSt] == s[oldSt])) {
                    ++newSt;
                    ++oldSt;
                }
                if(newSt == n) {
                    // 和下面情况是一样的
                    st = newSt;
                    continue;
                } else if(oldSt == st) {
                    // 答案必然不会在st 和 newSt之间
                    // 原因： s[oldSt:st]之间都是搜索过的z，那么肯定直接从下一个z搜索也就是st+1的位置后面的第一个z
                    // 然后由于从st开始到newSt的字串，没有撼动maxPos到st的这个字串，则直接从st到newSt之间的任何的z的搜索都会是重复计算
                    // 因为：s[oldSt:st]中的所有z都搜索过，然后又因为s[st:newSt] == s[oldSt:st]，那么必然s[st:newSt]中的每个z的都在s[oldSt:st]中
                    // 出现过，所以不会重新搜索，于是可以直接从newSt开始搜索
                    st = newSt;
                    continue;
                }
                if(s[newSt] > s[oldSt]) {
                    maxPos = st;
                }
                ++st;
            } else {
                ++st;
            }
        }

        return s.substr(maxPos);
    }
};
```