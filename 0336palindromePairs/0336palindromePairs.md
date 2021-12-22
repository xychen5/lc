## 0336. 回文对

### 1 题目
[

### 2 解题思路
- 1 参考官方解答：****
```cpp
class Solution {
public:
    class Trie {
    public:
        vector<Trie*> curLevel;
        bool isEnd = false;
        int wordIdx = -1;
        Trie() : curLevel(26), wordIdx(-1) {

        }
        void insert(string& word, int idx) {
            Trie* curNode = this;
            for(auto c : word) {
                c -= 'a';
                if(nullptr == curNode->curLevel[c]) {
                    curNode->curLevel[c] = new Trie();
                }
                curNode = curNode->curLevel[c];
            }
            curNode->isEnd = true;
            curNode->wordIdx = idx;
        }
        
        int inTrie(string word) {
            Trie* curNode = this;
            for(auto c : word) {
                c -= 'a';
                if(nullptr == curNode->curLevel[c]) {
                    return -1;
                }
                curNode = curNode->curLevel[c];
            }
            return curNode->wordIdx;
        }

        int inTrie(string& word, int left, int right) {
            Trie* curNode = this;
            for(int i = right; i >= left; --i) {
                char c = word[i] - 'a';
                if(nullptr == curNode->curLevel[c]) {
                    return -1;
                }
                curNode = curNode->curLevel[c];
            }
            return curNode->wordIdx;
        }
    };
 
    vector<vector<int>> palindromePairs(vector<string>& words) {
        // travel all prefix and subfix of a word,
        // find the palindrome and check the existence in the words of
        // reverse of the other part
        Trie* tree = new Trie();
        // Trie* treeReverse = new Trie();
        unordered_map<string, int> strToIdx;
        // int idx = 0;
        // for(auto word : words) {
        //     tree->insert(word);
        //     strToIdx[word] = idx++;
        // }
        
        // int ans = 0;
        // vector<vector<int>> res = {};
        // for(auto word : words) {
        //     deque<string> prefix; 
        //     deque<string> subfix;
        //     int n = word.size();
        //     for(int st = 0; st <= n; ++st) {
        //         string pre = word.substr(0, st);
        //         string sub = word.substr(st);
        //         // cout << "p/s : " << pre << " / " << sub << endl;
        //         if(checkPalindrome(pre)) {
        //             reverse(sub.begin(), sub.end());
        //             if(tree->inTrie(sub)) {
        //                 vector<int> resItem = {strToIdx[sub], strToIdx[word]};
        //                 if(resItem[1] != resItem[0]) {
        //                     // cout << "push: " << word + sub << endl;
        //                     res.emplace_back(resItem);
        //                 }
        //             }
        //         }
        //         if(checkPalindrome(sub) && pre.size() != n) {
        //             reverse(pre.begin(), pre.end());
        //             if(tree->inTrie(pre)) {
        //                 vector<int> resItem = {strToIdx[word], strToIdx[pre]};
        //                 if(resItem[1] != resItem[0]) {
        //                     // cout << "push: " << pre + word << endl;
        //                     res.emplace_back(vector<int>(resItem));
        //                 }
        //             }
        //         }
                
        //     }
        // }

        int idx = 0;
        for(auto word : words) {
            // tree->insert(word, idx);
            // reverse(word.begin(), word.end());
            tree->insert(word, idx);
            ++idx;
        }
        int tmp = 0;
        
        int ans = 0;
        vector<vector<int>> res = {};

        int curWordIdx = 0;
        for(auto word : words) {
            int n = word.size();
            for(int st = 0; st <= n; ++st) {
                string pre = word.substr(0, st);
                string sub = word.substr(st);
                // cout << "p/s : " << pre << " / " << sub << " curWordIdx : " << curWordIdx << endl;
                // if(checkPalindrome(pre)) {
                if(0 != st && checkPalindrome(word, 0, st-1)) {
                    // reverse(sub.begin(), sub.end());
                    int subIdx = tree->inTrie(word, st, n-1);
                    // cout << "subIdx = " << sub << "with idx = " << subIdx << endl;
                    if(subIdx != -1 && curWordIdx != subIdx) {
                        // cout << "curWordIdx / subIdx" << curWordIdx << "/" << subIdx << endl;
                        // cout << "push: " <<  sub << "+" << word << endl;
                        res.emplace_back(vector<int>({subIdx, curWordIdx}));
                    }
                }
                if(checkPalindrome(word, st, n-1)) {
                    // reverse(pre.begin(), pre.end());
                    int preIdx = tree->inTrie(word, 0, st-1);
                    if(preIdx != -1 && preIdx != curWordIdx) {
                        // cout << "curWordIdx / preIdx" << curWordIdx << "/" << preIdx << endl;
                        // cout << "push: " << pre << "+" + word << endl;
                        res.emplace_back(vector<int>({curWordIdx, preIdx}));
                    }
                }
                
            }
            ++curWordIdx;
        }
        return res;
    }
        // for (int i = 0; i < n; i++) {
        //     int m = words[i].size();
        //     for (int j = 0; j <= m; j++) {
        //         if (isPalindrome(words[i], j, m - 1)) {
        //             int left_id = findWord(words[i], 0, j - 1);
        //             if (left_id != -1 && left_id != i) {
        //                 ret.push_back({i, left_id});
        //             }
        //         }
        //         if (j && isPalindrome(words[i], 0, j - 1)) {
        //             int right_id = findWord(words[i], j, m - 1);
        //             if (right_id != -1 && right_id != i) {
        //                 ret.push_back({right_id, i});
        //             }
        //         }
        //     }
        // }

    bool checkPalindrome(string& s, int left, int right) {
        int len = right - left + 1;
        for(int i = 0; i < len / 2; ++i) {
            if(s[left + i] != s[right - i]) {
                return false;
            }
        }
        return true;
    }


    // bool checkPalindrome(string& s) {
    //     int n = s.size();
    //     for(int i = 0; i < n / 2; ++i) {
    //         if(s[i] != s[n - i - 1]) {
    //             return false;
    //         }
    //     }
    //     return true;
    // }
};

```

### 3 使用hash表来查前后缀
```cpp
class Solution {
public:
    class Trie {
    public:
        vector<Trie*> curLevel;
        bool isEnd = false;
        int wordIdx = -1;
        Trie() : curLevel(26), wordIdx(-1) {

        }
        void insert(string& word, int idx) {
            Trie* curNode = this;
            for(auto c : word) {
                c -= 'a';
                if(nullptr == curNode->curLevel[c]) {
                    curNode->curLevel[c] = new Trie();
                }
                curNode = curNode->curLevel[c];
            }
            curNode->isEnd = true;
            curNode->wordIdx = idx;
        }
        
        int inTrie(string word) {
            Trie* curNode = this;
            for(auto c : word) {
                c -= 'a';
                if(nullptr == curNode->curLevel[c]) {
                    return -1;
                }
                curNode = curNode->curLevel[c];
            }
            return curNode->wordIdx;
        }

        int inTrie(string& word, int left, int right) {
            Trie* curNode = this;
            for(int i = right; i >= left; --i) {
                char c = word[i] - 'a';
                if(nullptr == curNode->curLevel[c]) {
                    return -1;
                }
                curNode = curNode->curLevel[c];
            }
            return curNode->wordIdx;
        }
    };
 
    vector<string> wordReverse;
    unordered_map<string, int> strToIdx;

    int findWord(string& s, int left, int right) {
        string tmp = s.substr(left, right - left + 1);
        auto it = strToIdx.find(tmp);
        int res = it == strToIdx.end() ? -1 : it->second;
        // cout << "finding: " << tmp << " with ans = " << res << endl;
        return res;
    }
    

    vector<vector<int>> palindromePairs(vector<string>& words) {
        // travel all prefix and subfix of a word,
        // find the palindrome and check the existence in the words of
        // reverse of the other part
        int idx = 0;
        for(auto word : words) {
            reverse(word.begin(), word.end());
            wordReverse.emplace_back(word);
            strToIdx[word] = idx;
            ++idx;
        }

        vector<vector<int>> res = {};

        int curWordIdx = 0;
        for(auto word : words) {
            int n = word.size();
            for(int st = 0; st <= n; ++st) {
                // cout << "p/s : " << " / " << " curWordIdx : " << curWordIdx << endl;
                if(0 != st && checkPalindrome(word, 0, st-1)) {
                    int subIdx = findWord(word, st, n-1);
                    // cout << "subIdx = " << subIdx << endl;
                    if(subIdx != -1 && curWordIdx != subIdx) {
                        res.emplace_back(vector<int>({subIdx, curWordIdx}));
                    }
                }
                if(checkPalindrome(word, st, n-1)) {
                    int preIdx = findWord(word, 0, st-1);
                    if(preIdx != -1 && preIdx != curWordIdx) {
                        res.emplace_back(vector<int>({curWordIdx, preIdx}));
                    }
                }
                
            }
            ++curWordIdx;
        }
        return res;
    }


    bool checkPalindrome(string& s, int left, int right) {
        int len = right - left + 1;
        for(int i = 0; i < len / 2; ++i) {
            if(s[left + i] != s[right - i]) {
                return false;
            }
        }
        return true;
    }

};
```
