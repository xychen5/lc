## 0874robotSim

### 1 题目
[https://leetcode-cn.com/problems/walking-robot-simulation/](https://leetcode-cn.com/problems/walking-robot-simulation/)

### 2 解题思路
很普通的模拟，
- 1 用一个结构代表机器人的状态，包括朝向和位置
- 2 模拟每个指令，然后相应的改变机器人的状态即可\

值得思考的点：
如何快速得知当前位置是不是被阻挡了？
使用unordered_set作为hash快速查找

```cpp
#include <utility>
class Solution {
public:
    struct MovingPoint {
        int x = 0;
        int y = 0;
        bool headingX = false;
        bool headingPositive = true;
    }curPoint, lastPoint;

    int biggestDistance = 0;

    int robotSim(vector<int>& commands, vector<vector<int>>& obstacles) {
        // todo: 使用set作为hash来存储是否有障碍，将查询复杂度降低到O(ln)
        std::unordered_set<std::string> obs;
        
        for(auto coor: obstacles) {
            obs.emplace(std::to_string(coor[0]) + "xxx" + std::to_string(coor[1]));
        }

        for(int curStep = 0; curStep < commands.size(); ++curStep) {
            if(commands[curStep] == -2) {
                // left
                if(curPoint.headingX) {
                    curPoint.headingPositive = curPoint.headingPositive ? true : false;
                } else {
                    curPoint.headingPositive = curPoint.headingPositive ? false : true;
                }
                curPoint.headingX = !curPoint.headingX;
            } else if (commands[curStep] == -1) {
                // right
                if(curPoint.headingX) {
                    curPoint.headingPositive = curPoint.headingPositive ? false : true;
                } else {
                    curPoint.headingPositive = curPoint.headingPositive ? true : false;
                }
                curPoint.headingX = !curPoint.headingX;
            } else {
                // move one step: low efficiency
                for(int i = 0; i < commands[curStep]; ++i) {
                    lastPoint = curPoint;
                    move(curPoint);
                    // if(getObstacled(curPoint, obstacles)) {
                    //     curPoint = lastPoint;
                    // }
                    if(getObstacled2(curPoint, obs)) {
                        curPoint = lastPoint;
                    }
                    int tmpDis = pow(curPoint.x, 2) + pow(curPoint.y, 2);
                    biggestDistance = std::max(biggestDistance, tmpDis);
                }

                // // move directly
                // move2(curPoint, commands[curStep], obstacles);
                // int tmpDis = pow(curPoint.x, 2) + pow(curPoint.y, 2);
                // biggestDistance = std::max(biggestDistance, tmpDis);
            }
        }
        // return curPoint.x*curPoint.x + curPoint.y * curPoint.y;
        return biggestDistance;
    }

    bool getObstacled(MovingPoint& curPoint, vector<vector<int>>& obstacles) {

        for(int i = 0; i < obstacles.size(); ++i) {
            if(curPoint.x == obstacles[i][0] && curPoint.y == obstacles[i][1]) {
                return true;
            }
        }
        return false;
    }

    bool getObstacled2(MovingPoint& curPoint, unordered_set<string>& obstacles) {
        if(obstacles.find(std::to_string(curPoint.x) + "xxx" + std::to_string(curPoint.y)) != obstacles.end()) {
            return true;
        }
        return false;
    }

    void move(MovingPoint& curPoint) {
        if(curPoint.headingPositive) {
            if(curPoint.headingX) {
                ++curPoint.x;
            } else {
                ++curPoint.y;
            }
        } else {
            if(curPoint.headingX) {
                --curPoint.x;
            } else {
                --curPoint.y;
            }
        }
    }

    void move2(MovingPoint& curPoint, int len, vector<vector<int>>& obstacles) {
        MovingPoint tarPoint = curPoint;
        bool obstacled = false;
        // get tarPoint
        if(tarPoint.headingPositive) {
            if(tarPoint.headingX) {
                tarPoint.x += len;
                int realX = tarPoint.x;

                for(int i = 0; i < obstacles.size(); ++i) {
                    if(curPoint.y == obstacles[i][1] && \
                       curPoint.x < obstacles[i][0] && \
                       tarPoint.x >= obstacles[i][0] 
                    ) {
                        realX = std::min(realX, obstacles[i][0]);
                        obstacled = true;
                    }
                }
                curPoint.x = realX - (int)obstacled;
            } else {
                tarPoint.y += len;
                int realY = tarPoint.y;
                for(int i = 0; i < obstacles.size(); ++i) {
                    if(curPoint.x == obstacles[i][0] && \
                       curPoint.y < obstacles[i][1] && \
                       tarPoint.y >= obstacles[i][1] 
                    ) {
                        realY = std::min(realY, obstacles[i][1]);
                        obstacled = true;
                    }
                }
                curPoint.y = realY - (int)obstacled;
            }
        } else {
            if(tarPoint.headingX) {
                tarPoint.x -= len;
                int realX = tarPoint.x;
                for(int i = 0; i < obstacles.size(); ++i) {
                    if(curPoint.y == obstacles[i][1] && \
                       curPoint.x > obstacles[i][0] && \
                       tarPoint.x <= obstacles[i][0] 
                    ) {
                        realX = std::max(realX, obstacles[i][0]);
                        obstacled = true;
                    }
                }
                curPoint.x = realX + (int)obstacled;
            } else {
                tarPoint.y -= len;
                int realY = tarPoint.y;
                for(int i = 0; i < obstacles.size(); ++i) {
                    if(curPoint.x == obstacles[i][0] && \
                       curPoint.y > obstacles[i][1] && \
                       tarPoint.y <= obstacles[i][1] 
                    ) {
                        realY = std::max(realY, obstacles[i][1]);
                        obstacled = true;
                    }
                }
                curPoint.y = realY + (int)obstacled;
            }
        }
        
        // cal real point if get obstacled

    }
};
```