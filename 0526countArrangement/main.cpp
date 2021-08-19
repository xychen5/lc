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
    int countArrangement(int n) {
        this->n = n;

        // vec to place the arrange
        vector<int> curArr;
        vector<int> leftArr;
        for(int i = 0; i < n; ++i) {
            leftArr.emplace_back(i+1);
        }

        backTracking(curArr, leftArr);
                                            
        return sum;
    }

    bool backTracking(vector<int>& curArr, vector<int>& leftArr) {
        if(curArr.size() == n) {
            sum += 1;
            return true;
        }
        
        for(int i = 0; i < leftArr.size(); ++i) {
        // for(list<int>::iterator i = leftArr.begin(); i != leftArr.end(); ++i) {
            // try value
            int tar =  leftArr[i];
            curArr.emplace_back(tar);
            int curPos = curArr.size();

            // judge if ok
            if(tar % (curPos) == 0 || \
                (curPos) % tar == 0) {     
                // update the next level Arr and dive into
                vector<int> nextLevel = leftArr;
                nextLevel.erase(nextLevel.begin() + i);

                backTracking(curArr, nextLevel);
            }

            // try next value of curLevel
            curArr.pop_back(); 
        }
        return true;
    }
private:
    int sum = 0;
    int n = 0;
};

int main() {
    // vector<int> nums = {1, 15, 5, 11};
    // vector<int> nums = {1, 3};
    // vector<int> nums = {1, 3};
    // vector<int> nums = {1, 2, 5, 7};

    int n = 1;
    vector<int> nums = {2, 2, 3, 4};

    vector<vector<int>> nums2d1 = {
        {0, 1, 1, 0}, 
        {0, 0, 0, 0}
    };

    std::string str = "()(()())()(";

    Solution sl;
    std::cout << sl.countArrangement(n) << std::endl;
    
    // std::cout << ios::left << std::setw(20) << "Hello, World!" << std::setw(5) << "a s " << 1 << std::endl;
    return 0;
}