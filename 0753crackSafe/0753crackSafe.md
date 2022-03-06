## 0753crackSafe 破解保险箱(变形欧拉路)

### 1 题目
[https://leetcode-cn.com/problems/freedom-trail/](https://leetcode-cn.com/problems/freedom-trail/)
[https://leetcode-cn.com/problems/reconstruct-itinerary/](https://leetcode-cn.com/problems/reconstruct-itinerary/)

### 2 解题思路
- 1 对于 n = 3, k = 3, 我们的图的节点为(k ^ (n-1)个)： 00, 01, ..., 22, 然后每个节点都有k个边，这样一共是k^n个边
  - 1.1 那么如何认为走过一条边就是尝试一次密码呢？
  - 1.2 比如: 00的邻接顶点为0,1,2, 那么当dfs访问从00节点到其邻接点分别组成的边为000，001，002，则他们对应的下一跳就为: 00,01,02，也就是**取当前dfs访问得到的边的后n-1位**
- 2 hierholzer算法
  - 2.0 选择一个节点开始dfs
  - 2.1 当一个节点没邻居了
  - 2.2 将节点入栈reversePath
  - 2.3 dfs完成，reversePath则为逆序栈
```cpp
class Solution {
public:
    int n = -1;
    int k = -1;
    vector<char> kVec;
    string crackSafe(int n, int k) {
        // since for each bit, there a k's possiblity
        // so the final str's length = k^n
        // consider a G, vertices are {0, 1, ..., k-1}
        // for each edge: vi -> vj(vi could equal vj), 
        // there shall be n-1's such same edge
        // we just need a way to walk through the G
        // try hierholzer algo
        if(1 == n) {
            string tmpRes = "";
            for(int i = 0; i < k; ++i) {
                tmpRes.push_back(i + '0');
            }
            return tmpRes;
        }

        this->k = k;
        this->n = n;
        for(int i = 0; i < k; ++i) {
            kVec.push_back(i + '0');
        }

        unordered_set<string> seen;
        unordered_map<string, vector<char>> graph;
        buildGraph("", n - 1, graph);
        
        string stStr(n-1, '0');
        
        string res = "";
        hierholzer(stStr, graph, res, seen);
        
        // when n=3, k=3, we start from "00" node, so we add reverse of "00" to the end of the res, cause hierholzer produce a reverse eular path (start from "00", end to "00")
        res += stStr;
        return res;
    }

    void buildGraph(string tmp, int leftBitNum, unordered_map<string, vector<char>>& graph) {
        if(0 == leftBitNum) {
            // cout << "len: " << leftBitNum << "finish node: " << tmp << endl;
            graph[tmp] = kVec;
            return;
        }

        for(int st = 0; st < k; ++st) {
            buildGraph(tmp + kVec[st], leftBitNum-1, graph);
        }
    }

void hierholzer(
    string st, 
    unordered_map<string, vector<char>>& graph, 
    string& res, 
    unordered_set<string>& seen) {
        // cout << "doing : " << st << endl;
        bool hasOut = false;
        for(int edIdx = 0; edIdx < k; ++edIdx) {
            string curEdge(st);
            curEdge.push_back(graph[st][edIdx]);
            
            if(seen.count(curEdge)) {
                continue;
            }
            
            hasOut = true;
            string nextSt = curEdge.substr(1);
            // cout << "st -> nextSt: " << st << " -> " << nextSt << endl;
            seen.insert(curEdge);
            // cout << "see edge: " << curEdge << endl; 
            hierholzer(nextSt, graph, res, seen); // post order
            res.push_back(graph[st][edIdx]); // hierholzer
        }
    }

};
```