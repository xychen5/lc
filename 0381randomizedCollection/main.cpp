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
class RandomizedCollection {
public:
    vector<int> nums;
    int curLen = 0;
    unordered_map<int, multiset<int>> numToIndices;
    RandomizedCollection() {
        nums.resize(200000, 0);
    }
    
    bool insert(int val) {
        nums[curLen++] = val;
        if(numToIndices.count(val) == 0) {
            numToIndices[val] = {curLen - 1};
        } else {
            numToIndices[val].insert(curLen - 1);
        }
        
        return numToIndices[val].size() == 1;
    }
    
    bool remove(int val) {
        if(numToIndices.count(val) != 0 && numToIndices[val].size() != 0) {
            int rmIdx = *(numToIndices[val].begin());
            numToIndices[val].erase(rmIdx);
            nums[rmIdx] = nums[curLen - 1];
            numToIndices[nums[curLen - 1]].insert(rmIdx); // avoid rmIdx == curLen - 1
            numToIndices[nums[curLen - 1]].erase(curLen - 1);
            curLen--;
            
            return true;
        }
        return false;
    }
    
    int getRandom() {
        int st = 0;
        int ed = curLen;
        int randIdx = rand() % (ed - st) + st;
        return nums[randIdx];
    }
};

/**
 * Your RandomizedCollection object will be instantiated and called as such:
 * RandomizedCollection* obj = new RandomizedCollection();
 * bool param_1 = obj->insert(val);
 * bool param_2 = obj->remove(val);
 * int param_3 = obj->getRandom();
 */
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