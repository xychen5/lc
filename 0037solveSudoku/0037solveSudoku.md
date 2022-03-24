## 0037solveSudoku 解数独

### 1 题目
[https://leetcode-cn.com/problems/sudoku-solver/](https://leetcode-cn.com/problems/sudoku-solver/)

### 2 解题思路
- 1 解题思路：
  - dfs: 首先两次循环，对于每一个空格，找可能的候选者，然后dfs遍历候选者
  - 优化第一个方案： 比如01,02两个位置都是空格，那么我们挑选候选者，会将第0行搜索两次，重复计算了，于是使用row[i][j]记录第i行数字j是否可用，用col[i][j]记录第i列数字j是否可用，用grid[i][j]记录第i个九宫格数字j是否可用


```cpp
class Solution {
public:
    int n = -1;
    int blankCnt = 0;

    int gIdx(int i, int j) { return i / 3 * 3 + j / 3;};
    void solveSudoku(vector<vector<char> > &board) {
        n = board.size();
        vector<vector<unordered_set<char>>> spaces(n, vector<unordered_set<char>>(n));
        vector<vector<bool>> flags(n, vector<bool>(n, false));

        vector<vector<bool>> rowState(n, vector<bool>(n, true));
        vector<vector<bool>> colState(n, vector<bool>(n, true));
        vector<vector<bool>> gridState(n, vector<bool>(n, true));
        
        for(int i = 0; i < n; ++i) {
            for(int j = 0; j < n; ++j) {
                if('.' == board[i][j]) {
                    ++blankCnt;
                    flags[i][j] = true;
                } else {
                    rowState[i][board[i][j] - '1'] = false;
                    colState[j][board[i][j] - '1'] = false;
                    gridState[gIdx(i, j)][board[i][j] - '1'] = false;
                }
            }
        }
        

        dfs2(board, rowState, colState, gridState);
        
    }
    
    bool dfs2(
        vector<vector<char>>& board,
        vector<vector<bool>>& rowState,
        vector<vector<bool>>& colState,
        vector<vector<bool>>& gridState
    ) {
        if(blankCnt == 0) {
            return true;
        }
        for(int i = 0; i < n; ++i) {
            for(int j = 0; j < n; ++j) {
                if(board[i][j] == '.') {
                    // try to fill
                    for(int tar = 1; tar <= n; ++tar) {
                        if(rowState[i][tar - 1] && \
                            colState[j][tar - 1] && \
                            gridState[gIdx(i, j)][tar - 1]
                        ) {
                            // cout << "try i/j : " << i << "/" << j << " " << tar << endl;
                            board[i][j] = static_cast<char>(tar + '0');
                            // cout << "board[i][j] is " << board[i][j] << endl;
                            blankCnt --;
                            // update state
                            rowState[i][board[i][j] - '1'] = false;
                            colState[j][board[i][j] - '1'] = false;
                            gridState[gIdx(i, j)][board[i][j] - '1'] = false;
                            // cout << "updated!" << endl;


                            if(!dfs2(board, rowState, colState, gridState)) {
                                // backTrack
                                rowState[i][board[i][j] - '1'] = true;
                                colState[j][board[i][j] - '1'] = true;
                                gridState[gIdx(i, j)][board[i][j] - '1'] = true;
                                board[i][j] = '.';
                                ++blankCnt;
                            } else {
                                return true;
                            }
                        }
                    }
                    if(blankCnt != 0) {
                        return false;
                    }
                }
            }
        }
        return true;
    }
    
    void getCandidates(
        vector<vector<char>>& board,
        unordered_set<char>& can,
        int i, int j
    ) {
        int gx = i / 3;
        int gy = j / 3;
        // remove by grid
        for(int gi = gx * 3; gi < gx * 3 + 3; ++ gi) {
            for(int gj = gy * 3; gj < gy * 3 + 3; ++gj) {
                if('.' != board[gi][gj]) {
                    can.erase(board[gi][gj]);
                }
            }
        }

        // remove by x or y
        for(int x = 0; x < 9; ++x) {
            if('.' != board[x][j] && x != i) {
                can.erase(board[x][j]);
            }
        }

        for(int y = 0; y < 9; ++y) {
            if('.' != board[i][y] && y != j) {
                can.erase(board[i][y]);
            }
        }
    }

};
```