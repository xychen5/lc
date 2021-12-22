## 0212 单词搜索 II

### 1 题目
[https://leetcode-cn.com/problems/word-search-ii](https://leetcode-cn.com/problems/word-search-ii)

### 2 解题思路
- 1 要搜索整个字母棋盘，很自然想到使用回溯
- 2 要知道一个字符串是否在字典里，很自然想到trie
- 3 具体解答方法
  - 3.1 如下代码的注释的backTrack函数很清晰的阐述啦思路，称之为old way
  - 3.2 old way的缺陷，对于tmpRes的前面的公共部分反复调用啦startWith函数重复计算啦，
  - 3.3 改进，使用curNode记录tmpRes在前缀树里面的位置，那么只需要根据curNode来判断tmpRes即将加入的新的字符是否为curNode的子节点就可以啦，提升了速度
```cpp
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
```
