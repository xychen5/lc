## 0332HierholzerToFindEulerPath 找欧拉路径

### 1 题目
[https://leetcode-cn.com/problems/reconstruct-itinerary/](https://leetcode-cn.com/problems/reconstruct-itinerary/)


### 2 解题思路
hierholzer算法参考：[https://www.geeksforgeeks.org/hierholzers-algorithm-directed-graph/](https://www.geeksforgeeks.org/hierholzers-algorithm-directed-graph/)
[https://blog.csdn.net/qq_34292517/article/details/105463522?utm_medium=distribute.pc_relevant.none-task-blog-2~default~baidujs_title~default-0.pc_relevant_default&spm=1001.2101.3001.4242.1&utm_relevant_index=3](https://blog.csdn.net/qq_34292517/article/details/105463522?utm_medium=distribute.pc_relevant.none-task-blog-2~default~baidujs_title~default-0.pc_relevant_default&spm=1001.2101.3001.4242.1&utm_relevant_index=3)
- 1 自己的思路：
  - 1.1 主要是使用hierholzer算法找到欧拉路径，由于需要字典序，那么我们邻接表则使用优先队列来存储
- 2 hierholzer算法
  - 2.1 dfs，当一个节点没邻居了
  - 2.2 将节点入栈reversePath
  - 2.3 dfs完成，reversePath则为逆序栈
- 3 欧拉图等等理解：参考上述第二篇文章
> 基本概念：
> 圈：任选图中一个顶点为起点，沿着不重复的边，经过不重复的顶点为途径，之后又回到起点的闭合途径称为圈。
> 欧拉路径：通过图中所有边一次且仅一次遍历所有顶点的路径称为欧拉(Euler)路径；
> 欧拉回路：通过图中所有边一次且仅一次行遍所有顶点的回路称为欧拉回路；
> 欧拉图：具有欧拉回路的图称为欧拉图；
> 半欧拉图：有欧拉路径但没有欧拉回路的图称为半欧拉图。
> 欧拉图与半欧拉图的判定：
> G是欧拉图⇔ \Leftrightarrow⇔G中所有顶点的度均为偶数⇔ \Leftrightarrow⇔G是若干个边不重的圈的并。
> G是半欧拉图⇔ \Leftrightarrow⇔G中恰有两个奇数度顶点。
```cpp
class Solution {
public:
    
    int edgeNums = -1;
    int nodeNums = -1;
    unordered_map<string, int> nodes;
    unordered_map<int, string> toStr;
    vector<string> findItinerary(vector<vector<string>>& tickets) {
        // map str to int according to dictionary order
        set<string, std::less<string>> airports;
        for(auto& vec : tickets) {
            airports.insert(vec[0]);
            airports.insert(vec[1]);
        }

        int i = 0;
        for(auto& str : airports) {
            toStr[i] = str;
            nodes[str] = i++;
        }
        
        // construct the adj table
        int nodeNums = airports.size();
        int edgeNums = tickets.size();
        // vector<vector<int>> table(nodeNums, vector<int>(0));
        vector<priority_queue<int, vector<int>, greater<int>>> table(nodeNums, priority_queue<int, vector<int>, greater<int>>());
        for(auto& vec : tickets) {
            table[nodes[vec[0]]].push(nodes[vec[1]]);
        }

        vector<string> strRes;
        vector<priority_queue<int, vector<int>, greater<int>>> tableTmp(table);
        vector<int> res;
        dfs(nodes["JFK"], tableTmp, res);
        reverse(res.begin(), res.end());
        for(auto& node : res) {
            strRes.push_back(toStr[node]);
        }

        return strRes;
    }

    // 
    void dfs(int st, vector<priority_queue<int, vector<int>, greater<int>>>& map, vector<int>& res) {
        
        while(!map[st].empty()) {
            int nextSt = map[st].top();
            map[st].pop();
            // cout << "from to: " << toStr[st] << " -> " << toStr[nextSt] << endl;
            dfs(nextSt, map, res);
        }
        res.emplace_back(st);
    }
};
```