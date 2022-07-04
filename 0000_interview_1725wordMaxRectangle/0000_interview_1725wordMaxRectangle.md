## 0000_interview_1725wordMaxRectangle 单词矩阵

### 1 题目
[https://leetcode.cn/problems/word-rectangle-lcci/](https://leetcode.cn/problems/word-rectangle-lcci/)

### 2 解题思路
- 1 解题思路:
  - 1.1 很显然回溯即可：对于所有的同长度的单词，用回溯实现任意的permutation，hori记录放置的单词，vert记录垂直的单词，一单vert构成的前缀不存在，说明当前单词需要从新选择，回溯的深度我们无须考虑，因为vert不成功我们就提前返回了，然而vert成功的最基本的就是，回溯深度不可能超过最长的单词。
  - 1.2 我们从最长的单词出发，这样我们能够尽早的获取更大面积的单词矩阵，然后利用这个面积结果去跳过那些不可能比当前结果大的长度的单词集合，比如，已经发现最大面积为12，然后我们搜索长度为2的单词可能的矩阵，然后最大单词长度为6，我们就不用搜了，因为2为长度的单词集合，最大带来的面积就是2 * 6 = 12，我们就可以直接跳过了。

```cpp
class Solution {
public:
    class Trie {
    public:
        vector<Trie*> curLevel;
        bool isEnd = false;
        Trie() : curLevel(26, nullptr) {
        }

        void buildTrie(vector<string>& words) {
            for(auto& w : words) {
                auto curNode = this;
                for(auto& c : w) {
                    if(nullptr == curNode->curLevel[c - 'a']) {
                        curNode->curLevel[c - 'a'] = new Trie();
                    }
                    curNode = curNode->curLevel[c - 'a'];
                }
                curNode->isEnd = true;
            }
        }

        bool preInTrie(string& w) {
            auto curNode = this;
            for(auto& c : w) {
                auto nextLevel = curNode->curLevel[c - 'a'];
                if(nullptr == nextLevel) {
                    return false;
                }
                curNode = nextLevel;
            }
            return true;
        }

        bool wordInTrie(string& w) {
            auto curNode = this;
            for(auto& c : w) {
                auto nextLevel = curNode->curLevel[c - 'a'];
                if(nullptr == nextLevel) {
                    return false;
                }
                curNode = nextLevel;
            }
            return curNode->isEnd;
        }

    };

    void ableToMakeRes(vector<string>& hori, vector<string>& vert) {
        // cout << "> hori.size() " << hori.size() << endl;
        if(0 == vert[0].size()) {
            // cout << "> vert empty: " << endl;
            return;
        }

        for(auto& v : vert) {
            if(!root->wordInTrie(v)) {
                // cout << "> word failed: " << v;
                return ;
            }
        }
        
        int curSquare = vert[0].size() * vert.size();
        // cout << "> curSquare: " << vert[0].size() * vert.size() << endl;
        // cout << "> finSquare: " << finSquare << endl;
        if(curSquare > finSquare) {
            // cout << "updated!\n";
            finSquare = curSquare;
            resVec = hori;
        }
    }

    // try all possible permutation of rect with width = w
    void backTrack(
        vector<string>& curWords,
        vector<string>& hori,
        vector<string>& vert,
        vector<string>& resVec
    ) {
        int width = curWords[0].size();
        // cur found square bigger then all possilbe res from curWords
        if(finSquare > width * maxWordLen) return;

        // check if we obtain a res
        ableToMakeRes(hori, vert);

        for(auto& word : curWords) {
            hori.push_back(word);
            int vertCnt = 0;
            bool failed = false;
            for(int i = 0; i < width; ++i) {
                vert[i].push_back(word[i]);
                ++vertCnt;
                if(!root->preInTrie(vert[i])) {
                    failed = true;
                    break;
                }
            }
            // cout << "trying: " << word << " | with hori = " << hori.size() << endl;
            
            if(!failed) {
                // cout << "choosing: " << word << endl;
                // next level
                backTrack(curWords, hori, vert, resVec);
            }

            // backTrack
            // cout << "failed on: " << word << endl;
            hori.pop_back();
            for(int i = 0; i < vertCnt; ++i) {
                vert[i].pop_back();
            }
        }

    }
    unique_ptr<Trie> root;
    int finSquare = INT_MIN;
    vector<string> resVec;

    int maxWordLen = -1;

    vector<string> maxRectangle(vector<string>& words) {
        root = make_unique<Trie>();
        root->buildTrie(words);

        map<int, vector<string>, std::greater<int>> lenWords;
        for(auto& w : words) {
            lenWords[w.size()].push_back(w);
            maxWordLen = max(maxWordLen, static_cast<int>(w.size()));
        }

        for(auto& [w, curWords] : lenWords) {
            vector<string> hori;
            vector<string> vert(w, "");
            // cout << "w is: " << w <<endl;
            backTrack(curWords, hori, vert, resVec);
        }
        return resVec;
    }
};
```