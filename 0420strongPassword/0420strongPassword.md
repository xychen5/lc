## 0420strongPassword 强密码校验器

### 1 题目
[https://leetcode-cn.com/problems/strong-password-checker/submissions/](https://leetcode-cn.com/problems/strong-password-checker/submissions/)

### 2 解题思路
- 1 没有意义的分类讨论

```cpp
class Solution {
public:
    int strongPasswordChecker(string password) {

        bool missUpperCase = true;
        bool missLowerCase = true;
        bool missNumber = true;
        
        int n = password.size();
        for(int i = 0; i < n; ++i) {
            if(isUpperCase(password[i])) {
                missUpperCase = false; continue;
            }
            if(isLowerCase(password[i])) {
                missLowerCase = false;continue;
            }
            if(isNumber(password[i])) {
                missNumber = false;continue;
            }
        }

        // find 3 continous chars
        map<int, int, std::less<int>> con;
        for(int i = 0; i < n; ++i) {
            int st = i;
            int ed = i;
            while(password[ed] == password[st]) {
               ++ed;
            }
            i = ed - 1;
            if(ed - st >= 3) {
                con[st] = ed - st;
            }
        }

        int types = !missLowerCase + !missNumber + !missUpperCase;

        // when len [4, 5]

        int curLen = password.size();
        if(password.size() <= 5) {
            return max((int)(6 - password.size()), (int)3 - (int)types);
        } else if(password.size() <= 20) {
            // only mod
            int res = 0;
            for(auto p : con) {
                res += p.second / 3;
            }
            cout << types << endl;
            return max(res, 3 - types);
        } else {
            int insCnt = 0;
            int delCnt = 0;
            int modCnt = 0;

            int rm2 = 0;
            for(auto p : con) {
                modCnt += p.second / 3;
            }
            
            delCnt = n - 20;
            for(auto p : con) {
                if(delCnt > 0) {
                    // 如果是 k % 3 = 0 的组，那么优先删除 1 个字符，减少 1 次替换操作
                    if(p.second % 3 == 0) {
                        --delCnt; 
                        --modCnt;
                    } else if(p.second % 3 == 1) {
                        // 如果是 k % 3 = 1 的组，那么存下来备用
                        ++rm2;
                    }
                }
            }

            // 假设字符串为： aaaaBBBBCCCCdddd11112222 n = 24, rm2 = 6, delCnt = 6,
            // 于是我们优先采用删除2个字符串的方式，来减少修改操作，因为一开始我们假设全部用修改操作，那么
            // modCnt = 6, 有6个删除机会，那么分别删除aa,BB,CC，保证长度在20，然后进行3个替换，就是最优解
            int use2 = min({modCnt, rm2, delCnt / 2});
            modCnt -= use2;
            delCnt -= use2 * 2;
            
            // 同上，设置字符串为aaaaaBBBBBCCCCC1111122222 n = 25, delCnt = 5, modCnt = 5
            // 那么用掉delCnt中的3个，将aaaaa变成aa，然后再替换4次就行可以
            int use3 = min({modCnt, delCnt / 3});
            modCnt -= use3;
            delCnt -= use3 * 3;
            return (n - 20) + max(modCnt, 3 - types);
        }
        return 0;
    }

    bool isUpperCase(char a) {
        return a - 'A' >= 0 && a - 'Z' <= 0;
    }

    bool isLowerCase(char a) {
        return a - 'a' >= 0 && a - 'z' <= 0;
    }

    bool isNumber(char a) {
        return a - '0' >= 0 && a - '9' <= 0;
    }
    

};
```