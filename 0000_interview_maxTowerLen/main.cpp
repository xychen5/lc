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

