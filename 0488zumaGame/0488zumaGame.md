## 0488zumaGame 祖玛游戏

### 1 题目
[https://leetcode-cn.com/problems/zuma-game/](https://leetcode-cn.com/problems/zuma-game/)

### 2 解题思路
- 1 对于hand中，每次挑选一个去填补到board中，然后消除board中的球，接着用剩下的hand再选择一个，到board里中去消除，dfs去遍历即可
- 2 使用记忆化搜索 memo[board + " " + hand]记录了对应的board和hand的结果，为何" "是必须的？
  - 2.1 考虑以下例子：
  - 2.2 可以知道必须在中间的RR中先插入B，那么假设我们的第一次搜索从第一个字符G，第二个字符是B，开始，那么我们的memo中会有结果(若是不带空格)：memo[RRYGGYYRBRYYGGYRRGGBB]，这样当第一个字符变成B，我们会在memo发现一个失败的方法直接返回结果，导致改题变成没有结果，同时这个例子也解释了为何减枝的条件3需要在两个相同字符之间插入字符，如果带了空格，就能够绝对避免这个问题，因为：
  - memo[RRYGGYYRBRYYGGYRR GGB] 和 memo[RRYGGYYRBRYYGGYRR GGBB]就能够区分开
> "RRYGGYYRRYYGGYRR"<br>
> "GGBBB"

```cpp
class Solution {
public:
    int allBallsCnt = -1;
    map<string, int> memo;

    int findMinStep(string board, string hand) {
        // simulate this game
        int res = 0;
        allBallsCnt = hand.size();
        res = bfs(board, hand);
        return res == INT_MAX ? -1 : res;
    }
    int bfs(string board, string hand) {
        // space mustn't be eliminated! it's neutig!
        if(memo.find(board + " " + hand) != memo.end()) {
            return memo[board + " " + hand];
        }

        if(0 == board.size()) {
            return allBallsCnt - hand.size();
        }
        if(0 == hand.size()) {
            return INT_MAX;
        }

        int useRes = INT_MAX;
        string lastTarBallStr = "";
        for(int k = 0; k < hand.size(); ++k) {
            string nextHand = hand.substr(0, k) + hand.substr(k + 1);
            string tarBallStr = hand.substr(k, 1);

            // case1: cut the same ball
            if(tarBallStr == lastTarBallStr) {
                continue;
            }

            // use this char, find put pos
            for(int i = 0; i <= board.size(); ++i) {
                // case2: only insert at the start of str with same chars
                if(i > 0 && board[i - 1] == hand[k]) {
                    continue;
                }

                // case3: only put when cur is equal current || when cur is not equal to two continuous same chars
                if(i < board.size() && board[i] == hand[k] || \
                i > 0 && board[i] == board[i-1] && hand[k] != board[i-1]) {
                    string tmpBoard1 = board;
                    tmpBoard1.insert(i, tarBallStr);
                    // reduce repeat balls
                    reduceRepeat(tmpBoard1);

                    // put to tarBall left and right
                    int lRes = bfs(tmpBoard1, nextHand);

                    useRes = min(lRes, useRes);
                }
            }
            
            lastTarBallStr = tarBallStr;
        }
        memo[board + " " + hand] = useRes;
        return useRes;
    }

    inline void reduceRepeat(string& board) {
        int idx = 0;
        // cout << "reducing " << board << endl;
        while(board.length() > 0 && idx < board.length()) {
            int st = idx, cur = st;
            char head = board[st];
            while(++cur < board.length() && board[cur] == head) {
            }
            if(cur - st >= 3) {
                board.erase(st, cur - st);
                idx = 0;
            } else {
                idx = cur;
            }
        }
        // cout << "after redu " << board << endl;
    }

};
```