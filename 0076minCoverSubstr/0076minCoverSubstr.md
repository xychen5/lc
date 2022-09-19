## 0076minCoverSubstr 最小覆盖字串

### 1 题目
[https://leetcode.cn/problems/permutation-sequence/](https://leetcode.cn/problems/permutation-sequence)

### 2 解题思路
- 1 解题思路
  - 滑动窗口两阶段：
    - 增加，直到可以cover
    - 减少，直到刚刚好不能cover
    - 更新结果
  - 判断窗口是否cover？
    - 用map记录当前窗口每个字符出现个数，去遍历对比就行


```cpp
class Solution {
public:
    string minWindow(string s, string t) {
        int sLen = s.length();
        int tLen = t.length();

        if(tLen > sLen) {
            return "";
        }

        int st = 0;
        int ed = 0;
        vector<int> win(130, 0);
        vector<int> tar(130, 0);
        for(auto c : t) {
            tar[c]++;
        }

        auto canCover = [](vector<int>& win, vector<int>& tar){
            for(int i = 0; i < 130; ++i) {
                if(win[i] < tar[i]) {
                    return false;
                }
            }

            return true;
        };

        int finRes = INT_MAX;
        pair<int, int> stEd = {st, ed};
        while(ed < s.size()) {
            // mving the ed till win cover tar
            while(ed < sLen && (!canCover(win, tar))) {
                win[s[ed]]++;
                ++ed;
            }

            if(!canCover(win, tar)) {
                // cout << "st/ed: " << st << "/" << ed << " failed!" << endl;
                break;
            }

            // cout << "cover : st/ed: " << st << "/" << ed << endl;
            while(st < sLen && canCover(win, tar)) {
                win[s[st]]--;
                ++st;
            }
            
            // cout << "no cover : st/ed: " << st << "/" << ed << endl;
            if(ed - st + 1 < finRes) {
                stEd = {st - 1, ed - 1};
                // cout << "curres: " << st - 1 << " " <<ed - 1<< endl;
                finRes = ed - st + 1;
            }
        }

        return finRes == INT_MAX ? "" : s.substr(stEd.first, stEd.second - stEd.first + 1);
    }
}
```
