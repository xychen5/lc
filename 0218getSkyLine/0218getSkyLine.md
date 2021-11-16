## 0391 完美矩形

### 1 题目
[https://leetcode-cn.com/problems/the-skyline-problem](https://leetcode-cn.com/problems/the-skyline-problem)


### 2 解题思路
思路：
- 1 对于每一个建筑的边界b，
  - 1.2 首先获得所有可能对其产生影响的建筑里(即左边边界比当前边界小的顶点),将这个建筑存到优先队列里，每个item为<右边界，高度>
  - 1.3 通过不断弹出队列里的元素，找到包含这个边界的建筑building也就是，building[0] <= b < building[1], 若找不到(也就是和当前队列有关的建筑都空了，即优先队列(大顶堆)都空了)，则当前边界对应的高度为0, 找到了则，看它的高度是否与当前堆顶的高度相同，若不同，则将结果b以及其高度压入否则舍弃b，去看下一个边界
```cpp
class Solution {
public:
    vector<vector<int>> getSkyline(vector<vector<int>>& buildings) {
        // 思路：
        // 对于每一个建筑的边界b，首先获得所有可能对其产生影响的建筑里(即左边边界比当前边界小的顶点)，
        // 将这个建筑存到优先队列里，每个item为<右边界，高度>
        // 通过不断弹出队列里的元素，找到包含这个边界的建筑building
        // 也就是，building[0] <= b < building[1]
        // 若找不到(也就是和当前队列有关的建筑都空了，即优先队列(大顶堆)都空了)，则当前边界对应的高度为0
        // 找到了，看它与当前堆顶的高度谁大
        // 若b更大，则将结果b以及其高度压入
        // 否则舍弃b，去看下一个边界

        auto cmp = [](std::pair<int, int>& a, std::pair<int, int>& b){return a.second < b.second;};
        std::priority_queue<std::pair<int, int>, vector<pair<int, int>>, decltype(cmp)> queue(cmp);
        
        int n = buildings.size();
        vector<int> bounds;
        vector<vector<int>> res;
        
        for(int i = 0; i < buildings.size(); ++i) {
            bounds.emplace_back(buildings[i][0]);
            bounds.emplace_back(buildings[i][1]);
        }

        sort(bounds.begin(), bounds.end(), std::less<int>());
        
        int j = 0;
        for(auto& curBound : bounds) {
            // 获取所有对当前边界有影响的建筑
            while(j < buildings.size() && buildings[j][0] <= curBound) {
                queue.push(std::make_pair(buildings[j][1], buildings[j][2]));
                ++j;
            }
                        
            // 找到第一个包含该边界的建筑
            while(!queue.empty() && queue.top().first <= curBound) {
                queue.pop();
            }
            
            int curBoundHeight = queue.empty() ? 0 : queue.top().second;
            
            // 避免一些边界对应的是任然是上一个边界对应的最高值，然后把它加进去了，第一行为没有最后一个或判断的输出
            // [[2,10],[3,15],[5,15],[7,12],[9,12],[12,0],[15,10],[19,10],[20,8],[24,0]]
            // [[2,10],[3,15],[7,12],[12,0],[15,10],[20,8],[24,0]]
            if(res.size() == 0 || res.back()[1] != curBoundHeight) {
                res.emplace_back(vector<int>{curBound, curBoundHeight});
            }
        }

        return res;
    }
};
```
