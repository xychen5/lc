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

    int maxChunksToSorted(vector<int>& arr) {
        // monoStack: every ele in mono represent: the biggest value in a chunk
        vector<int> mono = {INT_MIN}; // from small to bigger
        int n = arr.size();
        for(int i = 0; i < n; ++i) {
            if(arr[i] >= mono.back()) {
                mono.emplace_back(arr[i]);
            }  else { // arr[i] < mono.back()
                // merge the chunk untill arr[i] > mono.back()
                int curChunkMax = mono.back();
                while(mono.back() > arr[i]) {
                    mono.pop_back();
                }
                mono.emplace_back(curChunkMax);
            }
        }
        
        return mono.size() - 1;
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