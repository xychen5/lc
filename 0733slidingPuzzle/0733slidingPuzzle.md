## 0733slidingPuzzle 滑动到123450谜题

### 1 题目
[https://leetcode.cn/problems/sliding-puzzle/](https://leetcode.cn/problems/sliding-puzzle/)

### 2 解题思路
- 1 解题思路：
  - 1.1 为何选用bfs，因为要获得最终的移动步数，那么bfs的层数就是最终的答案
  - 1.2 节点就是当前的棋盘，后继节点为移动后改变的棋盘
  - 1.3 使用位运算加速


```cpp
class Solution {
public:
    constexpr static int tar = ((1<<3) | (2<<6) | (3<<9) | (4<<12) | (5<<15));
    unordered_set<int> vis;

    int dx[4] = {1, 0, -1, 0};
    int dy[4] = {0, -1, 0, 1};
    

    bool isTar(vector<vector<int>>& board) {
        return tar == toInt(board);
    }
    int toInt(vector<vector<int>>& board) {
        return board[0][0]<<3 | board[0][1]<<6 | board[0][2]<<9 | board[1][0]<<12 | board[1][1]<<15;
    }

    pair<int, int> getPos(vector<vector<int>>& board) {
        for(int i = 0; i < 2; ++i) {
            for(int j = 0; j < 3; ++j) {
                if(board[i][j] == 0) {
                    return {i, j};
                }
            }
        }
        return {-1, -1};
    }

    int slidingPuzzle(vector<vector<int>>& board) {
        int res = 0;
        if(toInt(board) == tar) {
            return 0;
        }
    
        res = bfsCheck(board);
        return res;
    }

    void swap(int& a, int& b) {
        int tmp = a;
        a = b;
        b = tmp;
    }

    int bfsCheck(vector<vector<int>>& oriBoard) {
        queue<vector<vector<int>>> curLevel;
        curLevel.push(oriBoard);
        vis.insert(toInt(oriBoard));

        int depth = 1;
        while(!curLevel.empty()) {
            int curSize = curLevel.size();
            // pop all curLevel and do next level
            while(curSize-- > 0) {
                auto board = curLevel.front();
                curLevel.pop();

                auto coord = getPos(board);
                int x = coord.first;
                int y = coord.second;
            
                for(int mv = 0; mv < 4; ++mv) {
                    int nextX = x + dx[mv];
                    int nextY = y + dy[mv];
                    if(0 <= nextX && nextX < 2 && 0 <= nextY && nextY < 3) {
                        swap(board[nextX][nextY], board[x][y]);
                        // cout << "trying : " << x << ", " << y << " to " << nextX << ", " << nextY << " withd d = " << depth <<endl;
                        // print(board);
                        
                        int intBoard = toInt(board);

                        if(0 == vis.count(intBoard)) {
                            curLevel.push(board);
                            if(isTar(board)) {
                                // cout << "final tar: " << endl;
                                // print(board);
                                return depth;
                            }
                            vis.insert(intBoard);
                        }
                        swap(board[x][y], board[nextX][nextY]);
                    }
                }
            }
            ++depth;
        }
        return -1;

    }

    void print(vector<vector<int>>& board) {
        for(int i = 0; i < 2; ++i) {
            for(int j = 0; j < 3; ++j) {
                cout << board[i][j] << " ";
            }cout << " | ";
        }
        cout << "----------\n";
    }

};

```