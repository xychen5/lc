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
    int totalFruit(vector<int>& fruits) {
        if(fruits.size() <= 1) {
            return 1;
        }

        // 不同元素最多为2的数组长度
        int res = 0;
        int st = 0;
        int ed = 0;
        int curCnt = 0;
        map<int, int> freq;
        bool stNotMov = true;
        while(ed < fruits.size()) {
            while(freq.size() <= 2 && ed < fruits.size()) {
                if(freq.find(fruits[ed]) == freq.end()) {
                    curCnt++;
                }
                freq[fruits[ed]]++;
                ed++;
            }
            
            if(!stNotMov && ed != fruits.size()) {
                res = std::max(res, ed - st - 1);
            } else  {
                if(freq.size() == 3) {
                    res = std::max(res, ed - st - 1);
                } else {
                    res = std::max(res, ed - st);
                }
                
            }
            
            while(freq.size() > 2) {
                freq[fruits[st]]--;
                if(freq[fruits[st]] == 0) {
                    freq.erase(freq.find(fruits[st]));
                }
                ++st;
                stNotMov = false;
            }
        }
        return res;
    }
};
int main() {
    // vector<int> nums = {1, 15, 5, 11};
    // vector<int> nums = {1, 3};
    // vector<int> nums = {1, 3};
    int n = 2;
    vector<int> nums1d = {1, 0};
    vector<vector<int>> nums2d1 = {{1}, {0}};
    vector<vector<int>> nums2d2 = {
        {1,0}
    };
    Solution sl;
    std::cout << sl.totalFruit(nums1d) << std::endl;

    // std::cout << ios::left << std::setw(20) << "Hello, World!" << std::setw(5) << "a s " << 1 << std::endl;
    return 0;
}
