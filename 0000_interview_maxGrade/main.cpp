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

int main()
{
    // vector<int> nums = {1, 15, 5, 11};
    // vector<int> nums = {1, 3};
    // vector<int> nums = {1, 3};
    int n = 2;
    vector<int> nums1d = { 1, 0 };
    vector<vector<int>> nums2d1 = { {1}, {0} };
    vector<vector<int>> nums2d4 = { {1,1,3,3},{3,1,4,2},{3,2,4,4},{1,3,2,4},{2,3,3,4} };
    Solution sl;
    // std::cout << sl.medianSlidingWindow(nums1d, 3) << std::endl;

    // std::cout << ios::left << std::setw(20) << "Hello, World!" << std::setw(5) << "a s " << 1 << std::endl;
    return 0;
    std::cout << "Hello World!\n";
}