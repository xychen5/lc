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
    int allBallsCnt = -1;
    map<string, int> memo;

    int findMinStep(string board, string hand) {
        // simulate this game
        int res = 0;
        allBallsCnt = hand.size();
        res = bfs(board, hand);
        return res == INT_MAX ? -1 : res;
    }
    int bfs(string board, string hand) {
        // space mustn't be eliminated! it's neutig!
        if(memo.find(board + " " + hand) != memo.end()) {
            return memo[board + " " + hand];
        }

        if(0 == board.size()) {
            return allBallsCnt - hand.size();
        }
        if(0 == hand.size()) {
            return INT_MAX;
        }

        int useRes = INT_MAX;
        string lastTarBallStr = "";
        for(int k = 0; k < hand.size(); ++k) {
            string nextHand = hand.substr(0, k) + hand.substr(k + 1);
            string tarBallStr = hand.substr(k, 1);

            // case1: cut the same ball
            if(tarBallStr == lastTarBallStr) {
                continue;
            }

            // use this char, find put pos
            for(int i = 0; i <= board.size(); ++i) {
                // case2: only insert at the start of str with same chars
                if(i > 0 && board[i - 1] == hand[k]) {
                    continue;
                }

                // case3: only put when cur is equal current || when cur is not equal to two continuous same chars
                if(i < board.size() && board[i] == hand[k] || \
                i > 0 && board[i] == board[i-1] && hand[k] != board[i-1]) {
                    string tmpBoard1 = board;
                    tmpBoard1.insert(i, tarBallStr);
                    // reduce repeat balls
                    reduceRepeat(tmpBoard1);

                    // put to tarBall left and right
                    int lRes = bfs(tmpBoard1, nextHand);

                    useRes = min(lRes, useRes);
                }
            }
            
            lastTarBallStr = tarBallStr;
        }
        memo[board + " " + hand] = useRes;
        return useRes;
    }

    inline void reduceRepeat(string& board) {
        int idx = 0;
        // cout << "reducing " << board << endl;
        while(board.length() > 0 && idx < board.length()) {
            int st = idx, cur = st;
            char head = board[st];
            while(++cur < board.length() && board[cur] == head) {
            }
            if(cur - st >= 3) {
                board.erase(st, cur - st);
                idx = 0;
            } else {
                idx = cur;
            }
        }
        // cout << "after redu " << board << endl;
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
    // Solution sl;
    // std::cout << sl.medianSlidingWindow(nums1d, 3) << std::endl;

    // std::cout << ios::left << std::setw(20) << "Hello, World!" << std::setw(5) << "a s " << 1 << std::endl;
    return 0;
    std::cout << "Hello World!\n";
}