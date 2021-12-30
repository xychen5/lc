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

    string getMaxConcat(vector<int>& longVec, vector<int>& shortVec, int lenInLonger, int lenInShorter) {
        string monoLong, monoShort;

        // choose biggest lenInLonger's subArr from  longer vec
        for(int i = 0; i < longVec.size(); ++i) {
            while(monoLong.size() > 0 && monoLong.back() - '0' < longVec[i] && monoLong.size() + longVec.size() - i > lenInLonger) {
                // cout << "pop_long: " << monoLong.back() << " monoLong's std len: " << lenInLonger << " curback: " << monoLong.back() << endl;
                monoLong.pop_back();
            }
            if(monoLong.size() < lenInLonger) {
                // cout << "push_long: in " << static_cast<char>(longVec[i] + '0') << endl;
                monoLong.push_back(static_cast<char>(longVec[i] + '0'));
            }
        }
        for(int i = 0; i < shortVec.size(); ++i) {
            // while(monoLong.back() < longVec[i] && monoLong.size() <= lenInLonger && monoLong.size() + longVec.size() - i + 1 < lenInLonger) {
            while(!monoShort.empty() && monoShort.back() - '0' < shortVec[i] && monoShort.size() + shortVec.size() - i > lenInShorter) {
                // cout << "pop_short: " << monoShort.back() << " monoLong's std len: " << lenInShorter << " curback: " << monoShort.back() << endl;
                monoShort.pop_back();
            }
            if(monoShort.size() < lenInShorter) {
                // cout << "push_short: in " << static_cast<char>(longVec[i] + '0') << endl;
                monoShort.push_back(static_cast<char>(shortVec[i] + '0'));
            }
        }

        int j = 0;
        // merger the two biggest substr,
        string finalRes = "";
        // cout << "longMax and shortMax str: " << monoLong << " " << monoShort << endl;
        for(int i = 0; i < monoShort.size(); ++i) {
            while(j < monoLong.size() && monoLong[j] > monoShort[i]) {
                finalRes.push_back(monoLong[j++]);
            }
            // decided whether to use long str or short when the char compared is true
            if(monoLong[j] == monoShort[i]) {
                if(monoLong.substr(j) > monoShort.substr(i)) {
                    finalRes.push_back(monoLong[j++]);
                    i--;
                    continue;
                }
            }
            finalRes.push_back(monoShort[i]);
        }
        finalRes += monoLong.substr(j);
        // cout << "finalRes string is: " << finalRes << endl;
        return finalRes;
    }

    vector<int> maxNumber(vector<int>& nums1, vector<int>& nums2, int k) {
        int m = nums1.size();
        int n = nums2.size();
        // cout << "m/n" << m << " " << n << endl;

        // let k split into nums1 and nums2
        string maxStr(k, '0');
        if(m <= n) {
            for(int lenInShorter = max(0, k - n); lenInShorter <= min(m, k); ++lenInShorter) {
                int lenInLonger = k - lenInShorter;
                // cout << "lenInLong/short" << lenInLonger << " " << lenInShorter << endl;
                string curMax = getMaxConcat(nums2, nums1, lenInLonger, lenInShorter);
                maxStr = maxStr > curMax ? maxStr : curMax;
            }
        } else {
            for(int lenInShorter = max(0, k - m); lenInShorter <= min(n, k); ++lenInShorter) {
                int lenInLonger = k - lenInShorter;
                string curMax = getMaxConcat(nums1, nums2, lenInLonger, lenInShorter);
                maxStr = maxStr > curMax ? maxStr : curMax;
            }
        }

        vector<int> res;
        for(auto& c : maxStr) {
            res.emplace_back(c - '0');
        }
        return res;
    }
};

/**
 * Your StreamChecker object will be instantiated and called as such:
 * StreamChecker* obj = new StreamChecker(words);
 * bool param_1 = obj->query(letter);
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