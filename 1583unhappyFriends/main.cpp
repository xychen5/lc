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
    int unhappyFriends(int n, vector<vector<int>>& preferences, vector<vector<int>>& pairs) {
        vector<vector<int>> rank(n, vector<int>(n, -1));
        for(int i = 0; i < n; ++i) {
            for(int j = 0; j < n-1; ++j) {
                rank[i][preferences[i][j]] = j;
            }
        }

        unordered_map<int, int> mapPair;
        for(int i = 0; i < n / 2; ++i) {
            mapPair[pairs[i][0]] = pairs[i][1];
            mapPair[pairs[i][1]] = pairs[i][0];
        }

        int unhappyNum = 0;
        // for ervey person
        for(int i = 0; i < n; ++i) {
            int p1 = i;
            int p2 = mapPair[i];
            // for p1's better matched ones than p2:
            // if(rank[p1][p2] == 0)
            for (int j = 0; j < rank[p1][p2]; ++j) {
                int betterThanP2 = preferences[p1][j];
                if(rank[betterThanP2][p1] <
                    rank[betterThanP2][mapPair[betterThanP2]]) {
                    unhappyNum ++;
                    break;
                }
            }
        }

        return unhappyNum; 
    }
};
int main() {
    // vector<int> nums = {1, 15, 5, 11};
    // vector<int> nums = {1, 3};
    // vector<int> nums = {1, 3};
    int n = 2;
    vector<int> nums1d = {1, 3};
    vector<vector<int>> nums2d1 = {{1}, {0}};
    vector<vector<int>> nums2d2 = {
        {1,0}
    };
    Solution sl;
    std::cout << sl.unhappyFriends(n, nums2d1, nums2d2) << std::endl;

    // std::cout << ios::left << std::setw(20) << "Hello, World!" << std::setw(5) << "a s " << 1 << std::endl;
    return 0;
}
