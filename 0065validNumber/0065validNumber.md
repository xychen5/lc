## 0065validNumber 有效数字

### 1 题目
[https://leetcode.cn/problems/valid-number/](https://leetcode.cn/problems/valid-number/)

### 2 解题思路
- 1 解题思路
  - 将小数按照左右两侧去检测整数正确性
  - 将有效数字按照e分割，去检测左右两边，左边可以为整数或者小数，右侧必须为整数

```cpp
class Solution {
public:

    bool pureNumber(string s) {
        bool valid = true;
        for(auto c : s) {
            valid = valid && ('0' <= c && c <= '9');
            // cout << c << " " << valid << endl;
        }
        if(!valid) {
            return false;
        }
        return true;
    }
    bool isInterger(string s) {
        bool hasDot = (s.find(".") != string::npos);
        bool hasE = (s.find("E") != string::npos) || (s.find("e") != string::npos);
        bool res = true;

        bool valid = true;
        bool hasNum = false;
        for(auto c : s) {
            valid = valid && (('.' == c) || ('0' <= c && c <= '9') || ('e' == c) || ('E' == c) || ('-' == c) || ('+' == c));
            hasNum = (hasNum || ('0' <= c && c <= '9'));
            // cout << c << " " << hasNum << endl;
        }
        if((!valid) || (!hasNum)) {
            return false;
        }

        // interger
        if((!hasDot) && (!hasE)) {
            if(s.substr(1).find_first_of("+-") != string::npos) {
                return false;
            }
            return true;
        }
        return false;
    }

    bool isNumber(string s) {
        bool hasDot = (s.find(".") != string::npos);
        bool hasE = (s.find("E") != string::npos) || (s.find("e") != string::npos);
        bool res = true;

        bool valid = true;
        for(auto c : s) {
            valid = valid && (('.' == c) || ('0' <= c && c <= '9') || ('e' == c) || ('E' == c) || ('-' == c) || ('+' == c));
            // cout << c << " " << valid << endl;
        }
        if(!valid) {
            return false;
        }

        // interger
        if((!hasDot) && (!hasE)) {
            return isInterger(s);
        }

        auto isDecimal = [&](string s) {
            // split with dot
            // left half can be an integer or null string
            // right half must be pure number
            size_t pivot = s.find_first_of('.');
            string left = s.substr(0, pivot);
            string right = s.substr(1 + pivot);
            if(left.size() > 0 ) {
                if('+' == left[0] || '-' == left[0]) {
                    left = left.substr(1);
                }
            }
            if(((left == "") || isInterger(left)) && pureNumber(right) && \
             ((left.size() != 0) || (right.size() != 0))) {
                return true;
            }
            return false;
        };

        // decimal
        if((!hasE) && hasDot) {
            return isDecimal(s);
        }

        // valid num
        // split with dot
        // left half can be an integer or null string
        // right half must be pure number
        size_t pivot = s.find_first_of('e');
        if(pivot == string::npos) {
            pivot = s.find_first_of('E');
        }
        
        string left = s.substr(0, pivot);
        string right = s.substr(1 + pivot);

        if((left.size() > 0 && right.size() > 0) && (isDecimal(left) || isInterger(left)) && isInterger(right)) {
            return true;
        }
        return false;
    }
};
```
