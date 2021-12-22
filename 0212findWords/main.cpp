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
        bool hasNext = true;
        Trie() : curLevel(26) {
        }

        void insert(string word) {
            Trie* curNode = this;
            for(char c : word) {
                c -= 'a';
                if(nullptr == curNode->curLevel[c]) {
                    curNode->curLevel[c] = new Trie();
                }
                curNode = curNode->curLevel[c];
                curNode->hasNext = true;
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

        bool endWith(string word) {
            Trie* curNode = this;
            for(char c : word) {
                c -= 'a';
                if(nullptr == curNode->curLevel[c]) {
                    return false;       
                }
                curNode = curNode->curLevel[c];
            }
            return !curNode->hasNext;
        }
    };

    
    vector<string> findWords(vector<vector<char>>& board, vector<string>& words) {
        int m = board.size();
        int n = board[0].size();
        
    
        
        // build trie in normal or reverse order
        // std::shared_ptr<Trie> treeNormal = make_shared<Trie>();
        Trie* treeNormal = new Trie();
        // std::unique_ptr<Trie> treeReverse = new Trie();
        for(auto w : words) {
            treeNormal->insert(w);
            // treeReverse.insert(reverse(w.begin(), w.end()));
        }

        int deltaX[] = {1, 0, -1, 0};
        int deltaY[] = {0, 1, 0, -1};
        // get the answer
        vector<string> res;
        unordered_set<string> hash;
        for(int i = 0; i < board.size(); ++i) {
            for(int j = 0; j < board[0].size(); ++j) {
                // std::cout << "check next st point!" << endl;
                string tmpRes = "";
                vector<vector<bool>> exploredFlag(m, vector<bool>(n, false));
                backTrack(i, j, board, tmpRes, res, treeNormal,
                    deltaX, deltaY, exploredFlag, hash
                );
            }
        }
        return res;
    }


/**
[["o","a","a","n"],
 ["e","t","a","e"],
 ["i","h","k","r"],
 ["i","f","l","v"]]
["oath","pea","eat","rain","oathi","oathk","oathf","oate","oathii","oathfi","oathfii"]
**/
    void backTrack(int i, int j, vector<vector<char>>& board, string& tmpRes, vector<string>& res, Trie* curNode, 
    const int* deltaX, const int* deltaY,
    vector<vector<bool>>& exploredFlag,
    unordered_set<string>& hash) {
        char ch = board[i][j];
        if(nullptr == curNode->curLevel[ch - 'a']) {
            return ;
        }

        // start from i, j
        tmpRes.push_back(board[i][j]);
        // Trie* lastNode = curNode;
        curNode = curNode->curLevel[ch - 'a'];
        if(nullptr == curNode) {
            cout << "a???" << endl;
            return ;
        }
        
        // cout << "start : in " << i << "->" << j << " " << board[i][j] << "with tmpRes : " << tmpRes << endl;
        // we check the tmpRes directly using the trie
        // if(tree->inTrie(tmpRes) && 0 == hash.count(tmpRes)) {
        //     res.emplace_back(tmpRes);
        //     hash.insert(tmpRes);
        //     if(tree->endWith(tmpRes)) {
        //         tmpRes.pop_back();
        //         return;
        //     }
        // }
        if(nullptr != curNode && curNode->isEnd == true && 0 == hash.count(tmpRes)) {
            // cout << "find! >>>>> " << tmpRes << endl;
            res.emplace_back(tmpRes);
            hash.insert(tmpRes);
            if(!curNode->hasNext) {
                tmpRes.pop_back();
                return;
            }
        }

        // cout << "current[i, j] : in " << i << "->" << j << " " << board[i][j] << "with tmpRes : " << tmpRes << endl;
        exploredFlag[i][j] = true;
        if(nullptr != curNode) {
            // not null
            for(int mvIdx = 0; mvIdx < 4; ++mvIdx) {
                int nextX = i + deltaX[mvIdx];
                int nextY = j + deltaY[mvIdx];
                // cout << "tryStart: [x, y] :" << nextX << " " << nextY << endl;;
                if( nextX < board.size() && nextX >= 0 && nextY < board[0].size() && nextY >= 0 && \
                    ! exploredFlag[nextX][nextY]) {
                    backTrack(nextX, nextY, board, tmpRes, res, curNode,
                        deltaX, deltaY, exploredFlag, hash
                    );
                }
                // cout << "tryFinish: [x, y] :" << nextX << " " << nextY << endl;;
            }
        }
        exploredFlag[i][j] = false;
        tmpRes.pop_back();
    }

    // OLD WAY TO DO, will exceed the time limitation
    // void backTrack(int i, int j, vector<vector<char>>& board, string& tmpRes, vector<string>& res, unique_ptr<Trie>& tree, 
    // const int* deltaX, const int* deltaY,
    // vector<vector<bool>>& exploredFlag,
    // unordered_set<string>& hash) {

    //     // start from i, j
    //     tmpRes.push_back(board[i][j]);
        
    //     // cout << "start : in " << i << "->" << j << " " << board[i][j] << "with tmpRes : " << tmpRes << endl;
    //     if(tree->inTrie(tmpRes) && 0 == hash.count(tmpRes)) {
    //         res.emplace_back(tmpRes);
    //         hash.insert(tmpRes);
    //         if(tree->endWith(tmpRes)) {
    //             tmpRes.pop_back();
    //             return;
    //         }
    //     }


    //     // cout << "current[i, j] : in " << i << "->" << j << " " << board[i][j] << "with tmpRes : " << tmpRes << endl;
    //     exploredFlag[i][j] = true;
    //     if(tree->startWith(tmpRes)) {
    //         for(int mvIdx = 0; mvIdx < 4; ++mvIdx) {
    //             int nextX = i + deltaX[mvIdx];
    //             int nextY = j + deltaY[mvIdx];
    //             if( nextX < board.size() && \
    //                 nextX >= 0 && \
    //                 nextY < board[0].size() && \
    //                 nextY >= 0 && \
    //                 ! exploredFlag[nextX][nextY]) {
    //                 backTrack(nextX, nextY, board, tmpRes, res, tree,
    //                     deltaX, deltaY, exploredFlag, hash
    //                 );
    //             }
    //             // cout << "tryFinish: [x, y] :" << nextX << " " << nextY << endl;;
    //         }
    //     }
    //     exploredFlag[i][j] = false;
    //     tmpRes.pop_back();
    //     // cout << "current[i, j] : exit " << i << "->" << j << " " << board[i][j] << "with tmpRes : " << tmpRes << endl;
    // }
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