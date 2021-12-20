## 0208. 实现 Trie (前缀树)

### 1 题目
[https://leetcode-cn.com/problems/implement-trie-prefix-tree/](https://leetcode-cn.com/problems/implement-trie-prefix-tree/)

### 2 解题思路
- 1 就正常生成字典树也就是前缀树即可，前缀树大致示意如下：
  - 1.1 其主要功能是将单词集合使用树形结构存储，便于查询和模糊匹配尝试的常见应用包括存储预测文本或自动完成字典和实现近似匹配算法，例如在拼写检查和连字软件中使用的算法。 此类应用程序利用 trie 快速搜索、插入和删除条目的能力。 但是，如果只需要存储字典单词（即不需要存储与每个单词关联的元数据），则最小确定性非循环有限状态自动机 (DAFSA) 或基数树将使用比 trie 更少的存储空间。 这是因为 DAFSA 和基数树可以从对应于存储的不同单词的相同后缀（或部分）的特里树中压缩相同的分支。
- 2 描述一下插入一个词的方式：
  - 2.0 将当前节点curNode设置为root
  - 2.1 对于词的每一个字母
    - 若该字母不在当前节点，则创建该节点
    - 将当前节点curNode更新为当前字母对应的子节点
![https://cdn.jsdelivr.net/gh/xychen5/blogImgs@main/imgs/Trie_example.svg.369cli0zka00.png](https://cdn.jsdelivr.net/gh/xychen5/blogImgs@main/imgs/Trie_example.svg.369cli0zka00.png)

实现代码如下：
```cpp
class Trie {
public:
    vector<Trie *>curLevel;
    bool isEnd = false;

    Trie() : curLevel(26) {
        
    }

    void insert(string word) {
        Trie * curNode = this;
        for(char c : word) {
            c -= 'a';
            if(nullptr == curNode->curLevel[c]) {
                curNode->curLevel[c] = new Trie();
            } 
            // check nextLevel
            curNode = curNode->curLevel[c];
        }
        curNode->isEnd = true;
    }
    
    bool search(string word) {
        Trie * curNode = this;
        for(char c : word) {
            c -= 'a';
            if(nullptr == curNode->curLevel[c]) {
                return false;
            }
            curNode = curNode->curLevel[c];
        }
        return curNode->isEnd;
    }
    
    bool startsWith(string prefix) {
        Trie * curNode = this;
        for(char c : prefix) {
            c -= 'a';
            if(nullptr == curNode->curLevel[c]) {
                return false;
            }
            curNode = curNode->curLevel[c];
        }
        return true;
    }
};

/**
 * Your Trie object will be instantiated and called as such:
 * Trie* obj = new Trie();
 * obj->insert(word);
 * bool param_2 = obj->search(word);
 * bool param_3 = obj->startsWith(prefix);
 */
```
