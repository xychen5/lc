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
class Trie {
public:
    vector<Trie *>curLevel;
    bool isEnd = false;

    Trie() : curLevel(26) {
        
    }

    void insert(string word) {
        Trie * curNode = this;
        for(char c : word) {
            c -= 'a';
            if(nullptr == curNode->curLevel[c]) {
                curNode->curLevel[c] = new Trie();
            } 
            // check nextLevel
            curNode = curNode->curLevel[c];
        }
        curNode->isEnd = true;
    }
    
    bool search(string word) {
        Trie * curNode = this;
        for(char c : word) {
            c -= 'a';
            if(nullptr == curNode->curLevel[c]) {
                return false;
            }
            curNode = curNode->curLevel[c];
        }
        return curNode->isEnd;
    }
    
    bool startsWith(string prefix) {
        Trie * curNode = this;
        for(char c : prefix) {
            c -= 'a';
            if(nullptr == curNode->curLevel[c]) {
                return false;
            }
            curNode = curNode->curLevel[c];
        }
        return true;
    }
};

/**
 * Your Trie object will be instantiated and called as such:
 * Trie* obj = new Trie();
 * obj->insert(word);
 * bool param_2 = obj->search(word);
 * bool param_3 = obj->startsWith(prefix);
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