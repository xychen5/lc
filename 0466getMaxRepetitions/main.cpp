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
    int getMaxRepetitions(string s1, int n1, string s2, int n2) {
        // find how many s1 can construct a s2
        string matchStr;
        int len1 = s1.length();
        int len2 = s2.length();
        int p1 = 0, p2 = 0;
        vector<int> firstMatchInS1;
        vector<int> lastMatchInS2;
        int headS1UnUsedCnt = 0;
        map<int, int> posToS1Repeat;
        map<int, int> posToMatchStrPos;
        bool firstMatch = true;
        int s1Cnt = 0;
        int nS1EqualKS2 = -1;
        int kS2 = -1;
        while(s1Cnt < n1) {
            if(s1[p1] == s2[p2]) {
                if(firstMatch) {
                    if(posToS1Repeat.find(p2) == posToS1Repeat.end()) {
                        posToS1Repeat[p2] = s1Cnt;
                        posToMatchStrPos[p2] = matchStr.size();
                    } else {
                        headS1UnUsedCnt = posToS1Repeat[p2];
                        nS1EqualKS2 = s1Cnt - posToS1Repeat[p2];
                        kS2 = (matchStr.size() - posToMatchStrPos[p2]) / len2;
                        break;
                    }
                    firstMatchInS1.push_back(p2);
                    firstMatch = false;
                }
                matchStr.push_back(s1[p1]);
                p2 = (p2 + 1) % len2;
            }
            p1 = (p1 + 1) % len1;
            if(p1 == 0) {
                ++s1Cnt;
                firstMatch = true;
            }
        }



        // recycle node found
        int entirePart = 0; 
        // cout << nS1EqualKS2 << "/" << kS2 << endl;
        // entire:

        double repeatS2InS1 =  (double)(n1 - headS1UnUsedCnt) / nS1EqualKS2 * kS2;
        entirePart += floor(repeatS2InS1 / n2);
        int leftS1Cnt = n1 - round((double)entirePart * n2 * 1.0/ kS2 * nS1EqualKS2);
		// partly: 
        repeatS2InS1 = 0;
        
        // no recycle node found!
        if(nS1EqualKS2 == -1) {
            repeatS2InS1 = 0;
            leftS1Cnt = n1;
            entirePart = 0;

        }

        p1 = 0, p2 = 0;
        matchStr.clear();
        while(leftS1Cnt != 0) {
            if(s1[p1] == s2[p2]) {
                matchStr.push_back(s1[p1]);
                p2 = (p2 + 1) % len2;
            }
            p1 = (p1 + 1) % len1;
            if(p1 == 0) {
                --leftS1Cnt;
            }
        }
        repeatS2InS1 += matchStr.length() / len2;
        
        return (int)repeatS2InS1 / n2 + entirePart;
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