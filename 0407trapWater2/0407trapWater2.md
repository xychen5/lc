## 0407trapWater2 接雨水2

### 1 题目
[https://leetcode.cn/problems/trapping-rain-water-ii/](https://leetcode.cn/problems/trapping-rain-water-ii/)

### 2 解题思路
- 1 解题思路：
  - 1.1 使用dijstra，我们考虑如何将dijstra和这个问题对应？
  - 1.2 对于坐标x,y我们要求最终能接多少雨水，是不是就是求从xy到边界所有路径的最小高度，这个高度和x,y的差值不就是我们的答案吗？但是我们显然不可能从每个xy出发运算dijstra，这样复杂度太大
  - 1.3 很容易想到，我们不从xy出发，从边界出发即可，那么有问题，边界是很多个点的集合，不还是有较大复杂度？那么我们考虑，将所有边界设置为一个超级原点O的直接后继节点，那么我们只需要从O出发即可，那么dijstra的松弛数组初始化为？边界上所有点的高度呗
  - 1.4 说了那么久，具体来看一个dijstra的某一步是如何执行的
    - 1.4.1 定义：松弛数组 这里由于每次从最短路（也就是最小高度出发），于是使用minHeap，那么minHeap存的是什么？是接雨水后的对应位置的高度
    - 1.4.2 松弛操作：取出minHeap中的top，然后考虑用这个top去松弛它的四周的位置，看看能不能接雨水，能接雨水的前提是：被松弛的对象的高度比这个top的高度要低，但是我们试想，这个被松弛的对象会不会完全没有办法接到被松弛后的这个高度的雨水？不会，因为倘若接不到，一定会有边界有个高度比这个被松弛对象的高度低，然而我们选的是边界（也就是minHeap初始化的那些点）中高度最低的点，这个点都比被松弛对象的高度高，所以被松弛对象一定能够接到top的高度的雨水(前提是能够松弛)
  - 1.5 对dijstra的宏观印象：
    - 我们可以看到，其实是minHeap存的是目前探索的地区的接雨水后的高度，我们贪心的每次从最低高度出发，去松弛没有探索过的点，所以这个贪心策略的正确性就在于每次从最低高度出发，因为水只能从高度更低的地方溜出去

```cpp
class Solution {
public:
    
    int m, n;
    int dx[4] = {-1, 0, 1, 0};
    int dy[4] = {0, 1, 0, -1};


    int trapRainWater(vector<vector<int>>& heightMap) {
        m = heightMap.size();
        n = heightMap[0].size();
        if(m <= 2 || n <= 2) {
            return 0;
        }

        auto cmp = [](const pair<pair<int, int>, int>& a, const pair<pair<int, int>, int>& b) {
            return a.second > b.second;
        };
        priority_queue<pair<pair<int, int>, int>, vector<pair<pair<int, int>, int>>, decltype(cmp)> minHeap(cmp);

        // init
        vector<vector<int>> vis(m, vector<int>(n, false));        
        for(int i = 0; i < m; ++i) {
            minHeap.push({{i, 0}, heightMap[i][0]});
            minHeap.push({{i, n-1}, heightMap[i][n-1]});
            vis[i][0] = true;
            vis[i][n-1] = true;
        }
        for(int j = 1; j < n-1; ++j) {
            minHeap.push({{0, j}, heightMap[0][j]});
            minHeap.push({{m-1, j}, heightMap[m-1][j]});
            vis[0][j] = true;
            vis[m-1][j] = true;
        }

        // dijstra
        // minHeap: [idx, maxWaterHeight]
        int res = 0;
        while(!minHeap.empty()) {
            auto cur = minHeap.top();
            minHeap.pop();
            int x = cur.first.first;
            int y = cur.first.second;
            auto height = cur.second;

            // release around
            for(int i = 0; i < 4; ++i) {
                int nextX = x + dx[i];
                int nextY = y + dy[i];
                if(0 <= nextX && nextX < m && 0 <= nextY && nextY < n && !vis[nextX][nextY]) {
                    if(heightMap[nextX][nextY] < height) {
                        res += height - heightMap[nextX][nextY];
                        heightMap[nextX][nextY] = height;
                    }
                    vis[nextX][nextY] = true;
                    minHeap.push({{nextX, nextY}, heightMap[nextX][nextY]});
                }
            }
        }
        return res;
    }
};
```