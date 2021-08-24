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
    int compress(vector<char>& chars) {
        int res = 0;
        char cur = chars[0];
        int curLen = 1;

        if(chars.size() == 1) {
            return 1;
        }

        int curSize = chars.size();

        for(int i = 1; i < curSize; ++i) {
            if(chars[i] == cur) {
                curLen += 1;
                if (i == curSize - 1) {
                    res += countDecimalBits(curLen);
                    substitue(i - curLen + 2, curLen, cur, chars);
                    break;
                }
            } else {
                res += countDecimalBits(curLen);
                i += substitue(i - curLen + 1, curLen, cur, chars);
                
                curSize = chars.size();
                curLen = 1;
                cur = chars[i];
                if (i == curSize - 1) {
                    res += countDecimalBits(curLen);
                    break;
                }
            }
        }

        return res;
    }


    /**
    * chars = a b b b b b b b b b b b b b b b c c
    * for b, stIdx is 2, n is 15, substitueBitNum is 2
    * a b 1 5 c c
    * ret: should back to: 
    */
    int substitue(int stIdx, int n, char tarBit, vector<char>& chars) {
        if (n == 1) {
            return 0;
        }
        else {
            string tmp = std::to_string(n);
            int substitueBitNum = tmp.length();
            for(int i = 0; i < substitueBitNum; ++i) {
                chars[stIdx + i] = tmp[i];
            }

            // eliminate the redundant chars
            int eliminateNum = 0;
            while (chars.size() > stIdx + substitueBitNum \
              && chars[stIdx + substitueBitNum] == tarBit) {
                chars.erase(chars.begin() + stIdx + substitueBitNum);
                eliminateNum += 1;
            }

            return - eliminateNum;
        }
    }

    /**
    * n <= 2000
    * e.g.: if n = 1000, then return 4
    */
    int countDecimalBits(int n) {
        if(n == 1) {
            return 1;
        }
        else if(n < 10) {
            return 2;
        }
        else if ( n < 100) {
            return 3;
        }
        else if (n < 1000) {
            return 4;
        }
        return 4;
    }
};

int main() {
    // vector<int> nums = {1, 15, 5, 11};
    // vector<int> nums = {1, 3};
    // vector<int> nums = {1, 3};
    // vector<int> nums = {1, 2, 5, 7};
    vector<int> nums = {2, 2, 3, 4};

    vector<vector<int>> nums2d1 = {
        {0, 1, 1, 0}, 
        {0, 0, 0, 0}
    };

    vector<vector<int>> nums2d2 = {
        {1,2},
        {1,3},
        {2,3}
    };

    vector<char> charVec = {"a","b","c","c","c","d","e","f","g"};

    std::string str = "()(()())()(";

    Solution sl;
    std::cout << sl.compress(charVec) << std::endl;
    
    // std::cout << ios::left << std::setw(20) << "Hello, World!" << std::setw(5) << "a s " << 1 << std::endl;
    return 0;
}