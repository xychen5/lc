## 2102sequentialOrdinalRankRequest 序列顺序查询

### 1 题目
[https://leetcode.cn/problems/sequentially-ordinal-rank-tracker/](https://leetcode.cn/problems/sequentially-ordinal-rank-tracker/)

### 2 解题思路
- 1 解题思路:
  - 1.1 好的景点定义为分数高，那么这种查询是序列到来的时候，很容易想到双堆对顶的做法，比如，序列到来的数字，求中位数？那么左边maxHeap 右边minHeap保证左边的总比右边的小且maxHeap最大比minHeap最小小即可
  - 1.2 同理，我们需要minHeap来维持，最好的getCnt + 1个景点，注意，之所以是minHeap，是因为我们要获取的是第getCnt + 1个最好的，而不是前getCnt+1里面第一的，所以，minHeap保持getCnt+1大小，每次取对顶作为答案即可
    - add：如果发现minHeap中大于了getCnt+1，则说明放不下了，我们得把目前的getCnt+2的对顶，也就是getCnt+2好的景点放到maxHeap里，这样我们能方便的从堆顶里取到getCnt+2好的数据
    - get：get调用以后我们的目标变成了原来的getCnt+1 + 1好的，如果maxHeap不是空，那么就从maxHeap取出来剩下的最好的，放入minHeap中，这样minHeap的对顶，就是最好的第 getCnt+1 + 1个，当然最后我们还要++getCnt的；


```cpp
class SORTracker {
public:
    using sight = pair<string, int>;
    static constexpr auto minCmp = [](const sight& a, const sight& b) {
        return a.second > b.second || ((a.second == b.second) && (a.first < b.first));
    };
    
    static constexpr auto maxCmp = [](const sight& a, const sight& b) {
        return a.second < b.second || ((a.second == b.second) && (a.first > b.first));
    };

    priority_queue<sight, vector<sight>, decltype(minCmp)> minHeap;
    priority_queue<sight, vector<sight>, decltype(maxCmp)> maxHeap; // the best getCnt + 1's sights

    int getCnt;
    SORTracker() : minHeap(minCmp), maxHeap(maxCmp), getCnt(0) {

    }
    
    void add(string name, int score) {
        // keep there are always best getCnt + 1's in the minHeap
        minHeap.push({name, score});
        if(minHeap.size() > getCnt + 1) {
            maxHeap.push(minHeap.top()); 
            minHeap.pop();
        }
        //cout << "curTop: " << minHeap.top().first << " " << minHeap.top().second << endl;
    }
    
    string get() {
        ++getCnt;
        auto res = minHeap.top().first;
        if(!maxHeap.empty()) {
            minHeap.push(maxHeap.top());
            maxHeap.pop();
        }
        return res;
    }
};
```