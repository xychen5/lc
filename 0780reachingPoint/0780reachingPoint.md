## 0780reachingPoint 到达终点

### 1 题目
[https://leetcode-cn.com/problems/reaching-points/](https://leetcode-cn.com/problems/reaching-points/)

### 2 解题思路
- 1 参考官解，最关键的是，我们倒过来从终点到起点的思维很关键，而且当tx==sx但是ty!=sy，我们的退出循环的方式，比如从5，52到5，2，其实就是看55能不能由sy + k*sx组成，可以就返回true，否则false

```cpp
class Solution {
public:
    int tx = -1;
    int ty = -1;
    bool reachingPoints(int sx, int sy, int tx, int ty) {
        int sum = sx + sy;
        // dfs search from st to ed
        // this->tx = tx;
        // this->ty = ty;
        // return checkCurPoint(sx, sy);
        
        // from ed to st
        while(tx >= sx && ty >= sy) {
            if(tx == sx && ty == sy) {
                return true;
            }

            if(tx == sx) {
                return (ty - sy) % sx == 0;
            }
            if(ty == sy) {
                return (tx - sx) % sy == 0;
            }

            if(tx > ty) {
                tx %= ty;
            } else {
                ty %= tx;
            }
        }
        return false;
        
    }
    
    bool checkCurPoint(int& sx, int& sy) {
        if(sx > tx || sy > ty) {
            return false;
        }

        if(sx == tx && sy == ty) {
            return true;
        }

        int sum = sx + sy;
        return checkCurPoint(sum, sy) || checkCurPoint(sx, sum);
    }
};
```