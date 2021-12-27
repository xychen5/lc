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
class StreamChecker {
public:
    class Trie{
    public:
        vector<Trie*> curLevel;
        bool isEnd = false;

        Trie() : curLevel(26) {}

        void insert(string& word) {
            Trie* curNode = this;
            int n = word.size();
            for(int i = n-1; i >= 0; --i) {
                char c = word[i] - 'a';
                if(nullptr == curNode->curLevel[c]) {
                    curNode->curLevel[c] = new Trie();
                }
                curNode = curNode->curLevel[c];
            }
            curNode->isEnd = true;
        }

        bool inTrie(string& word) {
            Trie* curNode = this;
            int n = word.size();
            for(int i = n-1; i >= 0; --i) {
                char c = word[i] - 'a';
                if(nullptr == curNode->curLevel[c]) {
                    return false;
                }
                if(curNode->curLevel[c]->isEnd) {
                    return true;
                }
                curNode = curNode->curLevel[c];
            }
            return curNode->isEnd;
        }

    };

    Trie* root;
    string curStr;

    StreamChecker(vector<string>& words) {
        root = new Trie();
        for(auto& w : words) {
            root->insert(w);
        }

        curStr = "";
    }
    
    bool query(char letter) {
        curStr += letter;
        return root->inTrie(curStr);
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