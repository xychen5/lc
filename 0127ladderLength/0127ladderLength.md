## 0127ladderLength 单词接龙

### 1 题目
[https://leetcode-cn.com/problems/word-ladder/](https://leetcode-cn.com/problems/word-ladder/)

### 2 解题思路
- 1 解题思路：
  - 首先，我们构建字典，记单词长度为n，对于从beginword出发，我们首先得选择改变beginword的第i位，这个对应到字典树里就是第i层，那么第i为的选择为词汇树第i层的节点数目，可以将beginword的每一位改变(每一位改变就有很多种)之后记为单词tmp，用字典树检测是否在树里，在的话才会放入nextLevel，对于nextLevel的每一个单词，然后用对beginword同样的方法找到下一个nextLevel，bfs嘛


```cpp
class Solution {
public:

    class DictTree {
    public:
        vector<DictTree*> level;
        bool isEnd = false;
        DictTree(): level(26, nullptr) {}
    };

    bool wordInTree(string& a, DictTree* root) {
        DictTree* curLevel = root;
        for(auto& c : a) {
            if(curLevel->level[c - 'a'] != nullptr) {
                curLevel = curLevel->level[c - 'a'];
            } else {
                // cout << a << " not in tree!" << endl;
                return false;
            }
        }
        cout << a << " in tree!" << endl;
        return true;
    }

    DictTree* construct(vector<string>& wordList) {
        DictTree* level = new DictTree();
        for(auto& word : wordList) {
            DictTree* curLevel = level;
            int levelCnt = 0;
            for(auto& c : word) {
                if(nullptr == curLevel->level[c - 'a']) {
                    curLevel->level[c - 'a'] = new DictTree();
                } 
                curLevel = curLevel->level[c - 'a'];
                levelChars[levelCnt++].insert(c);
            }
            curLevel->isEnd = true;
        }
        return level;
    }


    DictTree* tree;
    vector<unordered_set<char>> levelChars;
    string endWord = "";
    int n = -1;

    int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
        n = beginWord.size();
        levelChars.resize(n, {});
        tree = construct(wordList);

        int res = INT_MAX;
        
        if(!wordInTree(endWord, tree)) {
            return 0;
        }

        this->endWord = endWord;
        vector<bool> usedPos(beginWord.length(), false);
        deque<string> curTryLevel = {beginWord};
        int chainLen = 1;
        set<string> tryPath;
        bfsGetLadLen(levelChars, curTryLevel, tryPath, chainLen);

        return chainLen == -1 ? 0 : chainLen;
    }

    int bfsGetLadLen(
        vector<unordered_set<char>>& levelChars, 
        deque<string>& curTryLevel, 
        set<string>& tryPath,
        int& chainLen)
    {


        if(tryPath.find(endWord) != tryPath.end()) {
            return chainLen;
        }

        if(curTryLevel.size() == 0) {
            chainLen = -1;
            return chainLen;
        }

        deque<string> nextTryLevel;
        while(!curTryLevel.empty()) {
            string str = curTryLevel.front();
            curTryLevel.pop_front();

            for(int l = 0; l < levelChars.size(); ++l) {
                for(const char& c : levelChars[l]) {
                    string tmp = str;
                    if(tmp[l] == c) {
                        continue;
                    }
                    tmp[l] = c;
                    if(tryPath.find(tmp) == tryPath.end() && wordInTree(tmp, tree)) {
                        // cout << "success: " << tmp << endl;
                        nextTryLevel.push_back(tmp);
                        tryPath.insert(tmp);
                    }
                }
            }
        }

        // cout << "------------------- " << endl;
        chainLen++;
        // cout << "chainLen " << chainLen << endl;
        return bfsGetLadLen(levelChars, nextTryLevel, tryPath, chainLen);
    }

};
```