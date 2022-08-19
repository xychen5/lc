## 0927threeEqualParts 三等分

### 1 题目
[https://leetcode.cn/problems/three-equal-parts/](https://leetcode.cn/problems/three-equal-parts/)

### 2 解题思路
- 1 解题思路:
  - 首先按照1的个数三等分，然后看最后的一份的尾部0有多少，分别检测前两段是否有足够的尾部0，然后检测1的部分的序列是否相等即可


```cpp
class Solution {
public:
    vector<int> threeEqualParts(vector<int>& arr) {
        int n = arr.size();
        int cnt1 = 0;
        for(int i = 0; i < n; ++i) {
            if(1 == arr[i]) {
                cnt1 += 1;
            }
        }

        if(0 != cnt1 % 3) {
            return {-1, -1};
        }

        if(cnt1 == 0) {
            return {0, 2};
        }

        int per1 = cnt1 / 3;

        int ed1 = -1;
        int st1 = -1;
        int ed2 = -1;
        int st2 = -1;
        int ed3 = -1;
        int st3 = -1;
        bool m1 = false, m2 = false, m3 = false;
        int cnt = 0;
        for (int i = 0; i < n; ++i) {
            if(1 == arr[i]) {
                if(cnt == 0) {
                    st1 = i;
                } else if(cnt - per1 == 0) {
                    st2 = i;
                } else if(cnt - 2 * per1 == 0) {
                    st3 = i;
                }
                cnt += 1;
            }

            // cout << "i:/arr[i]: " << arr[i] << " " << cnt << endl;

            if(cnt%per1 == 0) {
                if(!m1 && cnt / per1 == 1) {
                    ed1 = i;
                    m1 = true;
                }
                if(!m2 && cnt / per1 == 2) {
                    ed2 = i;
                    m2 = true;
                }
                if(!m3 && cnt / per1 == 3) {
                    ed3 = i;
                    m3 = true;
                }
            }
        }

        int tailZeroCnt = n - ed3 - 1;
        // cout << "need tail: " << tailZeroCnt << endl;
        // cout << "st123 : " << st1 << " " << st2 << " " << st3 << endl;
        // cout << "ed123 : " << ed1 << " " << ed2 << " " << ed3 << endl;
        
        // check if ed1 and ed2 has enough 0 tailed
        auto foundTail0 = [&arr](int st) {
            int cnt0 = 0;
            for(int i = st; i < arr.size(); ++i) {
                if(0 == arr[i]) {
                    cnt0++;
                } else {
                    break;
                }
            }
            // cout << "find zero: " << cnt0 << endl;
            return cnt0;
        };

        auto cmpVec = [&arr](int st1, int ed1, int st2, int ed2) {
            int delta = st2 - st1;
            for(int i = st1; i <= ed1; ++i) {
                if(arr[i] != arr[i + delta]) {
                    return false;
                }
            }
            return true;
        };

        int res1 = -1, res2 = -1;
        if(foundTail0(ed1 + 1) >= tailZeroCnt && foundTail0(ed2 + 1) >= tailZeroCnt && 
            cmpVec(st1, ed1, st2, ed2) && cmpVec(st3, ed3, st2, ed2)) {
            res1 = ed1 + tailZeroCnt;
            res2 = ed2 + tailZeroCnt + 1;
        } else {
            return {-1, -1};
        }
        return {res1, res2};
    }
}
```