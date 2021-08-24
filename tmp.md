# xxx

## 1 题目描述

## 2 解题思路

## 3 often main
```cpp
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

    std::string str = "()(()())()(";

    Solution sl;
    std::cout << sl.triangleNumber(nums) << std::endl;
    
    // std::cout << ios::left << std::setw(20) << "Hello, World!" << std::setw(5) << "a s " << 1 << std::endl;
    return 0;
}
```


# todo: 
## 1 data structure: 
- 1 monostack: [https://leetcode-cn.com/problems/largest-rectangle-in-histogram/submissions/](https://leetcode-cn.com/problems/largest-rectangle-in-histogram/submissions/)
- 2 union stack:[https://leetcode-cn.com/problems/redundant-connection](https://leetcode-cn.com/problems/redundant-connection)
- 3 std::list的片段节选是链表维护的
- 4 左值: &&, list的move构造函数
