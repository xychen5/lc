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
    int ans = -1;

    void dfs(int from, string& colors, vector<vector<int>>& g, map<char, int>& cntInPath) {
        cntInPath[colors[from]]++;
        ans = max(ans, cntInPath[colors[from]]);
        for(int to = 0; to < g.size(); ++to) {
            if(g[from][to] == 1) {
                dfs(to, colors, g, cntInPath);
            }
        }
        cntInPath[colors[from]]--;
    }

    int largestPathValue(string colors, vector<vector<int>>& edges) {
        // // 自然能够想到的解题方法: 
        // // 基于出度为0的点做dfs，然后统计每个颜色的值
        // vector<int> noInNode;
        // map<int, int> inDegreeStatistic;
        // for(auto &e : edges) {
        //     inDegreeStatistic[e[1]]++;
        // }
        // int n = colors.size();
        // for(int i = 0; i < n; ++i) {
        //     auto it = inDegreeStatistic.find(i);
        //     if(it == inDegreeStatistic.end()) {
        //         noInNode.emplace_back(i);
        //     }
        // }

        // if(noInNode.size() == 0){
        //     return -1;
        // }

        // vector<vector<int>> g(n, vector<int>(n, -1));
        // for(int i = 0; i < edges.size(); ++i) {
        //     g[edges[i][0]][edges[i][1]] = 1;
        // }

        // // 对每一个节点出度为0的遍历
        // int maxApperanceNumInPath = -1;
        // map<char, int> cntInPath;
        // for(auto& c : colors) {
        //     cntInPath[c] = 0;
        // }
        // for(auto& n : noInNode) {
        //     dfs(n, colors, g, cntInPath);
        // }

        // 上述算法的遍历节点总是从出度为0的地方开始遍历所有可能的路径
        // 有重复计算的第方，想象一下，1, 2分别连着3,3后面跟了1000个节点
        // 那么会动1,2分别计算一遍，那3后面的1000个节点被重复计算了2次
        // 很显然我们就会想到从小规模开始计算，那么1,2的计算结果就能利用
        // 小规模的值得到了,那么什么样的节点算是小规模子图的起始点？
        // 这隐藏了一个拓扑排序 + 动态规划的思路在其中：
        // 如果想要减少上述重复计算过程，可以考虑使用动态规划，但是
        // 需要直到1,2,3以及后面节点谁在前谁在后的问题，使用拓扑排序解决
        // dp[v][c] 表示到达节点v的所有路径的颜色为c的最大值(并未统计v节点本身)
        // 对于u所有的 -> v: 
        // dp[v][c] = max(dp[u][c], dp[v][c]); // 广度优先遍历

        // 构建邻接表，统计入度情况
        vector<int> noInNode;
        int n = colors.size();
        vector<vector<int>> g(n);

        map<int, int> inDeg;
        for(auto &e : edges) {
            inDeg[e[1]]++;
            g[e[0]].emplace_back(e[1]);
        }
        
        // 做拓扑排序，首先找到那些个入度为0的点
        vector<array<int, 26>> dp(n);
        deque<int> q;
        for(int i = 0; i < n; ++i) {
            auto it = inDeg.find(i);
            if(it == inDeg.end()) {
                q.push_back(i);
            }
        }
        
        // bfs访问节点的数目超过n本身才能说明有环
        // 或者dfs能够访问到之前访问过的节点，也说明有环
        // 不能仅仅通过是否有出度为0的节点来判断是否成环，eg:
        // [[0,1],[1,1]]
        int bfsTravelNum = 0;
        // 使用bfs遍历获取拓扑排序顺便动态规划
        while(!q.empty()) {
            ++bfsTravelNum;
            // 取出一个没有入度的节点
            int u = q.front();
            q.pop_front();
            // 访问到u节点
            dp[u][colors[u] - 'a']++;

            // 更新所有 以v为终点的路径(不包含v本身) 的颜色为c的最大节点数
            for(int v : g[u]) {
                inDeg[v]--;
                for(int c = 0; c < 26; ++c) {
                    dp[v][c] = max(dp[v][c], dp[u][c]);
                }
                // 位于u拓扑排序后面的v
                if(0 == inDeg[v]) {
                    q.push_back(v);
                }
            }
        }
        
        if(bfsTravelNum != n) return -1;

        for(int i = 0; i < n; ++i) {
            ans = std::max(ans, *max_element(dp[i].begin(), dp[i].end()));
        }

        return ans;
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