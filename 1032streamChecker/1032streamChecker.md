## 1032. 字符流 StreamChecke

### 1 题目
[https://leetcode-cn.com/problems/stream-of-characters/](https://leetcode-cn.com/problems/stream-of-characters/)

### 2 解题思路
- 1 倒序建立搜索树即可，因为可以观察到，总是从字符流的倒序开始查询
``` cpp
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
 *
```
