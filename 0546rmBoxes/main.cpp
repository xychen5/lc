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
#include <set>
#include <string>

using namespace std;
class Solution {
public:
    int maxPoint = INT_MIN;
    unordered_map<string, int> memo;
    int removeBoxes(vector<int>& boxes) {
        // dp
        vector<vector<vector<int>>> dp(100, vector<vector<int>>(100, vector<int>(100, 0)));
        int n = boxes.size();
        return calRes(dp, boxes, 0, n - 1, 0);

        // memo search, 20/65, not fast
        // return backTrack(boxes, 0);
    }

    int calRes(vector<vector<vector<int>>>& dp, vector<int>& boxes, int st, int ed, int k) {
        if(st > ed) {
            return 0;
        }
        
        if(dp[st][ed][k] == 0) {
            dp[st][ed][k] = max(dp[st][ed][k], calRes(dp, boxes, st, ed - 1, 0) + (k + 1) * (k + 1));
            for(int i = st; i <= ed-1; ++i) {
                if(boxes[i] == boxes[ed]) {
                    dp[st][ed][k] = max(
                        dp[st][ed][k], 
                        calRes(dp, boxes, st, i, k + 1) + calRes(dp, boxes, i + 1, ed - 1, 0)
                    );
                }
            }
        }
        
        return dp[st][ed][k];
    }

    // int backTrack(vector<int>& boxes, int curPoint) {
    //     if(boxes.size() == 0) {
    //         return 0;
    //     }
        
    //     string boxStr = myArrayToString(boxes);
    //     if(memo.find(boxStr) != memo.end()) {
    //         return memo[boxStr];
    //     }

    //     // st -> ed
    //     map<int, int> seg; 
    //     findContinousSegment(seg, boxes);
    //     // printMap(seg);
    //     int curLevelMax = INT_MIN;

    //     for(auto& p : seg) {
    //         vector<int> tmp = boxes;
    //         tmp.erase(tmp.begin() + p.first, tmp.begin() + p.second);

    //         int curGain = (p.second - p.first) * (p.second - p.first);
    //         curLevelMax = max(backTrack(tmp, curPoint) + curGain, curLevelMax);
    //     }
    //     memo[boxStr] = curLevelMax;
    //     return curLevelMax;
    // }

    // void findContinousSegment(map<int, int>& seg,  vector<int>& boxes) {
    //     int st = 0;
    //     int cur = st;
    //     while(cur < boxes.size() && st < boxes.size()) {
    //         if(boxes[cur] == boxes[st]) {
    //             ++cur;
    //         } else {
    //             seg[st] = cur;
    //             st = cur;
    //             ++cur;
    //         }
    //     }
    //     seg[st] = boxes.size();
    // }

    // string myArrayToString(vector<int>& arr) {
    //     string tmp = "";
    //     for(auto& i : arr) {
    //         tmp += to_string(i);
    //         tmp.push_back(',');
    //     }
    //     return tmp;
    // }

    // void printMap(map<int, int>& seg) {
    //     for(auto p : seg) {
    //         cout << p.first << " -> " << p.second << endl; 
    //     }
    // }
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
    // Solution sl;
    // std::cout << sl.medianSlidingWindow(nums1d, 3) << std::endl;

    // std::cout << ios::left << std::setw(20) << "Hello, World!" << std::setw(5) << "a s " << 1 << std::endl;
    return 0;
    std::cout << "Hello World!\n";
}