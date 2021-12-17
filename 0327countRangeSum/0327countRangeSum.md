## 0327. 区间和的个数

### 1 题目
[https://leetcode-cn.com/problems/count-of-range-sum/](https://leetcode-cn.com/problems/count-of-range-sum/)

题和逆序数对的计算方式相同：[https://leetcode-cn.com/problems/shu-zu-zhong-de-ni-xu-dui-lcof/](https://leetcode-cn.com/problems/shu-zu-zhong-de-ni-xu-dui-lcof/)
就是做了一个小改变而已，很多统计区间值的，st-ed < tar, 本来是让你找一个st，ed的对子的，那么就会转换思路为：
对于每一个ed找st，什么样的呢？ st < ed + tar
然后找这样的st就有很多方法，比如hash，前缀和，bitree，priority_queue

### 2 解题思路
- 1 求逆序对的思路：
  - 1.1 首先注意到：对于数组{5，5,2,3,6}而言，得到每个value的个数的统计：
    - index  ->  1 2 3 4 5 6 7 8 9
    - value  ->  0 1 1 0 2 1 0 0 0
  - 1.2 那么上述过程中，比如对于5，其贡献的逆序数对为5之前所有数字出现次数的和，也就是value数组中2之前的前缀和！
- 2 那么如何快速获得前缀和呢？考虑使用BST来获取，参考:[https://xychen5.github.io/2021/12/15/dataStructure-BinaryIndexedTree/](https://xychen5.github.io/2021/12/15/dataStructure-BinaryIndexedTree/)
  - 2.1 整体思路如下：
    - a 使用数字在数组中的排名来代替数字（这不会对逆序数对的个数产生影响）
    - b 对数组nums中的元素nums[i]从右到左构建BITree（i 从 n-1 到 0），注意，BITree所对应的前缀和是数组里数字出现次数的和
      - 比如进行到nums[i]，那么nums[i]右边的数字都已经统计了他们的出现次数，而后获取nums[i] - 1的前缀和，即可获取所有 < nums[i]的数字在nums[i:n]中的出现次数之和，也就是nums[i]贡献的逆序数对的个数
      - **之所以是逆序遍历构建BITree，是因为对于nums[i]，它能够贡献的逆序数对的个数仅仅出现在它的右侧，所以需要在右侧进行**
  - 2.2 额外说一下数组离散化，也就是不关系数字大小本身，只关心他们之间的相对排位
- 3 那么小改变在哪里呢？
  - 就是查一次查不出来了，要查两次做一个差
```cpp
        for a valid s(i, j) we shall find:
             preSum[j] - ub <= preSum[i] <= preSum[j] - lb
        we just need to statistic those preSum[i] for each j
```
实现代码如下：
```cpp
class Solution {
public:
    // when count the num, try to use BItree to count the appeared num, prefixSum to 
    // get how many < curNum will be fast
    class BITree{
    public:
        int n;
        vector<int> tree;
        BITree (int _n) : n(_n), tree(_n + 1) {}

        int lowBit(int x) {
            return x & (-x);
        }

        int query(int x) {
            int sum = 0;
            while(x > 0) {
                sum += tree[x];
                x -= lowBit(x);
            }
            return sum;
        }

        void update(int x, int val) {
            while(x <= n) {
                // cout << "x and tree[x] " << x << "->" << tree[x] << endl;
                tree[x] += val;
                x += lowBit(x);
            }
        }
    };


    int countRangeSum(vector<int>& nums, int lower, int upper) {
        unordered_map<int, int> numToIdx;
        set<long long> tmpNums;
        vector<long long> prefixSum = {0};

        for(int i = 0; i < nums.size(); ++i) {
            prefixSum.emplace_back(nums[i] + prefixSum.back());
        }

        for(auto ps : prefixSum) {
            tmpNums.insert(ps);
            tmpNums.insert(ps - lower);
            tmpNums.insert(ps - upper);
        }
        
        int i = 1;
        for(auto num : tmpNums) {
            numToIdx[num] = i++;
        }

        // for a valid s(i, j) we shall find:
        //     preSum[j] - ub <= preSum[i] <= preSum[j] - lb
        // we just need to statistic those preSum[i] for each j
        int n = tmpNums.size();
        BITree tree(n + 1);
        long long ans = 0;
        for(int j = 0; j < prefixSum.size(); ++j) {
            int leftBound = numToIdx[prefixSum[j] - upper];
            int rightBound = numToIdx[prefixSum[j] - lower];
            // cout << "lb, rb = " << leftBound << " " << rightBound << endl;
            ans += (tree.query(rightBound) - tree.query(leftBound - 1));
            // cout << "ans = " << ans << "preFixSumSize = " << prefixSum.size() << endl;
            tree.update(numToIdx[prefixSum[j]], 1); // avoid 0 to produce dead loop
        }
        return ans;
    }
};
```