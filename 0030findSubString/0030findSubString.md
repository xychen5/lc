## 0030findSubString 查找字串

### 1 题目
[https://leetcode-cn.com/problems/substring-with-concatenation-of-all-words/](https://leetcode-cn.com/problems/substring-with-concatenation-of-all-words/)

### 2 解题思路
- 1 很显然我们会去维护长度为words.size() * words[0].size()的滑动窗口然后滑动就可以了（记录单词个数为m，单词长度为d）
  - 1.1 如何存储每个窗口的值呢？因为无需考虑单词的顺序，于是不能用字符串去比较，我们采用 unordered_map<string, int>记录窗口中每个单词出现的次数即可
- 2 窗口每次移动d，那么比如窗口从0开始，那么1，2，，，d-1的窗口就没有被搜索，于是需要同时开启d个窗口
- 3 上面的过程最关键的一步是需要认识到，所有单词的长度为d，这导致我们可以按照d去移动，这导致了同时开启多个窗口，最具体的一点，存储窗口中的内容我们用unordered_map<string, int>去存储即可
```cpp
class Solution {
public:
    class DictTree {
    public:
        DictTree* root;
        vector<DictTree*> curLevel;
        bool isEnd = true;
        DictTree() : curLevel(26) {}
        DictTree(vector<string>& words):curLevel(26) {
            this->root = buildDict(words);
        }        
        
        DictTree* buildDict(vector<string>& words) {
            auto root = new DictTree();
            for(auto& w : words) {            
                auto cur = root;
                for(auto& c : w) {
                    if(cur->curLevel[c - '0']) {
                        cur->curLevel[c - '0'] = new DictTree();
                    }
                    cur = cur->curLevel[c - '0'];
                }
                cur->isEnd = true;
            }
            return root;
        }

        bool wordInTree(string& w) {
            auto cur = this->root;
            for(auto& c : w) {
                if(nullptr == cur->curLevel[c - '0']) {
                    return false;
                }
                cur = cur->curLevel[c - '0'];
            }
            
            return cur->isEnd;
        }

    };

    vector<int> findSubstring(string s, vector<string>& words) {
        int op = 0;
        int ed = 1;
        
        int wordLen = words[0].size();
        int wordCnt = words.size();
        int winLen = wordLen * wordCnt;
        vector<int> res;

        if(winLen > s.size()) {
            return res;
        }

        unordered_map<string, int> tar;
        for(auto& w : words) {
            tar[w]++;
        }
        
        // how to maintain a window is the most important
        vector<unordered_map<string, int>> windows;
        for(int i = 0; i < wordLen; ++i) {
            unordered_map<string, int> curWin;
            int wst = i;
            for(int wordIdx = 0; wordIdx < wordCnt && wst + wordLen <= s.size(); ++ wordIdx) {
                curWin[s.substr(wst, wordLen)]++;
                wst += wordLen;
            }
            windows.push_back(curWin);
                //             printMap(windows[i]);
                // cout << "--->\n";
            if(windows[i] == tar) {
                res.push_back(i);
            }
        }

        int stride = wordLen;
        int movNum = 1;
        while(movNum * stride + winLen <= s.size()) {
            int newWst = winLen + (movNum-1) * stride;
            int oldWst = (movNum-1) * stride;
            for(int winIdx = 0; winIdx < wordLen; ++winIdx) {
                string oldStWord = s.substr(oldWst + winIdx, wordLen);
                string newStWord = s.substr(newWst + winIdx, wordLen);
                
                if(0 == --windows[winIdx][oldStWord]) {
                    windows[winIdx].erase(oldStWord);
                }
                windows[winIdx][newStWord]++;
                
                // printMap(windows[winIdx]);
                // cout << "---\n";

                if(windows[winIdx] == tar) {
                    res.push_back(movNum * stride + winIdx);
                }
            }
            ++movNum;
        }

        return res;
 
    }

    void printMap(unordered_map<string, int>& um) {
        for(auto p : um) {
            cout << p.first << " -> " << p.second << endl;
        }
    }

};
```