## 0745WordFilter 前缀和后缀搜索
### 1 题目
[https://leetcode-cn.com/problems/prefix-and-suffix-search/](https://leetcode-cn.com/problems/prefix-and-suffix-search/)

### 2 解题思路
- 1 构建后缀拼接前缀树
  1.1 参考解释即可：
>   For a word like "test", consider "#test", "t#test", "st#test", "est#test", "test#test". Then if we have a query like prefix = "te", suffix = "t", we can find it by searching for something we've inserted starting with "t#te". 
``` cpp
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
```
