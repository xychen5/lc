## SH1 最高罗汉塔高度

### 1 题目
[https://www.nowcoder.com/practice/c2afcd7353f84690bb73aa6123548770?tpId=182&tqId=34688&rp=1&ru=/exam/oj&qru=/exam/oj&sourceUrl=%2Fexam%2Foj%3Ftab%3D%25E5%2590%258D%25E4%25BC%2581%25E7%25AC%2594%25E8%25AF%2595%25E7%259C%259F%25E9%25A2%2598%26topicId%3D182%26page%3D1&difficulty=undefined&judgeStatus=undefined&tags=&title=](https://www.nowcoder.com/practice/c2afcd7353f84690bb73aa6123548770?tpId=182&tqId=34688&rp=1&ru=/exam/oj&qru=/exam/oj&sourceUrl=%2Fexam%2Foj%3Ftab%3D%25E5%2590%258D%25E4%25BC%2581%25E7%25AC%2594%25E8%25AF%2595%25E7%259C%259F%25E9%25A2%2598%26topicId%3D182%26page%3D1&difficulty=undefined&judgeStatus=undefined&tags=&title=)

### 2 解题思路
- 1 解题思路：
  - 最关键的，了解到，本人上面只能站比自己矮比自己瘦的人，或者站完全一样的人，其实就是和俄罗斯套娃信封类似，首先按照weight增排序，然后按照height降排序，然后对height序列求最大增长子序列
  - dp[i] = max(dp[j] + 1, dp[i])，dp[i]代表以i为结尾的最大增序列的长度
- 2 **最为坑人的是，一定要直到牛客可能是很多个样例在一起输入！！！可以使用while(cin >> n)来判断是否输入完成！！！**

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
#include <string>

using namespace std;

int main()
{
    int n;
    while(cin >> n) {
        vector<vector<int>> persons(n, vector<int>(2, 0));

        for(int i = 0; i < n; ++i) {
            int tmp;
            cin >> tmp >> persons[i][0] >> persons[i][1];
        }

        if(n <= 1) {
            return 1;
        }

        sort(persons.begin(), persons.end(), [](const vector<int>& a, const vector<int>& b){
            return a[0] < b[0] || (a[0] == b[0] && a[1] > b[1]);
        });
        
        vector<int> dp(n, 1);
        int res = INT_MIN;
        for(int i = 0; i < n; ++i) {
            for(int j = 0; j < i; ++j) {
                if(persons[j][1] <= persons[i][1]) {
                    dp[i] = max(dp[j] + 1, dp[i]);
                    res = max(res, dp[i]);
                }
            }
        }
        cout << res << endl;
    }

    return 0;
}


```