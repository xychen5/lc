## 1036escapeHugeMaze 逃离巨大迷宫

### 1 题目
[https://leetcode.cn/problems/escape-a-large-maze/submissions/](https://leetcode.cn/problems/escape-a-large-maze/submissions/)

### 2 解题思路
- 1 解题思路：
  - 1.1 dfs，不能暴力dfs
  - 1.2 如何尽早退出?
    - 1.2.1 200个墙最多围住的方块数字不超过20000，所以dfs走的步数超过2w，那么出发点肯定没有被围住
    - 1.2.2 要是终点被围住了呢？也就是把src和target换个方向再dfs一遍即可
  - 1.3 返回为true的条件：
    - 大于20000次的dfs步数就说明成了
    - 遍历到了终点
    - 那么失败呢？也就是没到20000次，发现没有别的位置可以遍历，并且没有遍历到终点，则说明失败

```cpp
class Solution {
public:
    unordered_map<int, unordered_set<int>> block2;

    unordered_map<int, unordered_set<int>> mark;

    int tryCnt = 0;
    int dx[4] = {1, 0, -1, 0};
    int dy[4] = {0, 1, 0, -1};

    // check blocked
    bool isBlocked(vector<int>& pos) {
        if(0 != block2.count(pos[0])) {
            return 0 != block2[pos[0]].count(pos[1]);
        }
        return false;
    }

    bool isTraveled(vector<int>& pos) {
        if(0 != mark.count(pos[0])) {
            return 0 != mark[pos[0]].count(pos[1]);
        }
        return false;
    }

    bool isEscapePossible(vector<vector<int>>& blocked, vector<int>& source, vector<int>& target) {
        // attention that blocked.length <= 200
        // so, when the source is stuck, the most squares we can dfs is: 200 * 200 = 40000
        for(auto& v : blocked) {
            if(0 == block2.count(v[0])) {
                block2[v[0]] = {v[1]};
            } else {
                block2[v[0]].insert(v[1]);
            }
        }

        // do dfs
        auto bool1 = dfs(source, target) || tryCnt > 200'00;
        // auto bool1 = true;
        mark.clear();
        tryCnt = 0;
        auto bool2 = dfs(target, source) || tryCnt > 200'00;
        return bool1 && bool2; 
    }

    bool dfs(vector<int>& src, vector<int>& tar) {
        if(tar == src || tryCnt > 200'00) {
            return true;
        }
        if(0 == mark.count(src[0])) {
            mark[src[0]] = {src[1]};
        } else {
            mark[src[0]].insert(src[1]);
        }

        


        vector<int> nextSrc(2);
        bool res = false;
        for(int mv = 0; mv < 4; ++mv) {
            nextSrc[0] = src[0] + dx[mv];
            nextSrc[1] = src[1] + dy[mv];
            // cout << "to next try: with mv: " << nextSrc[0] << " " << nextSrc[1] << "with mv: " << mv << endl;
            if(nextSrc[0] >= 0 && nextSrc[0] < 1000'000 && \
            nextSrc[1] >= 0 && nextSrc[1] < 1000'000 && \
            !isBlocked(nextSrc) && \
            !isTraveled(nextSrc)) {
                
                ++tryCnt;
                
                res = res || dfs(nextSrc, tar);
            }
        }
        // cout << "return up level!" << endl;

        return res;
    }


};

```