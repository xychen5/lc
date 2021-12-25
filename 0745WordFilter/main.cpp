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
class WordFilter {
public:
    // containning suffix
    class Trie {
    public:
        vector<Trie*> curLevel;
        int idx = -1;
        Trie() : curLevel(27) {}

        void insert(string& word, int idx, int left, int right) {
            Trie* curNode = this;
            for(int i = left; i < right; ++i) {
                char c = word[i];
                c = (c == '#' ? 26 : c - 'a');
                if(nullptr == curNode->curLevel[c]) {
                    curNode->curLevel[c] = new Trie();
                }
                curNode = curNode->curLevel[c];
                curNode->idx = idx;
            }
            curNode->idx = idx;
        }

        int startWith(string& word) {
            Trie* curNode = this;
            int lastIdx = -1;
            for(auto c : word) {
                // cout << "checking char: " << c << endl;
                c = (c == '#' ? 26 : c - 'a');
                if(nullptr == curNode->curLevel[c]) {
                    return -1;
                }
                curNode = curNode->curLevel[c];
            }
            return curNode->idx;
        }
    };

    public:
        Trie* tree;


    WordFilter(vector<string>& words) {
        tree = new Trie();
        for(int wIdx = 0; wIdx < words.size(); ++wIdx) {
            int n = words[wIdx].size();
            string word = words[wIdx] + "#" + words[wIdx];
            for(int j = 0; j <= n - 1; ++j) {
                // string tmp = word.substr(j);
                // overwrite those who start with a same suffix and prefix
                // cout <<"insert : " << tmp << endl;
                tree->insert(word, wIdx, j, 2*n +1);
            }
        }
    }
    
    int f(string prefix, string suffix) {
        int ans = -1;
        string tmp = suffix + "#" + prefix;
        // cout << "target >> " << tmp << endl;
        return tree->startWith(tmp);

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