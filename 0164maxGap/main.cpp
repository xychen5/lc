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
    int n = -1;
    int k = -1;
    vector<char> kVec;
    string crackSafe(int n, int k) {
        // since for each bit, there a k's possiblity
        // so the final str's length = k^n
        // consider a G, vertices are {0, 1, ..., k-1}
        // for each edge: vi -> vj(vi could equal vj), 
        // there shall be n-1's such same edge
        // we just need a way to walk through the G
        // try hierholzer algo
        if(1 == n) {
            string tmpRes = "";
            for(int i = 0; i < k; ++i) {
                tmpRes.push_back(i + '0');
            }
            return tmpRes;
        }

        this->k = k;
        this->n = n;
        for(int i = 0; i < k; ++i) {
            kVec.push_back(i + '0');
        }

        unordered_set<string> seen;
        unordered_map<string, vector<char>> graph;
        buildGraph("", n - 1, graph);
        
        string stStr(n-1, '0');
        string res = stStr;
        if(1 == k) { // then st == last posiont
            res = "";
        }
        hierholzer(stStr, graph, res, seen);
        
        // when n=3, k=3, we start from "00" node, so we add reverse of "00" to the end of the res, cause hierholzer produce a reverse eular path (start from "00", end to "00")
        res += stStr;

        // // print g
        // for(auto p : graph) {
        //     for(auto j : p.second) {
        //         cout << "i->j " << p.first << " " << j << endl;
        //     }
        // }
        // cout << "g done!" << endl;

        

        return res;
    }

    void buildGraph(string tmp, int leftBitNum, unordered_map<string, vector<char>>& graph) {
        if(0 == leftBitNum) {
            // cout << "len: " << leftBitNum << "finish node: " << tmp << endl;
            graph[tmp] = kVec;
            return;
        }

        for(int st = 0; st < k; ++st) {
            buildGraph(tmp + kVec[st], leftBitNum-1, graph);
        }
    }

void hierholzer(
    string st, 
    unordered_map<string, vector<char>>& graph, 
    string& res, 
    unordered_set<string>& seen) {
        char nextE = '-';
        bool hasOut = false;
        // cout << "doing : " << st << endl;
        for(int edIdx = 0; edIdx < k; ++edIdx) {
            string curEdge(st);
            curEdge.push_back(graph[st][edIdx]);
            
            if(seen.count(curEdge)) {
                continue;
            }
            
            hasOut = true;
            string nextSt = curEdge.substr(1);
            // cout << "st -> nextSt: " << st << " -> " << nextSt << endl;
            seen.insert(curEdge);
            // cout << "see edge: " << curEdge << endl; 
            hierholzer(nextSt, graph, res, seen);
            nextE = graph[st][edIdx];
            // cout << "res is " << res << endl;
        }
        if(hasOut) {
            res.push_back(nextE); // hierholzer
        }
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