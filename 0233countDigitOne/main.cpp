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
    int countDigitOne(int n) {
        // brutle
        // string s = "";
        // for(long longi = 0; i <= n; ++i) {
        //     s += to_string(i);
        // }
        // long longres = 0;
        // for(long longi = 0; i < s.length(); ++i) {
        //     res += (int)(s[i] == '1');
        // }
        // return res;

        // using map to optimize: failed
        long long res = 0;
        // long longlim = 1000000;
        // for(long longi = 0; i <= n; ++i) {
        //     long longtmp = i;
        //     long longtmpRes = 0;

        //     while(tmp > 0) {
        //         tmpRes += (int)((tmp%10) == 1);
        //         tmp = tmp/10;
        //         if(tmp < 1000000){
        //             auto it = hash.find(tmp);
        //             if(it != hash.end()) {
        //                 tmpRes += it->second;
        //                 break;
        //             }
        //             else{
        //                 long longtmp2 = tmp;
        //                 long longtmpRes2 = 0;
        //                 while(tmp2 > 0) {
        //                     tmpRes2 += (int)((tmp2%10) == 1);
        //                     tmp2 = tmp2/10;
        //                 }
        //                 hash[tmp2] = tmpRes2;
        //                 tmpRes += tmpRes2;
        //                 break;
        //             }
        //         }
        //     }
        //     res += tmpRes;
        // }

        // respective compute each decimal bit's conditions and sum them
        long long curDecimalBitConditions = 1;
        long long ori = n;
        while(n > 0) {
            long long bit = n%10;
            n = n/10;
            if(bit == 0) {
                res += (1 + n - 1) * curDecimalBitConditions;
            }
            else if (bit == 1) {
                res += (1 + n - 1) * curDecimalBitConditions + ori % curDecimalBitConditions  + 1;
            } else {
                res += (1 + n) * curDecimalBitConditions;
            }

            // if(n > 0) {
            //     res += ((int)(bit >= 1) + n) * curDecimalBitConditions;
            // } else {
            //     res += ((int)(bit >= 1))
            // }


            curDecimalBitConditions *= 10;
        }
        return res;
    }
private:
    unordered_map<int, int> hash;
};


int main() {
     // vector<int> nums = {1, 15, 5, 11};
    // vector<int> nums = {1, 3};
    // vector<int> nums = {1, 3};
    vector<int> nums = {1, 2, 2, 3};
    Solution sl;
    std::cout << sl.countDigitOne(131232) << std::endl;
    return 0;
    // std::cout << ios::left << std::setw(20) << "Hello, World!" << std::setw(5) << "a s " << 1 << std::endl;
}
