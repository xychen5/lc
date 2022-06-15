## 1537maxScore 最大得分

### 1 题目
[https://leetcode.cn/problems/get-the-maximum-score/submissions/](https://leetcode.cn/problems/get-the-maximum-score/submissions/)

### 2 解题思路
- 1 解题思路：
  - 1.1 考虑这样一个感觉： 以相同点作为joint，将整个数列分成好几段，然后每一段取最大即可
  - 1.2 那么我们用sum1和sum2记录，分别遍历nums1和nums2的时候的和，每次将ssum1和sum2移动到同一个joint，然后才开始下一个joint，最后一个joint的后面加起来然后取模即可
  - 1.3 要注意，处理每个joint的过程中不要去取模，否则容易导致sum大小不是本来的大小，应该在到达同一个joint之后去取模，然后同步sum1和sum2为更大的那个sum
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