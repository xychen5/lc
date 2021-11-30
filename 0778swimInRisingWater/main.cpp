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

using namespace std;
class Solution {
public:
    int find(vector<int>& parent, int x) {
        while(x != parent[x]) {
            parent[x] = parent[parent[x]];
            x = parent[x];
        }

        return x;
    }

    bool unionMerge(vector<int>& parent, int x, int y) {
        int findX = find(parent, x);
        int findY = find(parent, y);
        if(findX != findY) {
            parent[findX] = findY
            return true;
        }
        return false;
    }

    int swimInWater(vector<vector<int>>& grid) {
        // for each threshold, maintain a unionFind
        // everytime increase thres, we modify the connection of unionFind
        int n = grid.size();

        if(n == 1) {
            return 0;
        }

        vector<int> parent(n * n);
        for(int i = 0; i < n * n; ++i) {
            parent[i] = i;
        }

        // Each value grid[i][j] is unique.
        vector<vector<int>> elevationToIdx(n * n, vector<int>(n));
        for(int i = 0; i < n; ++i) {
            for(int j = 0; j < n; ++j) {
                elevationToIdx[grid[i][j]][0] = i;
                elevationToIdx[grid[i][j]][1] = j;
            }
        }

        vector<vector<int>> moves = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
        for(int thres = 0; thres < n * n; ++thres) {
            // when the rain rise, process the exact the same height grid
            int tarX = elevationToIdx[thres][0];
            int tarY = elevationToIdx[thres][1];
            for(auto deltaXY : moves) {
                int newX = tarX + deltaXY[0];
                int newY = tarY + deltaXY[1];
                if(newX >= 0 && newY >= 0 && newX < n && newY < n && grid[newX][newY] <= thres) {
                    // cout << newX << " " << newY << "  ->" << thres <<endl;
                    unionMerge(parent, grid[newX][newY], grid[tarX][tarY]);
                    if(find(parent, grid[0][0]) == find(parent, grid[n - 1][n - 1])) {
                        return thres;
                    }
                }
            }
        }
        return n*n;
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
    // std::cout << sl.medianSlidingWindow(nums1d, 3) << std::endl;

    // std::cout << ios::left << std::setw(20) << "Hello, World!" << std::setw(5) << "a s " << 1 << std::endl;
    return 0;
    std::cout << "Hello World!\n";
}