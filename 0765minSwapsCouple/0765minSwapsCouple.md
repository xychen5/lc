## 2025waysToPartition

### 1 题目
[https://leetcode-cn.com/problems/couples-holding-hands/](https://leetcode-cn.com/problems/couples-holding-hands/)

### 2 解题思路
- 1 普通思路
对于每一个2k - 2， 2k - 1的连续两个座位去找，2k - 2上的人的情侣，把它换到2k - 1位置上，遍历k即可 o(n**2)
- 2 改进思路
考虑到这样一个事实：
如果有8个座位，然后所有情侣都没办法相邻而坐，则考虑：将在2k-2和2k-1座位上的相邻两人但不是情侣创建一条边，节点则是情侣的cp序号
(比如4,5序号的情侣对应一个节点，为5/2 == 4/2 == 2)
然后我们可以知道，这个图只有一个连通子图，然后其节点数量为4，那么需要交换的次数为4-1 = 3，
> 容易被迷惑的地方： 一次交换至少能够完成一对情侣，只有最后的一次交换能够完成两队情侣，其余均只能完成一次
> 所以说这个最小交换次数，其实别反复换，算出来的就是最小的
```cpp
class Solution {
public:
    int minSwapsCouples(vector<int>& row) {
        // 容易被迷惑的地方： 一次交换至少能够完成一对情侣，只有最后的一次交换能够完成两队情侣，其余均只能完成一次
        // 所以说这个最小交换次数，其实别反复换，算出来的就是最小的
        
        // 首先注意到，将2个情侣看成一个节点，如果不属于一对的情侣坐在2k - 2, 2k - 1的两个位置上，则连一条线
        vector<int> parent(row.size() / 2);
        for(int i = 0; i < row.size() / 2; ++i) {
            parent[i] = i;
        }

        for(int i = 0; i < row.size(); i += 2) {
            int nodeIdx = i / 2;
            unionMerge(parent, row[i] / 2, row[i + 1] / 2);
            // std::cout << row[i] / 2<< " -> " << row[i + 1] / 2 << std::endl;
        }

        // 找出上图所有连通子图, 所有连通子图的边的节点个数减去1得到一个子图所有情侣相邻而坐需要的交换次数
        unordered_map<int, int> rootIdxToCnt;
        for(int i = 0; i < row.size() / 2; ++i) {
            rootIdxToCnt[find(parent, i)] ++;
            // std::cout << i << " -> " << find(parent, i) << std::endl;
        }

        int res = 0;
        for(auto& it : rootIdxToCnt) {
            res += it.second - 1;
        }
        return res;

    }

    int find(vector<int>& parent, int curNode) {
        while(parent[curNode] != curNode) {
            parent[curNode] = parent[parent[curNode]];
            curNode = parent[curNode];
        }
        return curNode;
    }

    void unionMerge(vector<int>& parent, int from, int to) {
        int x = find(parent, from);
        int y = find(parent, to);
        
        if(x != y) {
            parent[x] = y;
        }
    }
}
```