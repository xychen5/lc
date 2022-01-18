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

class Solution {
public:
    string smallestSubsequence(string s, int k, char letter, int repetition) {
        // first, using monostack to get the min sub arr whose len = k
        // and check if there are rep's 'letter' in sub arr
                
        clock_t start,end;　　　//定义clock_t变量
        start = clock();  　　　//开始时间

        string mono; // abscending chars
        int n = s.size();
        int specialCharCnt = 0;
        int avaliableSpeChar = 0;
        for(auto &c : s) {
            avaliableSpeChar += (c == letter);
        }


        for(int i = 0; i < n; ++i) {
            while(!mono.empty() && mono.back() > s[i] && mono.size() - 1 + n - i >= k) {
                if(mono.back() == letter) {
                    // when not enough special letter, we do not pop special char
                    if(avaliableSpeChar <= repetition - specialCharCnt) {
                        break;
                    }
                    --specialCharCnt;
                }
                mono.pop_back();
            }

            mono.push_back(s[i]);
            if(s[i] == letter) {
                --avaliableSpeChar;
                ++specialCharCnt;
            }
        }

        start = clock();  　　　//开始时间
        string res = "";
        // eliminate some extra chars reversely
        int delNum = mono.size() - k;
        // cout << "letter Cnt: " << specialCharCnt << endl;
        for(int i = mono.size() - 1; i >= 0; --i){
            // make sure there are more than rep's 'letter'
            if(delNum != 0 ) {
                if(specialCharCnt > repetition) {
                    specialCharCnt -= (mono[i] == letter);
                    --delNum;
                    continue;
                } else {
                    if(mono[i] != letter) {
                        --delNum;
                        continue;
                    }
                }
            }
            // spend: 0.311s
            // res = mono[i] + res; // this spend two much time, ocuppy nearly 100% time! so we change our policy
            // spend: 0.000153s, 1000 times faster!
            res.push_back(mono[i]);
        }

        reverse(res.begin(), res.end());
        end = clock();   //结束时间
        cout<<"time = "<<double(end-start)/CLOCKS_PER_SEC<<"s"<<endl;  //输出
        return res;
    }
};



int main() {
    // vector<int> nums = {1, 15, 5, 11};
    // vector<int> nums = {1, 3};
    // vector<int> nums = {1, 3};
    vector<int> nums = {1, 2, 2, 3};
    Solution sl;
    std::cout << sl.largestRectangleArea(nums) << std::endl;
    std::cout << "Hello, World!" << std::endl;
    return 0;
}
