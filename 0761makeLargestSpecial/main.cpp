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
    string makeLargestSpecial(string s) {
        string res = reArrange(s);
        // string lastRes = "";
        // while(res != reArrange(res)){
        //     res = reArrange(res);
        // };
        return res;
    }

    string reArrange(string s) {
        // cout << "c1->"  << s << endl;
        int n = s.size();
        if(s.size() <= 2) {
            // cout << "less than 2: " << s << endl;
            return s;
        }

        // firstly, get all special subStr and sort as the lexical order
        vector<string> subStr;

        int st = 0;
        int cntRedundantNumberOne = 1;
        for(int i = st + 1; i < n; ++i) {
            cntRedundantNumberOne += (s[i] == '1' ? 1 : -1);
            if(0 == cntRedundantNumberOne) {
                subStr.emplace_back(s.substr(st, i - st + 1));
                st = i + 1;
                cntRedundantNumberOne = 0;
            }
        }

        if(1 == subStr.size()) {

            return s.substr(0, 1) + reArrange(s.substr(1, n-2)) + s.substr(n-2, 1);
        }

        // for(auto i : subStr) {
        //     cout << i << endl;
        // }
        
        
        // secondly, sort all sub part and sum up
        // cout << "a" << endl;
        for(int i = 0; i < subStr.size(); ++i) {
            subStr[i] = reArrange(subStr[i]);
        }
        // we shall reArrange first and then sort,
        // because when we reArrage, we my produce bigger subStr, 
        // if we sort first and reArrange all subpart we could get false res: eg: 
        // input:        "11100011010101100100"
        // false Result: "111000 11100101010100" // part2 is bigger subStr, so we shall reArrange all sub first and then sort
        // std result:   "11100101010100 111000" 
        sort(subStr.begin(), subStr.end(), std::greater<string>());

        string res = "";
        for(auto s : subStr) {
            res += s;
        }

        // cout << "c2" << endl;
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