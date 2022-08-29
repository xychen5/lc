## 0000_interview_gesturePassword 手势密码的个数

### 1 题目
下面是3个输入数据，每一个数据是3x3的字符，.代表可以用，x代表不能用，问能形成多少个图案？（可以从0号位置随意移动到另一个位置）
/**
 3
 ...
 XXX
 XXX
 ...
 XXX
 X.X
 .X.
 X.X
 .X.

 */

### 2 解题思路
- 1 解题思路
  - 搞清楚了，构成图案的基础边一共就28个，所以我们用一个int
  - 也就是状态压缩，来代表一个具体的图案
  - 然后对于一个board，从所有可能的地方dfs，即可
- 2 难的是形成那个状态压缩的表：
  - edgeMap[a][b]代表的是： 从a点到b点，能够cover的那些基础边
```cpp
// 一段的平行线 24
edgeMap[0][1] = (1 << 0 );edgeMap[1][0] = (1 << 0);
edgeMap[1][2] = (1 << 1 );edgeMap[2][1] = (1 << 1);
edgeMap[3][4] = (1 << 2 );edgeMap[4][3] = (1 << 2);
edgeMap[4][5] = (1 << 3 );edgeMap[5][4] = (1 << 3);
edgeMap[6][7] = (1 << 4 );edgeMap[7][6] = (1 << 4);
edgeMap[7][8] = (1 << 5 );edgeMap[8][7] = (1 << 5);
edgeMap[0][3] = (1 << 7 );edgeMap[3][0] = (1 << 7);
edgeMap[3][6] = (1 << 8 );edgeMap[6][3] = (1 << 8);
edgeMap[1][4] = (1 << 9 );edgeMap[4][1] = (1 << 9);
edgeMap[4][7] = (1 << 10);edgeMap[7][4] = (1 << 10);
edgeMap[2][5] = (1 << 11);edgeMap[5][2] = (1 << 11);
edgeMap[5][8] = (1 << 12);edgeMap[8][5] = (1 << 12);

// edgelen == 1 lean 一段的斜线 16
edgeMap[0][4] = (1 << 18);edgeMap[4][0] = (1 << 18);
edgeMap[4][8] = (1 << 19);edgeMap[8][4] = (1 << 19);
edgeMap[2][4] = (1 << 20);edgeMap[4][2] = (1 << 20);
edgeMap[4][6] = (1 << 21);edgeMap[6][4] = (1 << 21);
edgeMap[1][3] = (1 << 22);edgeMap[3][1] = (1 << 22);
edgeMap[1][5] = (1 << 23);edgeMap[5][1] = (1 << 23);
edgeMap[3][7] = (1 << 24);edgeMap[7][3] = (1 << 24);
edgeMap[5][7] = (1 << 25);edgeMap[7][5] = (1 << 25);

// edgelen = 1_2 lean 根号5的斜线 16
edgeMap[3][2] = (1 << 13);edgeMap[2][3] = (1 << 13);
edgeMap[3][8] = (1 << 14);edgeMap[8][3] = (1 << 14);
edgeMap[1][6] = (1 << 15);edgeMap[6][1] = (1 << 15);
edgeMap[1][8] = (1 << 16);edgeMap[8][1] = (1 << 16);
edgeMap[5][0] = (1 << 17);edgeMap[0][5] = (1 << 17);
edgeMap[5][6] = (1 << 26);edgeMap[6][5] = (1 << 26);
edgeMap[7][0] = (1 << 27);edgeMap[0][7] = (1 << 27);
edgeMap[7][2] = (1 << 28);edgeMap[2][7] = (1 << 28);

// len = 2 lean 2段的斜线 4
edgeMap[0][8] = edgeMap[0][4] + edgeMap[4][8];
edgeMap[2][6] = edgeMap[2][4] + edgeMap[4][6];
edgeMap[8][0] = edgeMap[0][4] + edgeMap[4][8];
edgeMap[6][2] = edgeMap[2][4] + edgeMap[4][6];

// len = 2 hori/vert 两段的直线 12
edgeMap[0][2] = edgeMap[0][1] + edgeMap[1][2];
edgeMap[3][5] = edgeMap[3][4] + edgeMap[4][5];
edgeMap[6][8] = edgeMap[6][7] + edgeMap[7][8];
edgeMap[0][6] = edgeMap[0][3] + edgeMap[3][6];
edgeMap[1][7] = edgeMap[1][4] + edgeMap[4][7];
edgeMap[2][8] = edgeMap[2][5] + edgeMap[5][8];

edgeMap[2][0] = edgeMap[0][1] + edgeMap[1][2];
edgeMap[5][3] = edgeMap[3][4] + edgeMap[4][5];
edgeMap[8][6] = edgeMap[6][7] + edgeMap[7][8];
edgeMap[6][0] = edgeMap[0][3] + edgeMap[3][6];
edgeMap[7][1] = edgeMap[1][4] + edgeMap[4][7];
edgeMap[8][2] = edgeMap[2][5] + edgeMap[5][8];
```

```cpp

#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <limits.h>
#include <numeric>
#include <list>
#include <queue>
#include <unordered_set>
#include <unordered_map>
#include <map>
#include <set>
#include <cmath>
#include <thread>
#include <mutex>
#include <pthread.h>
#include <string>
#include <sstream>
#include <strings.h>

using namespace std;

/**
 3
 ...
 XXX
 XXX
 ...
 XXX
 X.X
 .X.
 X.X
 .X.
 
 3
 22
 111
 
1
 .X.
 X.X
 .X.
 
 */

vector<vector<int>> edgeMap;

// to make sure the path not reused, we mark each edge, there are only 28's edge, so an int is enough
size_t getWays(vector<string>& board, int st, int curPath, unordered_set<int>& res, vector<bool>& pointUsed, int l){
    
    int curX = st / 3;
    int curY = st % 3;
    for(int curPoint = 0; curPoint < 9; ++curPoint) {
        // dfs
        if(pointUsed[curPoint]) {
            continue;
        }
        if(curPoint == st) {
            continue;
        }
        
        int nextX = curPoint / 3;
        int nextY = curPoint % 3;
        if(board[nextX][nextY] != 'X') {
            
            // nextstep
            int newPath = curPath | edgeMap[st][curPoint];
            int a = curPath | edgeMap[curPoint][st];

            pointUsed[curPoint] = true;
            
            res.insert(newPath);

            getWays(board, curPoint, newPath, res, pointUsed, l + 1);
            
            pointUsed[curPoint] = false;
        }
    }
    
//    cout << "allUsed!" << endl;
    
    return res.size();
        
}



int main() {
    int t;
    cin >> t;
    int n = t;
    vector<vector<string>> board(t);
    int lineCnt = 0;
    while(n > 0) {
        for(int l = 0; l < 3; ++l) {
            string tmp;
            cin >> tmp;
            board[lineCnt / 3].push_back(tmp);
            ++lineCnt;
        }
        --n;
    }

    
    edgeMap.resize(9, vector<int>(9, -1));
    // 一段的平行线 24
    edgeMap[0][1] = 1 << 0;edgeMap[1][0] = 1 << 0;
    edgeMap[1][2] = 1 << 1;edgeMap[2][1] = 1 << 1;
    edgeMap[3][4] = 1 << 2;edgeMap[4][3] = 1 << 2;
    edgeMap[4][5] = 1 << 3;edgeMap[5][4] = 1 << 3;
    edgeMap[6][7] = 1 << 4;edgeMap[7][6] = 1 << 4;
    edgeMap[7][8] = 1 << 5;edgeMap[8][7] = 1 << 5;
    edgeMap[0][3] = 1 << 7; edgeMap[3][0] = 1 << 7;
    edgeMap[3][6] = 1 << 8; edgeMap[6][3] = 1 << 8;
    edgeMap[1][4] = 1 << 9; edgeMap[4][1] = 1 << 9;
    edgeMap[4][7] = 1 << 10;edgeMap[7][4] = 1 << 10;
    edgeMap[2][5] = 1 << 11;edgeMap[5][2] = 1 << 11;
    edgeMap[5][8] = 1 << 12;edgeMap[8][5] = 1 << 12;
    
    // edgelen == 1 lean 一段的斜线 16
    edgeMap[0][4] = 1 << 18;edgeMap[4][0] = 1 << 18;
    edgeMap[4][8] = 1 << 19;edgeMap[8][4] = 1 << 19;
    edgeMap[2][4] = 1 << 20;edgeMap[4][2] = 1 << 20;
    edgeMap[4][6] = 1 << 21;edgeMap[6][4] = 1 << 21;
    edgeMap[1][3] = 1 << 22;edgeMap[3][1] = 1 << 22;
    edgeMap[1][5] = 1 << 23;edgeMap[5][1] = 1 << 23;
    edgeMap[3][7] = 1 << 24;edgeMap[7][3] = 1 << 24;
    edgeMap[5][7] = 1 << 25;edgeMap[7][5] = 1 << 25;

    // edgelen = 1_2 lean 根号5的斜线 16
    edgeMap[3][2] = 1 << 13;edgeMap[2][3] = 1 << 13;
    edgeMap[3][8] = 1 << 14;edgeMap[8][3] = 1 << 14;
    edgeMap[1][6] = 1 << 15;edgeMap[6][1] = 1 << 15;
    edgeMap[1][8] = 1 << 16;edgeMap[8][1] = 1 << 16;
    edgeMap[5][0] = 1 << 17;edgeMap[0][5] = 1 << 17;
    edgeMap[5][6] = 1 << 26;edgeMap[6][5] = 1 << 26;
    edgeMap[7][0] = 1 << 27;edgeMap[0][7] = 1 << 27;
    edgeMap[7][2] = 1 << 28;edgeMap[2][7] = 1 << 28;
    
    // len = 2 lean 2段的斜线 4
    edgeMap[0][8] = edgeMap[0][4] + edgeMap[4][8];
    edgeMap[2][6] = edgeMap[2][4] + edgeMap[4][6];
    edgeMap[8][0] = edgeMap[0][4] + edgeMap[4][8];
    edgeMap[6][2] = edgeMap[2][4] + edgeMap[4][6];

    // len = 2 hori/vert 两段的直线 12
    edgeMap[0][2] = edgeMap[0][1] + edgeMap[1][2];
    edgeMap[3][5] = edgeMap[3][4] + edgeMap[4][5];
    edgeMap[6][8] = edgeMap[6][7] + edgeMap[7][8];
    edgeMap[0][6] = edgeMap[0][3] + edgeMap[3][6];
    edgeMap[1][7] = edgeMap[1][4] + edgeMap[4][7];
    edgeMap[2][8] = edgeMap[2][5] + edgeMap[5][8];

    edgeMap[2][0] = edgeMap[0][1] + edgeMap[1][2];
    edgeMap[5][3] = edgeMap[3][4] + edgeMap[4][5];
    edgeMap[8][6] = edgeMap[6][7] + edgeMap[7][8];
    edgeMap[6][0] = edgeMap[0][3] + edgeMap[3][6];
    edgeMap[7][1] = edgeMap[1][4] + edgeMap[4][7];
    edgeMap[8][2] = edgeMap[2][5] + edgeMap[5][8];
    
//    for(int i = 0; i < 9; ++i) {
//        for(int j = 0; j < 9; ++j) {
//            if(edgeMap[i][j] != edgeMap2[i][j] && i != j) {
//                cout << i << " " << j << " -> " << edgeMap[i][j] << " | " << edgeMap2[i][j] << endl;
//            }
//        }
//    }
    
    for(auto& b : board) {
        int curPath = 0;
        unordered_set<int> res;
        vector<bool> pointUsed(9, false);
        int ways = 0;

        // find each able st and do getWays
        for(int i = 0; i < 3; ++i) {
            for(int j = 0; j < 3; ++j) {
                int l = 0;
                if(b[i][j] != 'X') {
                    pointUsed[i*3 + j] = true;
                    
                    auto cnt = getWays(b, i*3 + j, curPath, res, pointUsed, l);
                    
                    pointUsed[i*3 + j] = false;
                }
            }
        }
        cout << res.size() << endl;
    }
    
}
```
