## 0140. 单词拆分 II

### 1 题目
[https://leetcode-cn.com/problems/word-break-ii/](https://leetcode-cn.com/problems/word-break-ii/)

### 2 解题思路
- 1 首先确定搜索思路：
  - 1.1 很显然这个问题的解答思路不会随着问题规模的减小而改变，于是采用递归/回溯方案 
  - 1.2 由于需要确认当前子问题处于什么位置，于是采用回溯
  - 1.3 回溯方法
    - 1.3.1 每次在头部尝试字符串headWord，直到找到**一个在字典里面的headWord**
    - 1.3.2 将原来字符串去掉headWord，然后递归到下一层
    - 1.3.3 当前的headWord的所有可能尝试完毕，则回溯到尝试headWord之前，然后去尝试下一个headWord
  - 1.4 以上可以看出回溯和递归的区别，递归不带有当前搜索状态，而回溯需要维持搜索状态
- 2 有了大体思路，那么如何解决: 找到**一个在字典里面的headWord**?
  - 2.1 采用字典前缀树即可快速获得该字符串是否在字典树里面，复杂度为O(m)，m为字典树中的
```cpp
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
```
