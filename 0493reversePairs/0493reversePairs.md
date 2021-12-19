## 0493 翻转对

### 1 题目
[https://leetcode-cn.com/problems/reverse-pairs/](https://leetcode-cn.com/problems/reverse-pairs/)

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
  - 对于每个j，找位于它之前的数字，满足：nums[i] > 2*nums[j]
  - 找的方法为用总体减去目标的补集：用nums[j]之前所有的数字的个数，减去小于等于nums[j] * 2的数字就行
> for each j, find those nums[i]:
> which satisty: i < j && nums[i] > 2*nums[j]
> 
> so, we can get this by: using all to sub those nums[i] <= nums[j] * 2 to get the res
> preSum[1 -> 2\*n] - preSum[1 -> 2\*nums[j]]

实现代码如下：
```cpp
class Solution {
public:

    class BITree {
    public:
        long long n;
        vector<long long> tree;
        BITree(long long _n) : n(_n), tree(_n + 1) {}
        
        long long lowBit(long long x) {
            return x & (-x);
        }

        long long query(long long x) {
            long long sum = 0;
            while(x > 0) {
                sum += tree[x];
                x -= lowBit(x);
            }
            return sum;
        }

        void update(long long x, long long val) {
            while(x <= n) {
                tree[x] += val;
                x += lowBit(x);
            }
        }
    };

    int reversePairs(vector<int>& nums) {
        // deserialization
        vector<long long> tmpNums;
        for(auto num : nums) {
            tmpNums.emplace_back(num);
            tmpNums.emplace_back(num * 2LL);
        }
        sort(tmpNums.begin(), tmpNums.end(), [](long a, long b) {
            return a < b;
        });

        // for(auto& num : tmpNums) { cout << "tmp: " << num << endl;}
        
        // for(auto& num : nums) {
        //     num = lower_bound(tmpNums.begin(), tmpNums.end(), num) - tmpNums.begin() + 1; //  +1 to avoid update(0, 1) failure
        // }

        for(auto& num : nums) { cout << "num No: " << num << endl;}

        // deserialization
        int idx = 1;
        unordered_map<long long,long long> numToIdx;
        for(auto num : tmpNums) {
            numToIdx[num] = idx ++;
        }

        int n = nums.size();
        int ans = 0;
        BITree tree(2 * n);
        // for each j, find those nums[i]:
        // which satisty: i < j && nums[i] > 2*nums[j]
        // 
        // so, we can get this by: using all to sub those nums[i] <= nums[j] * 2 to get the res
        // preSum[1 -> 2*n] - preSum[1 -> 2*nums[j]]
        for(int i = 0; i < n; ++i) {
            // cout << "counting: " << nums[i] << endl;
            // attention the diff between 2LL and 2
            ans += (tree.query( 2LL*n ) - tree.query(numToIdx[2LL * nums[i]]));
            tree.update(numToIdx[nums[i]], 1);
        }

        return ans;
    }
}
```
