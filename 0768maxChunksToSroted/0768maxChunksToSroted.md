## 0768 最多能完成排序的块 II maxChunksToSroted

### 1 题目
[https://leetcode-cn.com/problems/max-chunks-to-make-sorted-ii](https://leetcode-cn.com/problems/max-chunks-to-make-sorted-ii)

### 2 解题思路
- 1 普通思路：
  - 1.1 利用已经排好序的数组，和当前数组进行比较，得到分块方式，也就是题目的提示：
> Each k for which some permutation of arr[:k] is equal to sorted(arr)[:k] is where we should cut each chunk.
  - 1.2 具体算法：
    - 记原数组为arr，然后其排序为sortArr，而后遍历arr，如何确定一个下标k是否为chunk的分割点呢？
    - 使用hashA记录arr[:k]子数组中每个元素的出现次数，使用diffCount**记录arr[:k]和sortArr[:k]（在两个数组里出现次数不同的）元素个数**
    - 当diffCount为0，就找到一个k，最后返回所有diffCount为0的地方即可
  - 1.3 普通解法：
```cpp
class Solution {
public:

    int maxChunksToSorted(vector<int>& arr) {
        // monoStack: every ele in mono represent: the biggest value in a chunk
        unordered_map<int, int> hash;

        // diffCnt, the size of those numbers whose cnt are not equal in arr[:k] and sortArr[:k]
        int ans = 0, n = arr.size(), diffCnt = 0;
        vector<int> sortArr(arr);
        sort(sortArr.begin(), sortArr.end(), std::less<int>());
        for(int k = 0; k < n; ++k) {
            ++ hash[arr[k]];
            if(hash[arr[k]] == 1) {
                diffCnt++;
            } 
            if(hash[arr[k]] == 0){
                diffCnt--;
            }

            -- hash[sortArr[k]];
            if(hash[sortArr[k]] == 0) {
                diffCnt--;
            } 
            if(hash[sortArr[k]] == -1) { // sortArr[k] is redundant
                diffCnt++;
            }

            ans += diffCnt == 0;
        }
        
        return ans;
    }
};
```

- 2 单调栈：
  - 2.1 考虑例子： 1 4 3 7 5，很容易发现，就三个分块，然后arr的单调增栈为1 4 7，刚好为每个分块的最大值，所以有这么一个单调栈定义：**单调栈里存入的数字为每个分块的最大值**
  - 2.2 当然这也有问题，会涉及到单调栈需要合并分块的情况： 1 4 3 7 5 2，当没检测到2的时候，单调栈为3个分块，最大值分别为1，4，7，当检测到2的时候，我们需要先弹出所有比2大的分块的最大值，因为2在这些分块后面意味着必须将2和这些分块合并，这样才能保证最终从小到大的排序，然后压入合并的这些分块里的最大值，也就是遇到2之前单调栈的栈顶 7，单调栈变成了1，7
  - 2.3 具体看代码：单调栈解法：[可视化参考](https://leetcode-cn.com/problems/max-chunks-to-make-sorted-ii/solution/768-zui-duo-neng-wan-cheng-pai-xu-de-kuai-iihua-do/#%E6%96%B9%E6%B3%95-2-%E5%8D%95%E8%B0%83%E9%80%92%E5%A2%9E%E6%A0%88)
``` cpp
class Solution {
public:

    int maxChunksToSorted(vector<int>& arr) {
        // monoStack: every ele in mono represent: the biggest value in a chunk
        vector<int> mono = {INT_MIN}; // from small to bigger
        int n = arr.size();
        for(int i = 0; i < n; ++i) {
            if(arr[i] >= mono.back()) {
                mono.emplace_back(arr[i]);
            }  else { // arr[i] < mono.back()
                // merge the chunk untill arr[i] > mono.back()
                int curChunkMax = mono.back();
                while(mono.back() > arr[i]) {
                    mono.pop_back();
                }
                mono.emplace_back(curChunkMax);
            }
        }
        
        return mono.size() - 1;
    }
};
```