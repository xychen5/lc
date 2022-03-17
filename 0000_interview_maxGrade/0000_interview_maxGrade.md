## 0000_interview_maxGrade 最大成绩

### 1 题目
[https://www.nowcoder.com/questionTerminal/b83f4f4950d04154a6dc053b6d419782](https://www.nowcoder.com/questionTerminal/b83f4f4950d04154a6dc053b6d419782)

### 2 解题思路
- 1 动态规划： 最重要的是，首先将动态规划的目标改为，算出所有可能构成的分数，那么记：在nums[:i]这个成绩子集能否组成成绩j记作： sumOk[i][j] = (sumOk[i-1][j - num[i]]) or (sumOk[i][j] = sumOk[i][j] || sumOk[i - 1][j])，很容易有这个状态转移
- 2 然后我们可以发现，我们会将sumOK[i-1]的状态复制一份到sumOK[i]中，也就是我们可以缩少到1维


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
#include <set>
#include <string>
#include <thread>
#include <mutex>
#include <mutex>
using namespace std;
int main() {
    int n = 0;
    cin >> n;
    vector<int> nums(n, 0);
    int sum = 0;
    for(int i = 0; i < n; ++i) {
        cin >> nums[i];
        sum += nums[i];
    }
    
    vector<vector<bool>> sumOk(n, vector<bool>(sum + 1, false));
    
    sumOk[0][0] = 1;
    sumOk[n - 1][sum] = 1;
    for(int i = 0; i < n; ++i) {
        sumOk[i][nums[i]] = true;
    }
    
    // sumOk[i][j] = sumOk[i-1][j - num[i]] or sumOk[i][j] = sumOk[i][j] || sumOk[i - 1][j];
    // can reduce to one dimension
    for(int i = 1; i < n; ++i) {
        for(int j = 0; j < sum; ++j) {
            if(j > nums[i]) {
                sumOk[i][j] = sumOk[i-1][j - nums[i]];
            }
            sumOk[i][j] = sumOk[i][j] || sumOk[i - 1][j];
        }
    }
    
    for(int j = sum; j >= 0; --j) {
        if(sumOk[n - 1][j]) {
            bool can = true;
            int tar = j;
            while (tar > 0) {
                int bit = tar % 10;
                tar /= 10;
                if (5 == bit) {
                    can = false;
                }
            }

            if (can) {
                cout << j << endl;
                return 0;
            }
        }
    }
    return 0;
}


```