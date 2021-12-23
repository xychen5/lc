## 0472. 连接词

### 1 题目
[https://leetcode-cn.com/problems/concatenated-words/](https://leetcode-cn.com/problems/concatenated-words/)

### 2 解题思路
- 1 首先很容易想到一点：
  - 1.1 由于需要快速定位一个单词是否在字典里，则采用字典树获取该信息
  - 1.2 对于一个单词，我们对于每个isEnd(也就是搜索前缀对应的单词在字典里)的位置，都从下一个字符从新开始在字典中匹配，然后每个isEnd位置后面的字符，需要继续匹配，eg：[cat, cats, catsdog, dog]，对于catsdog，从sdog和dog分别重新匹配
  - 1.3 对于一个单词，它的构成成分比他小，于是将字符串排序，一边插入，一边找
- 2 通过后缀记忆剪枝dfs, eg: 对于["a", "aa", "aaaa", "aaaakaa"]中的aaaakaa，运行代码会有如下日志：
  - 因为在第一次 a,a,a,a,k的时候记录了k位置往后的后缀无法成功匹配
  - 那么对于后面的 aa,a,a,k以及aaa,a,k等等搜索都会直接跳过k后缀的匹配
```py
when checking : aaaakaa the sufix start from pos : 4 has been validated to be failure!
when checking : aaaakaa the sufix start from pos : 3 has been validated to be failure!
when checking : aaaakaa the sufix start from pos : 2 has been validated to be failure!
when checking : aaaakaa the sufix start from pos : 4 has been validated to be failure!
```

```cpp
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
```
