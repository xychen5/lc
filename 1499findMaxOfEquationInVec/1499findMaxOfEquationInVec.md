## 1499findMaxOfEquationInVec 满足不等式的最大值

### 1 题目
[https://leetcode.cn/problems/max-value-of-equation/](https://leetcode.cn/problems/max-value-of-equation/)

### 2 解题思路
- 1 解题思路:
  - 1.1 首先能想到的是，对于数字point[i]的xy，我们可以维护一个window，其中放了所有xi,yi,满足|xi - x| <= k，然后我们遍历这个窗口的所有值，找到一个答案，但是这样复杂度是nk有点大了
  - 1.2 我们考虑一下，是不是需要考虑point[i]的左右距离为k的值？不需要，因为上面显然存在重复计算，比如x坐标为1,3,5的三个点，k = 100好了，对于1，考虑了3,5，对于3考虑了1，5，然而13的组合在x=1和这个点已经考虑过了，所以我们可以只考虑坐标的左半边或者右半边，我们以考虑左半边为例子
  - 1.3 由于是左半边，我们遍历的点称之为xj，那么xi就是左边的所有点，我们如何快速拿到结果呢？
    - res = for i < j && xj - xi <= k: max(yi + yj + |xi - xj|) = max(yj + xj + yi - xi)，去掉了绝对值
    - 然后可以看出来对于一个j，不就是求它左边窗口（窗口内的值需要满足：xj - xi <= k）中yi - xi的最大值吗？那不就是用priority_queue存起来就行了
    - 注意一点的是：当窗口中的xi, xj - xi > k可以放心pop，因为若当前的j都距离xi太远了，那后面的只会更加的遥远，于是可以pop 

```cpp
class Solution {
public:
    
    using pii = pair<int, int>;
 
    static constexpr auto cmp = [](const pii& a, const pii& b) {
        return a.second < b.second;
    };

    int findMaxValueOfEquation(vector<vector<int>>& points, int k) {
        // first: yi + yj + |xi - xj| == yj + xj + yi - xi
        // so: for each j, we shall found the biggest yi - xi and |xj - xi| <= k
        // using a priority_queue to store those yi - xi
        
        int n = points.size();
        // priority_queue<pii, vector<pii>, decltype(cmp)> maxHeapOri(cmp);
        priority_queue<pii, vector<pii>, decltype(cmp)> maxHeap(cmp);
        maxHeap.push({points[0][0], points[0][1] - points[0][0]}); // init it

        int curRes = INT_MIN;
        for(int j = 1; j < n; ++j) {
            // |xj - xi| <= k, we should consider xj - xi <= k or xi - xj <= k
            // but we can only consider those xj > xi, cause, when we try to consider xj < xi, 
            // the bigger J after j will be like xi, so all cases coverd
            int xj = points[j][0];
            int yj = points[j][1];
            // cout << "dealing: " << xj << " " << yj << endl;
            // auto maxHeap = maxHeapOri;
            while(1) {
                if(maxHeap.empty()) {
                    break;
                }

                auto t = maxHeap.top();
                int xi = t.first;
                int delatI = t.second;
                if(xi != xj ) {
                    if(xj - xi > k) {
                        // cout << "pop: " << xi << endl;
                        maxHeap.pop();
                    } else {
                        curRes = max(curRes, yj + xj + delatI);
                        break;
                    }    
                } else {
                    break;
                }
            }
            maxHeap.push({points[j][0], points[j][1] - points[j][0]});
        }
        return curRes;
        
    }
}
```