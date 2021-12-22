## 0440. 字典序的第K小数字

### 1 题目
[https://leetcode-cn.com/problems/k-th-smallest-in-lexicographical-order/](https://leetcode-cn.com/problems/k-th-smallest-in-lexicographical-order/)

### 2 解题思路
- 1 首先是模拟的思路，构建出n之前的字典树，然后dfs顺序算出来对应节点的数据
实现代码如下：
```cpp
class Solution {
public:
    class Trie {
    public:
        vector<Trie*> curLevel;
        bool isEnd = false;
        int idx = -1;
        
        Trie() : curLevel(10) {
            
        }

        void insert(string s, int idx) {
            Trie* curNode = this;
            cout << "in : " << s << endl;
            for(auto c : s) {
                c -= '0';
                if(nullptr == curNode->curLevel[c]) {
                    curNode->curLevel[c] = new Trie();
                }
                curNode = curNode->curLevel[c];
            }
            curNode->isEnd = true;
            curNode->idx = idx;
        }
    };

    int findKthNumber(int n, int k) {
        Trie* tree = new Trie();

        for(int i = 1; i <= n; ++i) {
            string str = std::to_string(i);
            tree->insert(str, i);
        }
        int res = 0;
        // cout << ">>>>>> " << tree->curLevel[1]->curLevel[0]->idx << endl;
        bool finish = false;
        dfsToCount(tree, k, res, finish);
        return res;
    }

    void dfsToCount(Trie* node, int& k, int& res, bool& finish) {
        // cout << "into it" << endl;
        if(!finish && 0 == k) {
            res = node->idx;
            finish = true;
            return;
        }
        
        int i = 0;
        for(Trie* child : node->curLevel) {
            // cout << "-----" << i++ << endl;
            if(nullptr != child) {
                // cout << "dfs:k > " << child->idx << ":" << k << " --- " << child->curLevel[0] << endl;
                --k;
                dfsToCount(child, k, res, finish);
            }
        }
        // cout << "out" << endl;
    }
};
```
- 2 改变思路，不真的去dfs搜索，**然后只需每次和k比较确定需要进入的节点**即可，想象对应的字典树(显然是10叉树)
  - 2.1 使用一个前缀去保留当前的节点，然后计算该前缀对应的之前的所有节点数
  - 2.2 移动节点直到该节点之前的节点数为k(要么横向移动，要么下一层)
  - 2.3 eg: 7928 7928对应的移动轨迹如下：
```cpp
prefix\cnt : 1 1111
curPrefix\curNode [find prefix]: 2 1112
prefix\cnt : 2 1111
curPrefix\curNode [find prefix]: 3 2223
prefix\cnt : 3 1111
curPrefix\curNode [find prefix]: 4 3334
prefix\cnt : 4 1111
curPrefix\curNode [find prefix]: 5 4445
prefix\cnt : 5 1111
curPrefix\curNode [find prefix]: 6 5556
prefix\cnt : 6 1111
curPrefix\curNode [find prefix]: 7 6667
prefix\cnt : 7 410
curPrefix\curNode [find prefix]: 8 7077
prefix\cnt : 8 111
curPrefix\curNode [find prefix]: 9 7188
prefix\cnt : 9 111
curPrefix\curNode [dive next]: 90 7189
prefix\cnt : 90 11
curPrefix\curNode [find prefix]: 91 7200
prefix\cnt : 91 11
curPrefix\curNode [find prefix]: 92 7211
prefix\cnt : 92 11
curPrefix\curNode [find prefix]: 93 7222
prefix\cnt : 93 11
curPrefix\curNode [find prefix]: 94 7233
prefix\cnt : 94 11
curPrefix\curNode [find prefix]: 95 7244
prefix\cnt : 95 11
curPrefix\curNode [find prefix]: 96 7255
prefix\cnt : 96 11
curPrefix\curNode [find prefix]: 97 7266
prefix\cnt : 97 11
curPrefix\curNode [find prefix]: 98 7277
prefix\cnt : 98 11
curPrefix\curNode [find prefix]: 99 7288
prefix\cnt : 99 11
curPrefix\curNode [dive next]: 990 7289
prefix\cnt : 990 1
curPrefix\curNode [find prefix]: 991 7290
prefix\cnt : 991 1
curPrefix\curNode [find prefix]: 992 7291
prefix\cnt : 992 1
curPrefix\curNode [find prefix]: 993 7292
prefix\cnt : 993 1
curPrefix\curNode [find prefix]: 994 7293
prefix\cnt : 994 1
curPrefix\curNode [find prefix]: 995 7294
prefix\cnt : 995 1
curPrefix\curNode [find prefix]: 996 7295
prefix\cnt : 996 1
curPrefix\curNode [find prefix]: 997 7296
prefix\cnt : 997 1
curPrefix\curNode [find prefix]: 998 7297
prefix\cnt : 998 1
curPrefix\curNode [find prefix]: 999 7298
```
```cpp
class Solution {
public:
    class Trie {
    public:
        vector<Trie*> curLevel;
        bool isEnd = false;
        int idx = -1;
        
        Trie() : curLevel(10) {
            
        }

        void insert(string s, int idx) {
            Trie* curNode = this;
            cout << "in : " << s << endl;
            for(auto c : s) {
                c -= '0';
                if(nullptr == curNode->curLevel[c]) {
                    curNode->curLevel[c] = new Trie();
                }
                curNode = curNode->curLevel[c];
            }
            curNode->isEnd = true;
            curNode->idx = idx;
        }
    };

    int findKthNumber(int n, int k) {
        Trie* tree = new Trie();

        for(int i = 1; i <= n; ++i) {
            string str = std::to_string(i);
            tree->insert(str, i);
        }
        int res = 0;
        // cout << ">>>>>> " << tree->curLevel[1]->curLevel[0]->idx << endl;
        bool finish = false;
        dfsToCount(tree, k, res, finish);
        return res;
    }

    void dfsToCount(Trie* node, int& k, int& res, bool& finish) {
        // cout << "into it" << endl;
        if(!finish && 0 == k) {
            res = node->idx;
            finish = true;
            return;
        }
        
        int i = 0;
        for(Trie* child : node->curLevel) {
            // cout << "-----" << i++ << endl;
            if(nullptr != child) {
                // cout << "dfs:k > " << child->idx << ":" << k << " --- " << child->curLevel[0] << endl;
                --k;
                dfsToCount(child, k, res, finish);
            }
        }
        // cout << "out" << endl;
    }
};
```
