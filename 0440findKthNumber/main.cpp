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
    class Trie {
    public:
        vector<Trie*> curLevel;
        bool isEnd = false;

        Trie() : curLevel(26){}

        void insert(string word ) {
            Trie* curNode = this;
            for(char c : word) {
                c -= 'a';
                if(nullptr == curNode->curLevel[c]) {
                    curNode->curLevel[c] = new Trie();
                }
                curNode = curNode->curLevel[c];
            }
            curNode->isEnd = true;
        }

        bool inTrie(string word) {
            Trie* curNode = this;
            for(char c : word) {
                c -= 'a';
                if(nullptr == curNode->curLevel[c]) {
                    return false;
                }
                curNode = curNode->curLevel[c];
            }
            return curNode->isEnd;
        }

        bool startWith(string word) {
            Trie* curNode = this;
            for(char c : word) {
                c -= 'a';
                if(nullptr == curNode->curLevel[c]) {
                    return false;
                }
                curNode = curNode->curLevel[c];
            }
            return true;
        }
    };



    vector<string> wordBreak(string s, vector<string>& wordDict) {
        // implement a trie to sort the word Dict
        Trie* tree = new Solution::Trie();
        for(string s : wordDict) {
            tree->insert(s);
        }

        vector<string> tmpRes;
        vector<vector<string>> res;
        backTrack(s, tmpRes, res, tree);

        vector<string> finalRes;
        for(auto& strVec : res) {
            string resItem = "";
            for(auto& str : strVec) {
                resItem += (str + " ");
            }
            finalRes.emplace_back(resItem.substr(0, resItem.size() - 1));
        }
        return finalRes;
    }

    void backTrack(string s, vector<string> tmpRes, vector<vector<string>>& res, Trie* trie) {
        if(0 == s.size()) {
            res.emplace_back(tmpRes);
        }
        // try every possibility
        for(int i = 0; i < s.size(); ++i) {
            string headWord = s.substr(0, i + 1);
            tmpRes.emplace_back(headWord);
            // cout << "head -> " << headWord << endl;
            if(trie->inTrie(headWord)) {
                // cout << "in it!" << endl;
                backTrack(s.substr(i + 1), tmpRes, res, trie);
            }
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
    // Solution sl;
    // std::cout << sl.medianSlidingWindow(nums1d, 3) << std::endl;

    // std::cout << ios::left << std::setw(20) << "Hello, World!" << std::setw(5) << "a s " << 1 << std::endl;
    return 0;
    std::cout << "Hello World!\n";
}