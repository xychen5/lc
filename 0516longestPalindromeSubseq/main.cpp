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
    int longestPalindromeSubseq(string s) {
        int n = s.length();
        if(n == 1) {
            return 1;
        }
        vector<vector<int>> subLen(n, vector<int>(n, 1));
        for(int i = n-2; i >= 0; --i) {
            for(int j = 0; j <= i; ++j) {
                int k = j + n - i - 1;
                if(s[j] == s[k]) {
                    subLen[j][k] = subLen[j+1][k-1] + 1 + (int)(abs(j-k) != 1);
                } else {
                    subLen[j][k] = max(subLen[j][k-1], subLen[j+1][k]);
                }
            }
        }
        return subLen[0][n-1];
    }
};

int main() {
    std::string str = "())))(()())()(";
    Solution sl;
    std::cout << sl.longestPalindromeSubseq(str) << std::endl;
    
    // std::cout << ios::left << std::setw(20) << "Hello, World!" << std::setw(5) << "a s " << 1 << std::endl;
    return 0;
}