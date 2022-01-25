
## 0850. 矩形面积 II

### 1 题目：
[https://leetcode-cn.com/problems/rectangle-area-ii/solution](https://leetcode-cn.com/problems/rectangle-area-ii/solution)

### 2 解题思路：
- 1 参考官方思路的扫描线：[https://leetcode-cn.com/problems/rectangle-area-ii/solution/ju-xing-mian-ji-ii-by-leetcode/](https://leetcode-cn.com/problems/rectangle-area-ii/solution/ju-xing-mian-ji-ii-by-leetcode/)
- 2 总结过程：
  - 2.1 将一个矩形看成x1,x2,y1,ST; x1,x2,y2,ED;的两条线
  - 2.2 而后用active记录还没有遇到ED的那些矩形的第一个扫描线集合，每回新来了一根线，则将active中的所有线和当前线计算对应面面积加起来
  - 2.3 当active中遇到了矩形的ED，则将active中对应的矩形的ST删除
```cpp
class Solution {
public:
    static constexpr long long bigPrime = 1000000007;
    int rectangleArea(vector<vector<int>>& rectangles) {
        // lines
        int ST = 0;
        int ED = 1;

        vector<vector<int>> lines;
        for(auto& vec : rectangles) {
            lines.emplace_back(vector<int>{vec[0], vec[2], vec[1], ST});
            lines.emplace_back(vector<int>{vec[0], vec[2], vec[3], ED});
        }

        // sort the lines by the y
        sort(lines.begin(), lines.end(), 
            [](vector<int>& a, vector<int>& b) {
                return a[2] < b[2];
        });

        // scan the lines
        vector<vector<int>> actives;
        long long res = 0;
        int lastY = lines[0][2];
        for(auto& line : lines) {
            int curY = line[2], type = line[3], x1 = line[0], x2 = line[1];
            int width = 0;
            int actX = -1;
            
            // actives: those opend lines, sorted by y
            for(auto& act : actives) {
                // cout << "act: " << act[0] << " " << act[1] << endl;
                actX = max(actX, act[0]);
                width += max(act[1] - actX, 0);
                actX = max(actX, act[1]);
            }

            res += static_cast<long long>(width) * (curY - lastY) % bigPrime;
            // cout << "w: " << width << endl;

            // add new actives
            if(type == ST) {
                actives.emplace_back(vector<int>{x1, x2, curY, type});
                // cout << "insert x1,2: " << x1 << " " << x2 << endl;
                // sort the opend lines of the started points
                sort(actives.begin(), actives.end(), 
                    [](vector<int>& line1, vector<int>& line2) {
                        return line1[0] < line2[0];
                    });
            } else {
                // find the active and rm it
                for(int i = 0; i < actives.size(); ++i) {
                    if(actives[i][0] == x1 && actives[i][1] == x2) {
                        actives.erase(actives.begin() + i);
                        // cout << "earse x1,2: " << x1 << " " << x2 << endl;
                        break;
                    }
                }
            }

            lastY = curY;
        }

        return res % bigPrime;


        // belowing ways will failed when: 0, 0, 5, 2; 3, 3, 7, 9;
        // // we just need to calculate the up and downside outline of the retangles
        // // then we could knwo the answer
        // // sort the recs by the x1
        // sort(rectangles.begin(), rectangles.end(), 
        //     [](vector<int>& a, vector<int>& b) {
        //         return a[0] < b[0];
        // });

        // for(auto& vec : rectangles) {
        //     cout << vec[0] << " " << endl;
        // }

        // int maxH = INT_MIN;
        // int minL = INT_MAX;
        // int maxR = INT_MIN;
        // for(int i = 0; i < rectangles.size(); ++i) {
        //     maxH = max(rectangles[i][3], maxH);
        //     minL = min(rectangles[i][0], minL);
        //     maxR = max(rectangles[i][2], maxR);
        // }
        // int trueWidth = maxR - minL;

        // // cal upLine suqare(from sky to ground) and downLine(from ground to sky) suqare
        // long long upToGroundSuqare = 0;
        // long long ans = 0;
        // vector<vector<int>> upLine;
        // vector<vector<int>> downLine;
        // for(int i = 0; i < rectangles.size(); ++i) {
        //     upLine.emplace_back(vector<int>{rectangles[i][0], rectangles[i][2], rectangles[i][3]});
        //     downLine.emplace_back(vector<int>{rectangles[i][0], rectangles[i][2], maxH - rectangles[i][1]});
        // }

        // cout << "d0" << endl;
        // vector<vector<int>> upSkyLine = getSkyLine(upLine);
        // vector<vector<int>> downSkyLine = getSkyLine(downLine);
        // cout << "d1" << endl;
        // print(upSkyLine);
        // cout << "-------" << endl;
        // print(downSkyLine);


        // // cal suqare res
        // for(int i = 0; i < upSkyLine.size() - 1; ++i) {
        //     ans = (ans + static_cast<long long>(upSkyLine[i][1]) * static_cast<long long>((upSkyLine[i+1][0] - upSkyLine[i][0]) % bigPrime)) % bigPrime;
        //     if(upSkyLine[i][1] == 0) {
        //         trueWidth -= (upSkyLine[i+1][0] - upSkyLine[i][0]);
        //     }
        // }
        // cout << " 1st ans: " << ans << endl;
        // for(int i = 0; i < downSkyLine.size() - 1; ++i) {
        //     ans = (ans + static_cast<long long>(downSkyLine[i][1]) * static_cast<long long>(abs(downSkyLine[i+1][0] - downSkyLine[i][0]) % bigPrime)) % bigPrime;
        // }

        // cout << " 2nd ans: " << ans << endl;
        // return ans % bigPrime - maxH * static_cast<long long>(trueWidth) % bigPrime;
    }

    vector<vector<int>> getSkyLine(vector<vector<int>>& buildings) {
        function<bool(pair<int, int>&, pair<int, int>&)> cmp = 
        [](pair<int, int>& a, pair<int, int>& b) {
            return a.second < b.second;
        };

        // <rightBound, height>
        priority_queue<pair<int, int>, vector<pair<int, int>>, function<bool(pair<int, int>&, pair<int, int>&)> > queue(cmp);

        vector<int> bounds;
        vector<vector<int>> res;
        int n = buildings.size();
        for(int i = 0; i < n; ++i) {
            bounds.emplace_back(buildings[i][0]);
            bounds.emplace_back(buildings[i][1]);
        }

        sort(bounds.begin(), bounds.end(), std::less<int>());
        // std::cout << "c1" << endl;
        
        int j = 0;
        for(auto& curBound : bounds) {
            // std::cout << "c "  << j << endl;
            // push buildings lefter than curBound until one righter meet
            while(j < buildings.size() && curBound >= buildings[j][0]) {
                queue.push(make_pair(buildings[j][1], buildings[j][2]));
                ++j;
            }
            // std::cout << "c "  << "adf" << endl;

            // pop out those rec unrelevant
            while(!queue.empty() && curBound >= queue.top().first) {
                queue.pop();
            }

            int curBoundHeight = queue.empty() ? 0 : queue.top().second;

            // if(res.size() == 0 || res.back()[1] != curBoundHeight) {
            //     res.emplace_back(vector<int>{curBound, curBoundHeight});
            // }
            if(res.size() == 0 || res.back()[1] != curBoundHeight) {
                res.emplace_back(vector<int>{curBound, curBoundHeight});
            }
        }

        return res;
    }

    void print(vector<vector<int>>& vec) {
        for(auto& v : vec) {
            for(auto& i : v) {
                cout << i << " ";
            }
            cout << endl;
        }

    }
};
```