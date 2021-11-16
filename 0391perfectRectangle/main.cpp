// ConsoleApplication1.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
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

using namespace std;

class Solution {
public:
    struct point {
        int x = 0;
        int y = 0;
        point() {};
        point(int x, int y) :x(x), y(y) {}
        bool operator==(const point& a) { return a.x == this->x && a.y == this->y; }
    };
    struct point_hash
    {
        std::size_t operator () (point const& p) const
        {
            return std::hash<int>{}(p.x)* std::hash<int>{}(p.y) - p.y;
        }
    };

    bool isRectangleCover(vector<vector<int>>& rectangles) {
        int n = rectangles.size();


        // 计数所有顶点的出现个数
        // unordered_set<point, point_hash> ptCnt;
        map<pair<int, int>, int> ptCnt;
        // 点出现次数为1的点的个数为
        int singlePtNum = 0;
        int sumSquare = 0;
        auto p4M = std::make_pair(INT_MIN, INT_MIN); // 右上
        auto p1M = std::make_pair(INT_MAX, INT_MAX); // 左下

        for (int i = 0; i < n; ++i) {
            auto p1 = std::make_pair(rectangles[i][0], rectangles[i][1]); //左下
            auto p2 = std::make_pair(rectangles[i][2], rectangles[i][1]); // 右下
            auto p3 = std::make_pair(rectangles[i][0], rectangles[i][3]); // 左上
            auto p4 = std::make_pair(rectangles[i][2], rectangles[i][3]); // 右上
            sumSquare += (rectangles[i][3] - rectangles[i][1]) * \
                (rectangles[i][2] - rectangles[i][0]);

            p1M.first = std::min(p1M.first, p1.first);
            p1M.second = std::min(p1M.second, p1.second);
            p4M.first = std::max(p4M.first, p4.first);
            p4M.second = std::max(p4M.second, p4.second);


            ptCnt[p1]++;

            ptCnt[p2]++;

            ptCnt[p3]++;

            ptCnt[p4]++;

        }
        auto p2M = std::make_pair(p1M.first, p4M.second); // 左下
        auto p3M = std::make_pair(p4M.first, p1M.second); // 左下
        int coverSquare = (p4M.second - p1M.second) * (p4M.first - p1M.first);
        if (sumSquare != coverSquare || ptCnt[p1M] != 1 || ptCnt[p2M] != 1 || ptCnt[p3M] != 1 || ptCnt[p4M] != 1) return false;

        ptCnt.erase(p1M);
        ptCnt.erase(p2M);
        ptCnt.erase(p3M);
        ptCnt.erase(p4M);


        int cornerCnt = 0;
        for (auto& i : ptCnt) {
            if (i.second != 2 && i.second != 4) {
                return false;
            }
        }
        if (cornerCnt != 4) return false;
        return true;
    }
};
int main()
{
    // vector<int> nums = {1, 15, 5, 11};
    // vector<int> nums = {1, 3};
    // vector<int> nums = {1, 3};
    int n = 2;
    vector<int> nums1d = { 1, 0 };
    vector<vector<int>> nums2d1 = { {1}, {0} };
    vector<vector<int>> nums2d4 = { {1,1,3,3},{3,1,4,2},{3,2,4,4},{1,3,2,4},{2,3,3,4} };
    Solution sl;
    std::cout << sl.isRectangleCover(nums2d4) << std::endl;

    // std::cout << ios::left << std::setw(20) << "Hello, World!" << std::setw(5) << "a s " << 1 << std::endl;
    return 0;
    std::cout << "Hello World!\n";
}