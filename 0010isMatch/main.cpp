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
    bool isMatch(string s, string p) {
        return greadyMatch(s, p);
    }

    bool greadyMatch(string s, string p) {
        int sLen = s.size();
        int pLen = p.size();
        // cout << "sLen & pLen => " << sLen << " " << pLen << s << " " << p << endl;
        if(pLen == 2 && p[0] == '.' && p[1] == '*') {
            return true;
        }

        if(pLen == 1) {
            if(sLen != 1) {
                return false;
            }
            return p[0] == '.' ? true : p[0] == s[0];
        }
        
        if(sLen == 0) {
            if(pLen == 0) {
                return true;
            }
            if(pLen == 2) {
                if(p[1] == '*') {
                    return true;
                }else {
                    return false;
                }
            } else {
                if(p[1] == '*') {
                    return greadyMatch(s, p.substr(2));
                } else {
                    return false;
                }
            }
        }

        if(pLen == 0) {
            return sLen == 0;
        }

        // match as much as possible
        char head0 = p[0];
        char head1 = p[1];
        bool res = false;

        if(p[0] == '.') {
            if(p[1] == '*') {
                // match any len >= 1 of s, when len == 0, then not match
                for(int len = 0; len <= sLen; ++len) {
                    res = res || greadyMatch(s.substr(len), p.substr(2));
                    // cout << "tried: " << s.substr(len) << " " << p.substr(2) << endl;
                }
                return res;
            } else { 
                return greadyMatch(s.substr(1), p.substr(1));
            }
        } else {
            // p[0] = a~z
            if(p[0] != s[0]) {
                if(p[1] == '*') {
                    // cout << p.substr(2) << "\nculled!" <<endl;
                    return greadyMatch(s, p.substr(2));
                } else {
                    return false;
                }
            } else {

                if(p[1] == '*') {
                    int sameLen = s.find_first_not_of(p[0]);
                    if(sameLen == -1) {
                        sameLen = sLen;
                    }
                    // cout << "sameLen2 -> " << sameLen << s.substr(1) << p.substr(2) << endl;
                    // when len = 0, not use this * to match
                    for(int len = 0; len <= sameLen; ++len) {
                        res = res || greadyMatch(s.substr(len), p.substr(2));
                    }
                    return res;
                } else {
                    return greadyMatch(s.substr(1), p.substr(1));
                }
            }
            
        }
        
        // never be executed
        return res;
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