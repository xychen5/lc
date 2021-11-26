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
    string longestSubsequenceRepeatedK(string s, int k) {
        // 找出大于等于k的字符记作kSet
        int n = s.size();

        vector<int> cnt(26, 0);
        // vector<bool> vis(26, false); 
        vector<char> dq;
        for(int i = 0; i < n; ++i) {
            int charNo = s[i]-'a';
            ++cnt[charNo];
            // if(cnt[charNo] == k && !vis[charNo]) {
            if(cnt[charNo] % k == 0) {
                dq.push_back(s[i]);
                // vis[charNo] = true;
            }
        }

        // 将kSet按照逆序字典序排序
        auto cmp = [](char a, char b) {return a > b;};
        sort(dq.begin(), dq.end(), cmp);

            // string tmp = "";
            // for(char& c : dq) tmp += c;
            // std::cout << "-d1 " << tmp << std::endl;


        // 找到第一个满足的最大长度为dq的字典序逆序的子序列的排列即为结果
        // 从子模式串的最大长度dq.size()一直遍历到1
        for(int len = dq.size(); len >= 1; --len) {
            // vector<char> tmp;
            // vector<vector<char>> res;
            // chooseN(dq, len, 0, res, tmp);
            string tmp;
            vector<string> res;
            chooseN2(dq, len, 0, res, tmp);

            // 构建出同len的所有permutaion，然后sort然后再来以此比较
            vector<string> sameLenStr;
            for(int i = 0; i < res.size(); ++i) {
                do {

                    // string tmp4 = "";
                    // for(char& c : res[i]) tmp4 += c;
                    // std::cout << "-d4 " << tmp4 << " with n = " << len <<std::endl;
                    sameLenStr.push_back(res[i]);
                }while(prev_permutation(res[i].begin(), res[i].end()));
            }
            sort(sameLenStr.begin(), sameLenStr.end(), [](string a, string b){return a > b;});
            
            // 看该子序列是否可以
            for(int subIdx = 0; subIdx < sameLenStr.size(); ++subIdx) {
                // do {
                // 构造seq*k
                string tmpDq;
                for(int i = 0; i < k; ++i) {
                    tmpDq += sameLenStr[subIdx];
                }

                // string tmp3 = "";
                // for(char& c : tmpDq) tmp3 += c;
                // std::cout << "-d3 " << tmp3 << " with n = " << tmpDq.size() <<std::endl;

                // 判断构造的seq*k是否存在于s中
                int tmpIdx = 0;
                int realIdx = 0;
                int cnt = 0;
                for(; tmpIdx < tmpDq.size(); ++tmpIdx) {
                    for(; realIdx < n; ++realIdx) {
                        if(s[realIdx] == tmpDq[tmpIdx]) {
                            ++cnt;
                            ++realIdx;
                            break;
                        }
                    }
                }

                
                if(cnt == tmpDq.size()) {
                    return sameLenStr[subIdx];
                }
                    
            }
        }
        return "";
    }

    void chooseN2(vector<char>& dq, int n, int st, vector<string>& res, string& tmpRes) {
        if(n == 0) {
            res.push_back(tmpRes);
            // std::cout << "-d2 " << tmpRes << " with n = " << tmpRes.size() <<std::endl;
            return;
        }
        for(int i = st; i < dq.size() - n + 1; ++i) {
            tmpRes.push_back(dq[i]);
            chooseN2(dq, n - 1, i + 1, res, tmpRes);
            tmpRes.pop_back();
        }
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
    Solution sl;
    // std::cout << sl.medianSlidingWindow(nums1d, 3) << std::endl;

    // std::cout << ios::left << std::setw(20) << "Hello, World!" << std::setw(5) << "a s " << 1 << std::endl;
    return 0;
    std::cout << "Hello World!\n";
}