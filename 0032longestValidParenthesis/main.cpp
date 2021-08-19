#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <limits.h>
#include <numeric>

using namespace std;

class Solution {
public:
    int longestValidParentheses(string s) {
        int stIdx, edIdx, maxLen;
        maxLen = stIdx = edIdx = 0;
        vector<int> lStack;
        if(s.length() <= 1) {
            return 0;
        }

        for(edIdx = stIdx; edIdx < s.length(); ++edIdx) {
            if(s[edIdx] == '(') {
                lStack.emplace_back(edIdx);
            }else {
                if (lStack.size() >= 1) {
                    lStack.pop_back();
                    if(lStack.size() == 0) {
                        maxLen = std::max(maxLen, edIdx - stIdx + 1);
                    } else {
                        maxLen = std::max(maxLen, edIdx - lStack.back());
                    }
                } else {
                    stIdx = edIdx + 1;
                }
            }
        }

        return maxLen;
    }
};

int main() {
    std::string str = "())))(()())()(";
    Solution sl;
    std::cout << sl.longestValidParentheses(str) << std::endl;
    
    // std::cout << ios::left << std::setw(20) << "Hello, World!" << std::setw(5) << "a s " << 1 << std::endl;
    return 0;
}
