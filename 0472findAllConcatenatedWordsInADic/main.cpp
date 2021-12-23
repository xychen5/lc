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
    class Trie{
    public: 
        vector<Trie*> curLevel;
        bool isEnd = false;
        // bool hasNext = false;

        Trie() : curLevel(26) {

        }

        void insert(string& s, int idx) {
            // cout << "inserting : " << s << endl;
            Trie* curNode = this;
            for(auto c : s) {
                c -= 'a';
                if(nullptr == curNode->curLevel[c]) {
                    curNode->curLevel[c] = new Trie();
                }

                curNode = curNode->curLevel[c];
                // curNode->hasNext = true;
            }
            curNode->isEnd = true;
        }
    };

    vector<string> findAllConcatenatedWordsInADict(vector<string>& words) {
        int n = words.size();
        Trie* tree = new Trie();
        
        // build trie
        int idx = 0;

        sort(words.begin(), words.end(), [](string& a, string& b){
            return a.size() < b.size();
        });

        vector<string> ans;


        for(auto w : words) {
            // cout << "-------checking " << w << endl;
            // bool ableToConnect = false;
            // findMaxConnectedCnt(w, 0, tree, 0, ableToConnect);
            // if(ableToConnect ) {
            //     ans.emplace_back(w);
            // }
            vector<bool> trap(w.size(), false);
            if(dfsToCheck(w, 0, tree, 0, trap)) {
                ans.emplace_back(w);
            }
            tree->insert(words[idx], idx);
            ++idx;
        }

        return ans;
    }

    // here we search all the possible ways, but we only need one possible way, so we need return early
    void findMaxConnectedCnt(string& s, int pos, Trie* root, int curCnt, bool& ableToConnect) {

        if(s.size() == pos) {
            if(curCnt >= 2) {
                ableToConnect = true;
            }
            // cout << "<<<<<< finish one!"  << endl;
            return ;
        }
        
        int curPos = pos;
        Trie* curNode = root;
        while(curPos < s.size()) { // serach all prefix
            int ch = s[curPos] - 'a';
            if(nullptr != curNode->curLevel[ch]) {
                if(curNode->curLevel[ch]->isEnd) {
                    // cout << ">>>>> curPos: " << curPos << " char is " << s[curPos] << " dive with curCnt: " << curCnt << endl;
                    // using this or next end
                    findMaxConnectedCnt(s, curPos + 1, root, curCnt + 1, ableToConnect);
                }
            } else {
                return;
            }
            // cout << "curPos: " << curPos << " char is " << s[curPos] << " with curCnt: " << curCnt << endl;
            curNode = curNode->curLevel[ch];
            ++curPos;
        }
    }

    bool dfsToCheck(string& s, int pos, Trie* root, int curCnt, vector<bool>& trap) {

        if(s.size() == pos) {
            return curCnt >= 2;
        }

        if(trap[pos]) {
            cout << "when checking : " << s << " the sufix start from pos : " << pos << " has been validated to be failure!" << endl;
            return false;
        }
        
        int curPos = pos;
        Trie* curNode = root;
        while(curPos < s.size()) { // serach all prefix
            int ch = s[curPos] - 'a';
            if(nullptr != curNode) {
                if(nullptr != curNode->curLevel[ch]) {
                    if(curNode->curLevel[ch]->isEnd) {
                        // cout << ">>>>> curPos: " << curPos << " char is " << s[curPos] << " dive with curCnt: " << curCnt << endl;
                        // using this or next end
                        if(dfsToCheck(s, curPos + 1, root, curCnt + 1, trap)) {
                            return true;
                        }
                    }
                }
            } else {
                break;
            }
            
            // cout << "curPos: " << curPos << " char is " << s[curPos] << " with curCnt: " << curCnt << endl;
            curNode = curNode->curLevel[ch];
            ++curPos;
        }
        
        trap[pos] = true;
        return false;
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