## 0000_interview_subAddBinTree 加减二叉树

### 1 题目
[https://www.nowcoder.com/questionTerminal/39953c879b79412b85fbca2ffdeb0a4c?f=discussion](https://www.nowcoder.com/questionTerminal/39953c879b79412b85fbca2ffdeb0a4c?f=discussion)

### 2 解题思路
- 1 首先想到，每个叶子唯一确定一条路径，复杂度为O(2**k)
- 2 然后考虑，对于每一条路径，每个节点都可能加减，复杂度为O(2**k)
- 3 那么上面考虑的问题，错误的是2，因为对于一条路径而言，比如有如下树
  - 3.1 你需要注意到，每条路径最下面的节点比上面所有节点的和都要大，
  - 3.2 这个很好证明，因为2^k的数列和为2^(k+1) - 1,而最下面的数字为2^k，也就是，当你对于一条具体的路从叶子到根节点判断该节点是该增加还是减少的时候，叶子节点的影响力要大于路上其他所有之和，于是只需要判断当前节点对于总和的影响即可
  - 3.3 比如有6 ，3，路径长度为3，我们考虑5，2，1这条路，首先总和为6，容得下5，那么路径中的5加上去，则剩余总和为1，由于任然有空间，2也先放进去，剩余空间则为-1，对于1，早已经没有位置，则该数要减去，所以为 5+ 2+ 1-的过程
```cpp
1
2     3
4  5  6  7
```
```cpp
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
#include <cmath>

using namespace std;

int test2Dfs(long long n, int k, vector<long long>& path) {
    long long curNode = pow(2, k - 1);
    // start from leaf level
    for(; curNode < pow(2, k); ++curNode) {
        long long leftSum = n;
        long long lastCurNode = curNode;
        for(int level = k - 1; level >= 0; --level) {
            if(leftSum >= 0) {
                leftSum -= curNode;
                path[level] = curNode;
            } else {
                leftSum += curNode;
                path[level] = -curNode;
            }
            curNode /= 2;
        }
        
        // find a path
        if(0 == leftSum) {
            return 0;
        }
        curNode = lastCurNode;
    }
    return 0;
}

int main() {
    long long int n = 0;
    int k = 0;
    
    cin >> n >> k;
    vector<long long> path(k, 0);
    test2Dfs(n, k, path);
    
    for(int i = 0; i < k; ++i) {
        if(path[i] > 0) {
            cout << path[i] << " +" << endl;
        } else {
            cout << abs(path[i]) << " -" << endl;
        }
    }
    cout << "\n";

    
    return 0;
    
}

```