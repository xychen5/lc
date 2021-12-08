## 1106 parseBoolExpr 解析bool表达式

### 1 题目
[https://leetcode-cn.com/problems/parsing-a-boolean-expression/](https://leetcode-cn.com/problems/parsing-a-boolean-expression/)

### 2 解题思路
- 1 个人思路：
  - 就像是剥洋葱一样的递归：
  - 解析父操作：
    - 1.1 得到父操作的所有参与项
    - 1.2 递归处理得到父操作的所有参与项的结果
    - 1.3 得到父操作的结果
```cpp
class Solution {
public:
    bool parseBoolExpr(string expression) {
        replace(expression.begin(), expression.end(), '{', '(');
        replace(expression.begin(), expression.end(), '}', ')');
        return parseNextLevel(expression);
    }

    bool parseNextLevel(string expression) {
        char op = expression[0];
        bool res = true;
        int n = expression.size();
        switch(op) {
            case '!' : {
                return !parseNextLevel(expression.substr(2, n - 3));
            } break;
            case '|' : {
                res = false;
                vector<string> subStr = getAndOrSubString(expression.substr(2, n - 3));
                if(subStr.size() == 1){
                    res = orOp(subStr[0]);
                } else {
                    for(auto s : subStr) {
                        res = res || parseNextLevel(s);
                    }
                }
            } break;
            case '&' : {
                vector<string> subStr = getAndOrSubString(expression.substr(2, n - 3));
                if(subStr.size() == 1) {
                    res = andOp(subStr[0]);
                } else {
                    for(auto s : subStr) {
                        res = res && parseNextLevel(s);
                    }
                }
                
            } break;
            default : {
                return getBool(expression[0]);
            }
        }
        return res;
    }

    bool getBool(char a) { return a != 'f' ? true : false;}

    // vector<string> getNotSubString(string expression) {
    //     int cntLeft = 
    //     for()
    // }

    vector<string> getAndOrSubString(string expression) {
        vector<string> res;
        int cntLeft = 0;
        int st = 0;
        int n = expression.size();
        for(int i = 0; i < expression.size(); ++i) {
            if(expression[i] == '(') {
                ++cntLeft;
            }
            if(expression[i] == ')') {
                --cntLeft;
            }
            if(expression[i] == ',' && cntLeft == 0) {
                res.emplace_back(expression.substr(st, i - st));
                st = i + 1;
            }
        }
        res.emplace_back(expression.substr(st));
        cout << expression << " >>> " << endl;
        for(auto s : res) {
            cout << s << endl;
        }
        return res;
    }

    bool orOp(string s) {
        bool res = false;
        for(auto c : s) {
            if(c == 'f' || c == 't') {
                res = res || getBool(c);
            }
        }
        return res;
    }
    bool andOp(string s) {
        for(auto c : s) {
            if(c == 'f') {
                return false;
            }
        }
        return true;
    }
};
```
