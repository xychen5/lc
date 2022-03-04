## 0514wayOfFreedom 自由之路

### 1 题目
[https://leetcode-cn.com/problems/freedom-trail/](https://leetcode-cn.com/problems/freedom-trail/)

### 2 解题思路
- 1 首先考虑到，key中的每一个字符，环的所有同种字符的所有位置都是遍历的可能
  - 1.1 于是使用dfs去尝试对于key的一个字符的每个位置即可，然后讲每个位置得到的结果比较取一个最小值
  - 1.2 1.1中提到的算法肯定是有问题的，比如key： abc， 然后ring: aaabbbccc
    - 会出现哪种情况呢？ ring中a的三个位置都会搜索，然后对于剩下的key和ring bc以及bbbccc会由于a有三个位置而搜索了三遍，所以需要记忆化搜索
  - 1.3 使用memo[i][j]记录： key[i:]和ring[j:]对应的最小步数即可
- 2 经过1的思考，也较为容易知道，本题目，动态规划也能做
- 3 **写代码的教训，由于我将dfsmemo写好，然后调用dfs的地方也改了，但是依然超时？**
  - 3.1 **因为dfsmemo递归调用不是自身，而是dfs函数，所以务必及时清理不需要的代码**
```cpp
class Solution {
public:

    int ringLen = -1;
    int keyLen = -1;
    int findRotateSteps(string ring, string key) {
        unordered_map<char, vector<int>> ringMap;
        ringLen = ring.length();
        keyLen = key.length();
        int pos = 0;
        for(auto& c : ring) {
            if(0 == ringMap.count(c)) {
                vector<int> tmp = {pos};
                ringMap[c] = tmp;         
            } else {
                ringMap[c].push_back(pos);
            }
            ++pos;
        }
        vector<vector<int>> memo(keyLen, vector<int>(ringLen, INT_MAX));
        return dfsMemo(0, 0, ringMap, key, memo);
    }

    // no memo dfs, too slow
    int dfs(int tar, int markPos, unordered_map<char, vector<int>>& ringMap, string& key) {
        if(tar == key.length()) {
            return 0;
        }

        int minStep = INT_MAX;
        // for cur key char, try ervery possible way on the ring
        for(auto tarPos : ringMap[key[tar]]) {
            int curStep = minDis(tarPos, markPos); // rotate
            curStep += 1; // write

            minStep = min(
                minStep,
                dfs(tar + 1, tarPos, ringMap, key) + curStep
            );
        }
        return minStep;
    }

    // memo version
    int dfsMemo(int tar, int markPos, unordered_map<char, vector<int>>& ringMap, string& key,
    vector<vector<int>>& memo) {
        if(tar == key.length()) {
            return 0;
        }

        if(INT_MAX != memo[tar][markPos]) {
            return memo[tar][markPos];
        }

        // for cur key char, try ervery possible way on the ring
        for(auto tarPos : ringMap[key[tar]]) {
            int curStep = minDis(tarPos, markPos); // rotate
            curStep += 1; // write
            memo[tar][markPos] = min(
                memo[tar][markPos],
                dfsMemo(tar + 1, tarPos, ringMap, key, memo) + curStep
            );
        }
        // cout << "memo ing: " << tar << ", " << markPos << ": " << memo[tar][markPos] << endl;
        return memo[tar][markPos];
    }

    int minDis(int tarPos, int markPos) {
        int gt = max(tarPos, markPos);
        int lt = min(tarPos, markPos);
        return min(gt - lt, lt + ringLen - gt);
    }
};
```