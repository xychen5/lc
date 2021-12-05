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

    bool unionMerge(vector<int>& parent, vector<int>& subTreeSize, int x, int y) {
        int findX = find(parent, x);
        int findY = find(parent, y);
        if(findX != findY) {
            parent[findX] = findY;
            subTreeSize[findY] += subTreeSize[findX];
            return true;
        }
        return false;
    }


    int minMalwareSpread(vector<vector<int>>& graph, vector<int>& initial) {
        // 对于每个initial计数的方式发生了改变，考虑一个不含有inital 的图，initial的得分应该是单独被他影响的子集
        int n = graph.size();
        vector<int> parent(n);
        for(int i = 0; i < n; ++i) {
            parent[i] = i;
        }
        
        vector<bool> isInitial(n, false);
        for(auto& i : initial) {
            isInitial[i] = true;
        }

        vector<int> subTreeSize(n, 1);
        // 构造union find set
        for(int i = 0; i < n; ++i) {
            if(isInitial[i]) {
                continue;
            }
            for(int j = 0; j < n; ++j) {
                if(1 == graph[i][j] && !isInitial[j]) {
                    unionMerge(parent, subTreeSize, i, j);
                }
            }
        }

        // for(int i = 0; i < n; ++i) {
        //     cout << "root " << i << " -> size " << subTreeSize[i] << endl;
        // }
        
        // find componets infected by a initial
        unordered_map<int, unordered_set<int>> initialToComponents;
        unordered_map<int, int> rootToInitial;
        for(auto& i : initial) {
            unordered_set<int> components;
            for(int v = 0; v < n; ++v) {
                if(!isInitial[v]) {
                    if(graph[i][v] == 1) {
                        int root = find(parent, v);
                        components.insert(root);
                        // cout << " ||| " << i << " >> " << root << endl;
                        // no occupied by single initial
                        if(rootToInitial.find(root) != rootToInitial.end() && \
                        rootToInitial[root] != i) {
                            rootToInitial[root] = -1;
                            continue;
                        }
                        rootToInitial[root] = i;
                    }
                }
            }
            initialToComponents[i] = components;
        }


        // cal scores for each initial
        int resInit = INT_MAX;
        int maxScore = INT_MIN;
        for(auto& p : initialToComponents) {
            int curInit = p.first;
            unordered_set<int> components = p.second;
            int score = 0;
            for(auto& root : components) {
                // std::cout << curInit << " -> " << score  << " with com: " << root << endl;
                if(rootToInitial[root] != -1) {
                    score += subTreeSize[root];
                    // cout << "added!" << endl;
                }
            }
            if(score > maxScore || (score == maxScore && curInit < resInit)) {
                maxScore = score;
                resInit = curInit;
            }
        }

        return resInit;
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