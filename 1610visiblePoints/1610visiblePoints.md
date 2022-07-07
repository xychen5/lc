## 1610visiblePoints 可见顶点的最大数目

### 1 题目
[https://leetcode.cn/problems/maximum-number-of-visible-points/](https://leetcode.cn/problems/maximum-number-of-visible-points/)

### 2 解题思路
- 1 解题思路:
  - 1.1 算出极角，然后排序，然后用一个窗口，范围是angle，从最小移动到最大即可
  - 1.2 注意循环：比如-179和179这两个数字爱得很近，所以我们把排序好的点的极角加上360加入到点的数组中，滑动窗口就行

```cpp
class Solution {
public:
    #define PI 3.14159265
 
    using Point = pair<pair<int, int>, double>;
    
    int visiblePoints(vector<vector<int>>& points, int angle, vector<int>& location) {

        vector<Point> calPoints;
        int n = points.size();
        int dupWithOriCnt = 0;
        // start form the negx: from -179.999 to 180
        auto calDegreeForPoints = [&](vector<int>& xy, vector<Point>& calPoints) {
            int x = xy[0] - location[0];
            int y = xy[1] - location[1];
            if(0 == x && 0 == y) {
                dupWithOriCnt += 1;
                return;
            }
            double result;
            result = atan2 (y, x) * 180 / PI;
            calPoints.emplace_back(Point{{x, y}, result});
        };   

        for(auto& p : points) {
            calDegreeForPoints(p, calPoints);
        }

        // all duplicated
        if(0 == calPoints.size()) {
            return dupWithOriCnt;
        }

        // sort by the angle
        sort(calPoints.begin(), calPoints.end(), [](const Point& a, const Point& b) {
            return a.second < b.second;
        });
        for(int i = 0; i < n; ++i) { // solve the circle problem
            auto p = calPoints[i];
            p.second += 360.0;
            calPoints.push_back(p);
        }

        // init window
        int st = 0;
        int ed = 0;

        double dAngle = angle;

        while(ed < calPoints.size() && calPoints[ed].second - calPoints[st].second <= dAngle) {
            ++ed;
        }
        --ed;
        int finRes = ed - st + 1;

        // mv window
        while(ed < calPoints.size()) {
            // mv st
            ++st;
            while(ed < calPoints.size() && calPoints[ed].second - calPoints[st].second <= dAngle) {
                ++ed;
            }
            if(ed == calPoints.size()) {
                finRes = max(finRes, static_cast<int>(calPoints.size()) - st);
            } else {
                --ed;
                finRes = max(finRes, ed - st + 1);
            }

        }

        return finRes + dupWithOriCnt;
    }
}
```