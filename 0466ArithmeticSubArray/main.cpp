// class Solution {
// public:
//     int numberOfArithmeticSlices(vector<int>& nums) {
//         if(nums.size() <= 2) {
//             return 0;
//         }
//         // sort
//         // sort(nums.begin(), nums.end(), [](int a, int b){return a < b;});
// 
//         // get all arithemetic slices length and sum it
//         int curItv = 0;
//         bool interupted = true;
//         int curLen = 0;
//         int res = 0;
//         for(int i = 1; i < nums.size(); ++i) {
//             if(interupted) {
//                 curItv = nums[i] - nums[i-1];
//                 curLen = 2;
//                 interupted = false;
//                 continue;
//             }
//             if(nums[i] - nums[i-1] == curItv) {
//                 curLen++;
//             } else {
//                 --i;
//                 res += subSlicesNum(curLen, curItv);
//                 interupted = true;
//             }
//         }
//         res += subSlicesNum(curLen, curItv);
//         return res;
//     }
// 
//     int subSlicesNum(int n, int itv) {
//         if(n <= 2) {
//             return 0;
//         }
//         int res = 0;
//         if(itv != 0) {
//             res = ((n-2) * (n-1))/2;
//             // 
//             int k = 1; // the delete one part length
//             while( n % (k+1) + n / (k+1) >= 3) { // the vector after del must have at least 3 elem
//                 int redundantNum = n % (k+1);
// 
//                 if( n % (k+1) == 0) { // the ori length became: ori = ori / (k+1)
//                     res += ((n/(k+1)-2) * (n/(k+1)-1))/2 * (k+1);
//                 }
//                 else if( n % (k+1) == 1) {
//                     // res += ((n/(k+1)-1) * (n/(k+1)-0))/2 - 1; // with redundant one
//                     res += n/(k+1) + 1 - 2; // with redundant one
//                     res += (k+1) * ((n/(k+1)-2) * (n/(k+1)-1))/2;
//                 }
//                 else {
//                     res += (n%(k+1)) * ((n/(k+1)-1) * (n/(k+1)-0))/2; // left part
//                     //                         here: the del part no covered by the left part
//                     res += (n/(k+1) >= 3) ? (k+1 - n%(k+1)) * ((n/(k+1)-2) * (n/(k+1)-1))/2 : 0; // del part
//                     // res += (redundantNum + (k + 1)) * ((n/(k+1)-1) * (n/(k+1)-0))/2;
//                     // for(int r = redundantNum; r > 0; --r){
//                     //     // if(k==1) {
//                     //     //     res += ((n/(k+1)-1) * (n/(k+1)-0))/2; // left part
//                     //     //     res += ((n/(k+1)-2) * (n/(k+1)-1))/2; // del part
//                     //     // }else {
//                     //         res += r * ((n/(k+1)-1) * (n/(k+1)-0))/2;
//                     //     // }
//                     // }
//                 }
//                 ++k;
//             }
//         } else {
//             res = 1;
//             for(int i = 1; i < n - 2; ++i) {
//                 res += frac(n) / frac(n-i) / frac(i);
//             }
//         }
//         return res;
//     }
// 
//     // n!
//     int frac(int n) {
//         int res = 1;
//         while(n!=0) {
//             res *= n;
//             --n;
//         }
//         return res;
//         // if(n = 1) {
//         //     return m;
//         // }
//         // if (n%2 == 0) {
//         //     return frac(m, n/2) * frac(m, n/2);
//         // } else {
//         //     return frac(m, n/2) * frac(m, n/2) * m;
//         // }
//     }
// };

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
    int numberOfArithmeticSlices(vector<int> &nums) {
        int ans = 0;
        int n = nums.size();
        vector<unordered_map<long long, int>> m(n);
        for(int i = 0; i < n; ++i) {
            for(int j = 0; j < i; ++j) {
                long long d = (long long)nums[i] - nums[j];
                auto it = m[j].find(d);
                int cnt = ((it == m[j].end()) ? 0 : it->second);
                ans += cnt;
                m[i][d] = m[i][d] + cnt + 1;
            }
        }
        return ans;
    }
};

int main() {
    // vector<int> nums = {1, 15, 5, 11};
    // vector<int> nums = {1, 3};
    // vector<int> nums = {1, 3};
    vector<int> nums = {1, 2, 2, 3};
    Solution sl;
    std::cout << sl.numberOfArithmeticSlices(nums) << std::endl;

    // std::cout << ios::left << std::setw(20) << "Hello, World!" << std::setw(5) << "a s " << 1 << std::endl;
    return 0;
}