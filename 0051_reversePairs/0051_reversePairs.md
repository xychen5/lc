## 剑指 Offer 51. 数组中的逆序对

### 1 题目
[https://leetcode-cn.com/problems/shu-zu-zhong-de-ni-xu-dui-lcof/](https://leetcode-cn.com/problems/shu-zu-zhong-de-ni-xu-dui-lcof/)

### 2 解题思路
- 1 思路：
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
```cpp
        sort(sortNoNums.begin(), sortNoNums.end(), std::less<int>());
        
        for(auto& num : nums) {
            num = lower_bound(sortNoNums.begin(), sortNoNums.end(), num) - sortNoNums.begin() + 1;
        }
```
相似题目：
[https://leetcode-cn.com/problems/count-of-smaller-numbers-after-self/](https://leetcode-cn.com/problems/count-of-smaller-numbers-after-self/)


```cpp
class Solution {
public:
    class BIT {
    public: 
        vector<int> tree;
        int n;
        BIT(int _n): n(_n) , tree(_n + 1){cout << "init Done!" << endl;};

        // find prefixSum with index x
        int query(int x) {
            int sum = 0;
            while(x > 0) {
                sum += tree[x];
                x -= (x&(-x));
            }
            return sum;
        }

        // update x with delta val v
        void update(int x, int v) {
            cout << "d1"<< endl;
            while(x <= n) {
                tree[x] += v;
                x += (x&(-x));
            }
            cout << "d2"<< endl;
        }
    };

    int reversePairs(vector<int>& nums) {
        // desrialization, using sort no to denote the value
        vector<int> sortNoNums = nums;
        sort(sortNoNums.begin(), sortNoNums.end(), std::less<int>());
        
        for(auto& num : nums) {
            num = lower_bound(sortNoNums.begin(), sortNoNums.end(), num) - sortNoNums.begin() + 1;
        }

        // using binary indexed tree to statistic the reversePair num
        // start from the end of nums, so that the prefix in BIT means the reversePiar num
        int ans = 0;
        BIT bit(nums.size());
        for(int i = nums.size() - 1; i >= 0; --i) {
            ans += bit.query(nums[i] - 1); // cause only elements right than current num[i] will contribute to the ans
            cout << ans << endl;
            // statistic frequence of nums[i]
            bit.update(nums[i], 1);
        }

        return ans;
    }
};
```