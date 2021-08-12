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
    int nthSuperUglyNumber(int n, vector<int>& primes) {
        std::priority_queue<long, std::vector<long>, std::greater<long>> uglyNum;
        std::unordered_set<long> ifAdded;
        std::list<long> lastLevel;
        
        int addNum = 1;
        uglyNum.emplace(1);
        while(1) {
            long curMin = uglyNum.top();
            if(addNum == n) {
                return curMin;
            }
            uglyNum.pop();
            
            for(int x = 0; x < primes.size(); ++x) {
                long tmp = curMin * primes[x];
                if (ifAdded.find(tmp) == ifAdded.end()) {
                    uglyNum.emplace(tmp);    
                    ifAdded.emplace(tmp);
                }
            }
            ++addNum;
        }
    }
};

int main() {
    // vector<int> nums = {1, 15, 5, 11};
    // vector<int> nums = {1, 3};
    // vector<int> nums = {1, 3};
    vector<int> nums = {2, 3, 5};
    Solution sl;
    std::cout << sl.nthSuperUglyNumber(9, nums) << std::endl;
    
    // std::cout << ios::left << std::setw(20) << "Hello, World!" << std::setw(5) << "a s " << 1 << std::endl;
    return 0;
}
