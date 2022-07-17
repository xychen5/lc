## 1948rmDupFolderInFS 删除系统中的重复文件夹

### 1 题目
[https://leetcode.cn/problems/delete-duplicate-folders-in-system/](https://leetcode.cn/problems/delete-duplicate-folders-in-system/)

### 2 解题思路
- 1 解题思路:
  - 1.1 构建字典树,curlevel: map<string, trie*>
  - 1.2 遍历，获取每个节点的hash值，用seqCnt[seq]记录节点的seq的出现个数
  - 1.3 回溯：curPath作为当前遍历的路径，查看每个节点在seqCnt出现个数，大于等于2则直接查看同级下一个节点，否则将结果加入，然后到下一层然后回溯

```cpp
class Solution {
public:
    class Trie {
    public:
        // vector<Trie*> curLevel;
        map<string, Trie*> curLevel;
        string seqInBackTrack;
        bool isEnd = false;

        Trie() : seqInBackTrack("") {
        }

        void buildTrie(vector<vector<string>>& dict) {
            for(auto& w : dict) {
                auto curNode = this;
                for(auto name : w) {
                    if(0 == curNode->curLevel.count(name)) {
                        curNode->curLevel[name] = new Trie();
                    }
                    curNode = curNode->curLevel[name];
                }
                curNode->isEnd = true;
            }
        }
    };

    unordered_map<string, int> seqToPtr;

    // version mine
    string dfs(Trie* root, string cur) {
        if(root->curLevel.empty()) {
            return cur;
        }
        for(auto& [name, nextRoot] : root->curLevel) {
            // cout << "cur/next: " << cur << "/" << name << endl;
            
            root->seqInBackTrack += dfs(nextRoot, name);
        }
        seqToPtr[root->seqInBackTrack]++;

        return "(" + cur + root->seqInBackTrack + ")";
    }
    
    // version others
    void dfs(Trie* root) {
        if(root->curLevel.empty()) {
            return;
        }
        string seq = "";
        for(auto& [name, nextRoot] : root->curLevel) {
            // cout << "cur/next: " << cur << "/" << name << endl;
            dfs(nextRoot);
            root->seqInBackTrack += (name + "(" + nextRoot->seqInBackTrack + ")");
        }
        seqToPtr[root->seqInBackTrack]++;
    }

    void dfs2(Trie*& root) {
        for(auto& [name, nextRoot] : root->curLevel) {
            if("" != nextRoot->seqInBackTrack && \
            seqToPtr[nextRoot->seqInBackTrack] >= 2) {
                nextRoot = nullptr;
            } else {
                dfs2(nextRoot);
            }
        }
    }
 
    void dfs3(Trie* root, vector<string>& cur, vector<vector<string>>& res) {
        for(auto& [name, nextRoot] : root->curLevel) {
            if(seqToPtr[nextRoot->seqInBackTrack] >= 2) {
                continue;
            }
            cur.push_back(name);
            res.push_back(cur);
            dfs3(nextRoot, cur, res);
            cur.pop_back();
        }
    }
   
    vector<vector<string>> deleteDuplicateFolder(vector<vector<string>>& paths) {
        Trie* trie = new Trie();
        trie->buildTrie(paths);

        dfs(trie,""); // get hash
        // dfs(trie);// get hash
        vector<string> cur;
        vector<vector<string>> res;
        dfs3(trie, cur, res); // get res

        return  res;
    }
};
```