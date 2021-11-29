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
    int minSwapsCouples(vector<int>& row) {
        // 容易被迷惑的地方： 一次交换至少能够完成一对情侣，只有最后的一次交换能够完成两队情侣，其余均只能完成一次
        // 所以说这个最小交换次数，其实别反复换，算出来的就是最小的
        
        // 首先注意到，将2个情侣看成一个节点，如果不属于一对的情侣坐在2k - 2, 2k - 1的两个位置上，则连一条线
        vector<int> parent(row.size() / 2);
        for(int i = 0; i < row.size() / 2; ++i) {
            parent[i] = i;
        }

        for(int i = 0; i < row.size(); i += 2) {
            int nodeIdx = i / 2;
            unionMerge(parent, row[i] / 2, row[i + 1] / 2);
            // std::cout << row[i] / 2<< " -> " << row[i + 1] / 2 << std::endl;
        }

        // 找出上图所有连通子图, 所有连通子图的边的节点个数减去1得到一个子图所有情侣相邻而坐需要的交换次数
        unordered_map<int, int> rootIdxToCnt;
        for(int i = 0; i < row.size() / 2; ++i) {
            rootIdxToCnt[find(parent, i)] ++;
            // std::cout << i << " -> " << find(parent, i) << std::endl;
        }

        int res = 0;
        for(auto& it : rootIdxToCnt) {
            res += it.second - 1;
        }
        return res;

    }

    int find(vector<int>& parent, int curNode) {
        while(parent[curNode] != curNode) {
            parent[curNode] = parent[parent[curNode]];
            curNode = parent[curNode];
        }
        return curNode;
    }

    void unionMerge(vector<int>& parent, int from, int to) {
        int x = find(parent, from);
        int y = find(parent, to);
        
        if(x != y) {
            parent[x] = y;
        }
    }
}

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