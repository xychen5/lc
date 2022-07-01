## 1255maxScoreWords 最大单词分数从字母集合中

### 1 题目
[https://leetcode.cn/problems/maximum-score-words-formed-by-letters/](https://leetcode.cn/problems/maximum-score-words-formed-by-letters/)

### 2 解题思路
- 1 解题思路：
  - 1.1 很显然：我们可以遍历所有的单词的集合，就是用或者不用，可以用状态压缩，也可以使用回溯
  - 1.2 这里我们使用回溯，主要就是：首先用，然后我们能得到一个分数，然后不用，我们也能得到一个分数，我们两者取最大值，记得在用了之后将其回溯，也就是把用掉的单词对应的字母再加回来
  - 1.3 返回结果：很显然，就是所有的单词都考虑到的时候返回0，就是对于编号st，每下一层回溯会让st++，那么等st和单词列表个数相等就返回就行

```cpp
class Solution {
public:
    vector<int> wordScore;

    void printPool(unordered_map<char, int>& leftCharPool) {
        for(auto& [c, cnt] : leftCharPool) {
            cout << c << " " << cnt << endl;
        }
        cout << "---\n";
    }
    
    bool addOrRemove(string& word, unordered_map<char, int>& leftCharPool, bool add) {
        // cout << "add/rm: " << word << endl;
        if(add) {
            for(auto& c : word) {
                ++leftCharPool[c];
            }
        } else {
            unordered_map<char, int> curWord;
            for(auto& c : word) {
                ++curWord[c];
            }

            for(auto& [c, cnt] : curWord) {
                if(leftCharPool[c] < cnt) {
                    return false;
                }
            }

            printPool(leftCharPool);
            // remove the word from the pool
            for(auto& [c, cnt] : curWord) {
                // cout << "rm " << c << " : " << cnt << endl;
                leftCharPool[c] -= cnt;
            }
            // printPool(leftCharPool);

        }
        return true;
    }

    int backTrack(vector<string>& words, int st, unordered_map<char, int>& leftCharPool) {
        if(words.size() == st) {
            return 0;
        }

        int curScore = INT_MIN;
        // use it
        if(addOrRemove(words[st], leftCharPool, false)) {
            // cout << "using " << words[st] << endl;
            // printPool(leftCharPool);
            curScore = max(wordScore[st] + backTrack(words, st + 1, leftCharPool), curScore);
            // add it back
            addOrRemove(words[st], leftCharPool, true);
        }
        // not use it
        // cout << "not using" << words[st] << endl;
            // printPool(leftCharPool);
        curScore = max(backTrack(words, st + 1, leftCharPool), curScore);
        return curScore; 
    }
   
    int maxScoreWords(vector<string>& words, vector<char>& letters, vector<int>& score) {
        // check all subsets of words using status compression
        // you may use status compression, but here we use backTrack
        unordered_map<char, int> leftCharPool;
        wordScore.resize(words.size(), 0);
        int wIdx = 0;
        for(auto& w : words) {
            for(auto& c : w) {
                wordScore[wIdx] += score[c - 'a'];
            }
            ++wIdx;
        }

        for(auto& c : letters) {
            ++leftCharPool[c];
        }
        
        int st = 0;
        return backTrack(words, 0, leftCharPool);
    }
};
```