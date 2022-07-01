## 1240tilingRect 铺瓷砖

### 1 题目
[https://leetcode.cn/problems/tiling-a-rectangle-with-the-fewest-squares/](https://leetcode.cn/problems/tiling-a-rectangle-with-the-fewest-squares/)

### 2 解题思路
- 1 解题思路：
  - 每一次从左上角，找出来目前能够铺的最大瓷砖，然后对于该位置，从最大瓷砖开始铺，铺好了进入下一层回溯，当下一层回溯完毕，对于当前位置，我们不再使用最大瓷砖，而使用长度小1的瓷砖，直到长度减小到1，对于每个起始位置，我们都从最大长度开始回溯，然后长度递减去回溯
  - 剪枝：当当前贴的瓷砖个数已经超过目前的值，我们直接return； 为什么要这个剪枝？比如一个10X10的瓷砖，一开始第一次就能铺满，那么等回溯到最后面都是1x1的瓷砖在贴，很慢很慢，那么就可以用这个已经得到的结果1，去提前返回，加速了回溯过程；



```cpp
class Solution {
public:
    vector<vector<bool>> board; // top left is 0, 0
    int n, m; // n colums, m rows

    int finRes = INT_MAX;

    // start from left top
    pair<int, pair<int, int>> findPos(vector<vector<bool>>& board) {
        int x, y;
        for(int i = 0; i < m; ++i) {
            for(int j = 0; j < n; ++j) {
                if(!board[i][j]) {
                    x = i; y = j;
                    // find len:
                    int u = x;
                    while(u < m && !board[u][y]) {
                        ++u;
                    }
                    int len = u - x;

                    int v = y;
                    while(v < n && !board[x][v]) {
                        ++v;
                    }
                    len = min(len, v - y);

                    return {len, {x, y}};
                }
            }
        }

        return {-1, {-1, -1}};
    } 

    void fillSquareWith(vector<vector<bool>>& board, int x, int y, int len, bool content) {
        for(int i = x; i < x + len; ++i) {
            for(int j = y; j < y + len; ++j) {
                board[i][j] = content;
            }
        }
    }

    void backTrack(vector<vector<bool>>& board, int& leftCnt, int curRes) {
        if(finRes <= curRes) {
            return ;
        }
        if(0 == leftCnt) {
            finRes = min(finRes, curRes);
            return ;
        }
        
        // find first zero pos along the boarder, or the next 1
        auto p = findPos(board);
        int len = p.first;
        int x = p.second.first, y = p.second.second;
        // cout << "found max len: " << len << " x/y " << x << " " << y << endl;

        for(int l = len; l > 0; --l) {
            fillSquareWith(board, x, y, l, true);
            leftCnt -= l*l;
            
            // cout <<"ready to fill: x/y/l: " << x << "/" <<  y << "/" <<  l << "/" << "left: " << leftCnt << endl;
            // print(board);
            backTrack(board, leftCnt, curRes + 1);

            leftCnt += l*l;
            fillSquareWith(board, x, y, l, false);
        }
        
    }

    int tilingRectangle(int n, int m) {
        this->n = m;
        this->m = n;
        // cout << "this: " << this->n << " " << this->m << endl;
        board.resize(n, vector<bool>(m, 0));
        int leftCnt = n*m;
        int curRes = 0;
        backTrack(board, leftCnt, curRes);
        return finRes;
    }

    void print(vector<vector<bool>>& board) {
        for(auto v : board) {
            for(auto i : v) {
                cout << i << " ";
            }cout << "\n";
        }cout << "\n ---------- ";

    }
}
```
