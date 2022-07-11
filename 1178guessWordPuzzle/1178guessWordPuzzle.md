## 1178guessWordPuzzle 猜字谜

### 1 题目
[https://leetcode.cn/problems/number-of-valid-words-for-each-puzzle/](https://leetcode.cn/problems/number-of-valid-words-for-each-puzzle/)

### 2 解题思路
- 1 解题思路:
  - 1.1 使用bitmask去判断单词A中所有字符是否在单词B中出现：将B的bitmask取反，得到哪些字符在B中是没有的，然后和A相与，如果结果不是0，则说明B中没有的字符在A中出现，则B没有包含A
  - 1.2 那么对于每一个puzz，去遍历每一个word的bitmask，即可
  - 1.3 可以 wordMaskCnt[wordBitMask] 表示 wordBitMask的cnt有多少个（因为可能出现：多个单词对应到同一个bitmask的情况）

```cpp
class Solution {
public:
    vector<int> findNumOfValidWords(vector<string>& words, vector<string>& puzzles) {
        unordered_map<int, int> cntWords;
        for(auto& s : words) {
            int curBitMask = 0;
            for(auto& c : s) {
                curBitMask = curBitMask | (1 << (c - 'a'));
            }
            ++cntWords[curBitMask];
        }
        
        // we use a bit mask to represent a word, so that: check each puzz's bitmask 
        // to see how may word's bitmask is contained by it
        vector<int> res(puzzles.size(), 0);
        int idx = 0;
        for(auto& p : puzzles) {
            int curBitMask = 0;
            for(auto& c : p) {
                curBitMask = curBitMask | (1 << (c - 'a'));
            }
            
            int firstBitMask = 1 << (p[0] - 'a');
            for(auto& [mask, cnt] : cntWords) {
                // if the mask donot contain the first bit, condition 1 failed!
                if(firstBitMask & (~mask)) {
                    continue;
                }
                
                // the puzz donot have such a bit himself not own it but curword has it
                if(!((~curBitMask) & mask)) {
                    res[idx] += cntWords[mask];
                }
            }

            ++idx;
        }
        return res;
    }
}
```