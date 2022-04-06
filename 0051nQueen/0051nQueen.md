## 0051nQueen n皇后

### 1 题目
[https://leetcode-cn.com/problems/n-queens/](https://leetcode-cn.com/problems/n-queens/)

### 2 解题思路
- 1 回溯，每一层尝试一个格子，然后用一下三个变量存储设计到的列还有两个斜线的禁区
  - vector<bool> forbiddenJ(n, false);
  - vector<bool> forbiddenIPlusJ(2 * n, false);
  - vector<bool> forbiddenISubJ(2 * n, false);

```cpp
class Solution {
public:
    int n = -1;
    vector<vector<string>> solveNQueens(int n) {
        this->n = n;

        vector<string> board(n, string(n, '.'));
        vector<bool> forbiddenJ(n, false);
        vector<bool> forbiddenIPlusJ(2 * n, false);
        vector<bool> forbiddenISubJ(2 * n, false);
        vector<vector<string>> res;
        getRes(res, board, 0, forbiddenJ, forbiddenIPlusJ, forbiddenISubJ);
        return res;

    }

    void getRes(
        vector<vector<string>>& res, 
        vector<string>& board, 
        int level, 
        vector<bool>& forbiddenJ, 
        vector<bool>& forbiddenIPlusJ,
        vector<bool>& forbiddenISubJ
    ) {
        if(level == n) {
            res.push_back(board);
            return ;
        }
        for(int j = 0; j < n; ++j) {
            if(forbiddenJ[j] || forbiddenIPlusJ[level + j] || forbiddenISubJ[n + level - j]) {
                continue;
            }

            // put to board[level][i]
            board[level][j] = 'Q';
            bool tmp1 = forbiddenJ[j];
            bool tmp2 = forbiddenIPlusJ[level + j];
            bool tmp3 = forbiddenISubJ[n + level - j];
            
            forbiddenJ[j] = true;
            forbiddenIPlusJ[level + j] = true;
            forbiddenISubJ[n + level - j] = true;
            getRes(res, board, level + 1, forbiddenJ, forbiddenIPlusJ, forbiddenISubJ);
            board[level][j] = '.';
            forbiddenJ[j] = tmp1;
            forbiddenIPlusJ[level + j] = tmp2;
            forbiddenISubJ[n + level - j] = tmp3;
        }
    }

};

```