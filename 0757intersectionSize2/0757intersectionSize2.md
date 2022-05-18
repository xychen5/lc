## 0757intersectionSize2 设置交集为2

### 1 题目
[https://leetcode.cn/problems/set-intersection-size-at-least-two/](https://leetcode.cn/problems/set-intersection-size-at-least-two/)

### 2 解题思路
- 1 解题思路：
  - 1.2 考虑官方解答
  - 1.3 排序区间，首先起点升序，终点降序，弄个数组记录每个区间还有几个元素需要相交
  - 1.4 而后从后往前，从起点开始遍历2个数字，然后对于当前区间前面的每一个区间，更新他们的需要相交元素的个数，然后看当前区间贡献了几个相交元素，加起来就行

```cpp
class Solution {
public:
    int intersectionSizeTwo(vector<vector<int>>& intervals) {
        sort(intervals.begin(), intervals.end(), [](const vector<int>& a, const vector<int>& b) {
            return a[0] < b[0] || a[0] == b[0] && a[1] > b[1];
        });

        // greedy
        int res = 0;
        int n = intervals.size();
        vector<int> needIntersectNum(n, 2);

        // from back to st
        for(int i = n-1; i >= 0; --i) {
            for(int val = intervals[i][0]; val < intervals[i][0] + needIntersectNum[i]; ++val) {
                for(int t = i-1; t >= 0; --t) {
                    if(0 != needIntersectNum[t] && intervals[t][1] >= val) {
                        --needIntersectNum[t];
                    }
                }
                ++res;
            }
            // res += needIntersectNum[i];
        }

        return res;
        

        // greedy to cover and use less elements
        // init
        // vector<int> curCover = {intervals[0][0], intervals[0][1]};
        // int curCnt = 2;
        // int canUse = 0;

        // int i = 1;
        // int n = intervals.size();
        // while(i < n) {

        //     // try to cover interval[i] and not to broad the curCover
        //     // // case0: same start point
        //     // // curCover:        -
        //     // // cur interval:   ---
        //     if(intervals[i][0] < curCover[0]) {
        //         cout << " " << intervals[i][0] << "->" <<intervals[i][1] << " res: " << curCnt << " @ " << curCover[0] << "->" << curCover[1] << " | " << canUse << endl;

        //         ++i;
        //         continue;
        //     }

        //     // case1: same start point
        //     // curCover:      -----       -
        //     // cur interval:  ------- or ---
        //     if(intervals[i][0] == curCover[0]) {

        //         if(canUse == 1) {
        //             curCnt += canUse;
        //             curCover[0] = intervals[i][0] + 1;
        //             curCover[1] = intervals[i][1];
        //             canUse = 1;
        //             // cout << "set 0" << endl;
        //         }
        //                         cout << " " << intervals[i][0] << "->" <<intervals[i][1] << " res: " << curCnt << " @ " << curCover[0] << "->" << curCover[1] << " | " << canUse << endl;

        //                                     // cout << "doing: intervals[i][0] <= curCover[0]" << intervals[i][0] << "->" <<intervals[i][1] << " res: " << curCnt << " @ " << curCover[0] << "->" << curCover[1] << endl;

        //         ++i;
        //         continue;
        //     }
            
            
        //     // case2: at least 2 intesection
        //     // curCover:      -----           -----
        //     // cur interval:    --- or          --
        //     if(intervals[i][1] <= curCover[1]) {
        //         curCover[0] = intervals[i][0];
        //         curCover[1] = intervals[i][1];
        //         if(canUse == 1) {
        //             curCnt += canUse;
        //             canUse = 0;
        //         }
        //                         cout << " " << intervals[i][0] << "->" <<intervals[i][1] << " res: " << curCnt << " @ " << curCover[0] << "->" << curCover[1] << " | " << canUse << endl;


        //         ++i;
        //         continue;
        //     }
        
        //     // case3: at least 2 intersection
        //     // curCover:      -----
        //     // cur interval:     ------
        //     if(curCover[1] > intervals[i][0] && curCover[1] - intervals[i][0] >= 1) {
        //         curCover[0] = intervals[i][0];
        //         if(canUse == 1) {
        //             curCnt += canUse;
        //             canUse = 0;
        //         }
        //                         cout << " " << intervals[i][0] << "->" <<intervals[i][1] << " res: " << curCnt << " @ " << curCover[0] << "->" << curCover[1] << " | " << canUse << endl;


        //         ++i;
        //         continue;
        //     }

        //     // case4: only 1 intersection
        //     // curCover:      -----   
        //     // cur interval:      ---- 
        //     if(curCover[1] == intervals[i][0]) {
        //         curCover[0] = intervals[i][0] + 1;
        //         curCover[1] = intervals[i][1];
        //         if(canUse == 1) {
        //             curCnt += canUse;
        //             canUse = 0;
        //         }
        //         curCnt += 1;
        //         canUse = 1;
        //         cout << " " << intervals[i][0] << "->" <<intervals[i][1] << " res: " << curCnt << " @ " << curCover[0] << "->" << curCover[1] << " | " << canUse << endl;

        //         ++i;
        //         continue;
        //     }

        //     // case5: no  intersection
        //     // curCover:      -----
        //     // cur interval:       --
        //     if(curCover[1] < intervals[i][0]) {
        //         curCover[0] = intervals[i][0];
        //         curCover[1] = intervals[i][1];

        //         curCnt += 2;
        //                         cout << " " << intervals[i][0] << "->" <<intervals[i][1] << " res: " << curCnt << " @ " << curCover[0] << "->" << curCover[1] << " | " << canUse << endl;


        //         ++i;
        //         continue;
        //     }

        // }
        // return curCnt;

    }
};
```