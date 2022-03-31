## 0564nearestPalindromic 最近最小回文数

### 1 题目
[https://leetcode-cn.com/problems/find-the-closest-palindrome/](https://leetcode-cn.com/problems/find-the-closest-palindrome/)

### 2 解题思路
- 1 解题思路： 用127953，12799, 99801发现改题目的规律，同时处理特殊情况： 1000， 100,10,9这种数据

```cpp
class Solution {
public:
    string nearestPalindromic(string n) {
        long long  len = n.size();
        long long  src = stol(n);

        // n is odd
        if(0 != len % 2) {
            long long  leftHalf = stol(n.substr(0, len / 2 + 1));
            if(len == 1) {
                if(leftHalf < 0) {
                    return "0";
                } else {
                    return to_string(leftHalf - 1);
                }
            }

            string tmp1 = to_string(leftHalf + 1);
            string cand1 = tmp1;
            reverse(tmp1.begin(), tmp1.end());
            if(tmp1.size() > len / 2 + 1) {
                cand1 += tmp1.substr(2);
            } else {
                cand1 += tmp1.substr(1);
            }
            

            string tmp2 = to_string(leftHalf - 1);
            string cand2 = tmp2;
            reverse(tmp2.begin(), tmp2.end());
            if(len/2 + 1 != tmp2.size()) {
                cand2 += tmp2;
            } else {
                cand2 += tmp2.substr(1); 
            }
            

            string tmp3 = to_string(leftHalf);
            string cand3 = tmp3;
            reverse(tmp3.begin(), tmp3.end());
            cand3 += tmp3.substr(1);

            long long cand1Int = stol(cand1);
            long long cand2Int = stol(cand2);
            long long cand3Int = stol(cand3);
 
            // cand2 < cand3 < cand1
            if(cand3Int != src) {
                if(abs(src - cand1Int) <= abs(src - cand2Int)) {
                    if(abs(src - cand1Int) < abs(src - cand3Int)) {
                        return cand1;
                    } else {
                        return cand3;
                    }
                } else {
                    if(abs(src - cand3Int) < abs(src - cand2Int)) {
                        return cand3;
                    } else {
                        return cand2;
                    }
                }
            } else {
                if(abs(src - cand1Int) < abs(src - cand2Int)) {
                    return cand1;
                } else {
                    return cand2;
                }
            }
            
            
        } else {
            long long  leftHalf = stol(n.substr(0, len / 2));

            string tmp1 = to_string(leftHalf + 1);
            string cand1 = tmp1;
            reverse(tmp1.begin(), tmp1.end());
            if(tmp1.size() > len / 2) {
                cand1 += tmp1.substr(1);
            } else {
                cand1 += tmp1;
            }

            string tmp2 = to_string(leftHalf - 1);
            string cand2 = tmp2;
            // cout << "1 cand2: " << cand2 << endl;
            reverse(tmp2.begin(), tmp2.end());
            if("0" == tmp2) {
                cand2 = "9";
            } else {
                if(len/2 != tmp2.size()) {
                    string t(len/2, '9');
                    cand2 += t;
                } else {
                    cand2 += tmp2;
                }   
            }

            string tmp3 = to_string(leftHalf);
            string cand3 = tmp3;
            reverse(tmp3.begin(), tmp3.end());
            cand3 += tmp3;

            long long cand1Int = stol(cand1);
            long long cand2Int = stol(cand2);
            long long cand3Int = stol(cand3);
 
            // cand2 < cand3 < cand1
            if(cand3Int != src) {
                if(abs(src - cand1Int) <= abs(src - cand2Int)) {
                    if(abs(src - cand1Int) < abs(src - cand3Int)) {
                        return cand1;
                    } else {
                        return cand3;
                    }
                } else {
                    if(abs(src - cand3Int) < abs(src - cand2Int)) {
                        return cand3;
                    } else {
                        return cand2;
                    }
                }
            } else {
                if(abs(src - cand1Int) < abs(src - cand2Int)) {
                    return cand1;
                } else {
                    return cand2;
                }
            }
        }
    }
};
```