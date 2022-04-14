## 0301removeInvalidParentheses 最少移除括号

### 1 题目
[https://leetcode-cn.com/problems/remove-invalid-parentheses/submissions/](https://leetcode-cn.com/problems/remove-invalid-parentheses/submissions/)

### 2 解题思路
- 1 解题思路：
  - 1.1 暴力搜索，当前字符串，要么要，要么不要，
    - 超时：因为不去考虑字符串的删除非法括号的个数是有限的
  - 1.2 暴力加上剪枝：
    - 1.2.1 整体思路： 每一次选一个括号去减少，但是注意：
      - 第一次for，假设选择了第i个，那么下一次就不必要从0开始，因为假设从0开始，选择了0到i中的第j个，也就j < i
      - 那么第一次循环，选择第j个，下一层选择i就可以，于是选择的括号下标是越来越大c
    - 1.2.2 剪枝思路：
      - 其一： cull 1, (((())), the first 4 same char, only deal the last one
      - 其二： cull 2, if s[i:] not enough for lrm and rrm

```cpp
class Solution {
public:
    unordered_map<string, bool> memo;
    unordered_set<string> had;
    int curMaxLen = 0;
    vector<string> removeInvalidParentheses(string s) {
        vector<string> res;
        string tmp;
        // brute force search puls branch cull
        int lRm, rRm;
        getLRRm(lRm, rRm, s);
        cout <<"l/r" << lRm << " " << rRm << endl;
        backTrack(res, 0, s, lRm, rRm);

        // backTrackOld(res, 0, s, tmp);]
        if(0 == res.size()) {
            res.push_back("");
        }
        return res;
    }

    // bool backTrackOld(vector<string>& res, int st, string s, string& tmp) {
    //     if(st == s.size()) {
    //         // cout << "tmp is: " << tmp << endl;
    //         if(tmp.size() > curMaxLen && checkValid(tmp)) {
    //             res.clear();
    //             res.push_back(tmp);
    //             had.insert(tmp);
    //             curMaxLen = tmp.size();
    //             return true;
    //         } else if(tmp.size() == curMaxLen && checkValid(tmp)) {
    //             if(0 != had.count(tmp)) {
    //                 return true;
    //             }
    //             had.insert(tmp);
    //             res.push_back(tmp);
    //             return true;
    //         }
    //         return false;
    //     }

    //     if(s[st] != '(' && s[st] != ')') {
    //         tmp.push_back(s[st]);
    //         backTrackOld(res, st + 1, s, tmp);
    //         tmp.pop_back();
    //     } else {
    //         // use current
    //         tmp.push_back(s[st]);
    //         // cout << "use: tmp " <<tmp << " -> " << st << endl;
    //         backTrackOld(res, st + 1, s, tmp);
    //         // not use, pop first ( or )
            
    //         tmp.pop_back();

    //         // popFirstParen(tmp);
    //         // cout << "not use: tmp " <<tmp << " -> " << st  << endl;

    //         backTrackOld(res, st + 1, s, tmp);
    //     }
    //     return false;
    // }
    
    void backTrack(vector<string>& res, int st, string& s, int lRm, int rRm) {
        if(0 == lRm && 0 == rRm) {
            cout << s << endl;
            // cout << "tmp is: " << tmp << endl;
            if(checkValid(s)) {
                if(0 == had.count(s)) {
                    res.push_back(s);
                    had.insert(s);
                }
            }
            return ;
        }

        
        for(int i = st; i < s.size(); ++i) {
            if(s[i] == '(' || s[i] == ')') {
                // cull 1, (((())), the first 4 same char, only deal the last one
                if(i != st && s[i] == s[i-1]) {
                    continue;
                }

                // cull 2, if s[i:] not enough for lrm and rrm
                if(s.size() - i < lRm + rRm) {
                    // cout << "not enough! " << endl;
                    return;
                }

                string next = s.substr(0, i) + s.substr(i+1);
                if(lRm > 0 && s[i] == '(') {
                    // cout << "rm ( -> " << next << endl; 
                    backTrack(res, i, next, lRm - 1, rRm);
                }
                if(rRm > 0 && s[i] == ')') {
                    // cout << "rm ) -> " << next << endl; 
                    backTrack(res, i, next, lRm, rRm - 1);
                }
            }
        }
    }

    void popFirstParen(string& tmp) {
        for(int i = tmp.size() - 1; i >= 0; --i) {
            if(tmp[i] == ')' || tmp[i] == '(') {
                tmp.erase(i);
            }
        }
    }

    void getLRRm(int &l, int& r, string& s) {
        l = r = 0;
        for(auto c : s) {
            if(c == '(') {
                ++l;
            } else if(c == ')') {
                if(0 == l) {
                    ++r;
                } else {
                    --l;
                }
            }
        }
    }

    bool checkValid(string& tmp) {
        int l = 0;
        for(auto c : tmp) {
            if(c == '(') {
                ++l;
            } else if(c == ')') {
                if(0 == l) {
                    return false;
                }
                --l;
            }
        }
        return 0 == l;
    }

};
```