## 0710randomNumInBlacklist 黑名单中的随机数

### 1 题目
[https://leetcode-cn.com/problems/random-pick-with-blacklist/](https://leetcode-cn.com/problems/random-pick-with-blacklist/)

### 2 解题思路
- 1 参考官解

```cpp
class Solution {
public:
    unordered_map<int, int> bTow;
    int allLen = -1;
    int blackLen = -1;
    Solution(int n, vector<int>& blacklist) {
        /**
        白名单中数的个数为 N - len(B)，那么可以直接在 [0, N - len(B)) 中随机生成整数。我们把所有小于 N - len(B) 
        且在黑名单中数一一映射到大于等于 N - len(B) 且出现在白名单中的数。这样一来，如果随机生成的整数出现在黑名单中，
        我们就返回它唯一对应的那个出现在白名单中的数即可。

        例如当 N = 6，B = [0, 2, 3] 时，我们在 [0, 3) 中随机生成整数，并将 2 映射到 4，3 映射到 5，这样随机生成的整数就是 [0, 1, 4, 5] 中的一个。

        算法

        我们将黑名单分成两部分，第一部分 X 的数都小于 N - len(B)，需要进行映射；第二部分 Y 的数都大于等于 N - len(B)，
        这些数不需要进行映射，因为并不会随机到它们。
        我们先用 Y 构造出 W，表示大于等于 N - len(B) 且在白名单中的数，X 和 W 的长度一定是相等的。随后遍历 X 和 W，
        构造一个映射表（HashMap）M，将 X 和 W 中的数构造一一映射。
        在 [0, N - len(B)) 中随机生成整数 a 时，如果 a 出现在 M 中，则将它的映射返回，否则直接返回 a。
        */
        allLen = n;
        blackLen = blacklist.size();

        int boarder = n - blacklist.size();
        unordered_set<int> whiteInRight;
        for(int i = n - 1; i >= boarder; --i) {
            whiteInRight.insert(i);
        }
        for(auto b : blacklist) {
            whiteInRight.erase(b);
        }
        
        auto st = whiteInRight.begin();
        for(auto b : blacklist) {
            if(b < boarder) {
                bTow[b] = *(st++);
            }
        }
    }
    
    int pick() {
        int tar = rand() % (allLen - blackLen);
        return bTow.count(tar) == 0 ? tar : bTow[tar];
    }

};
```