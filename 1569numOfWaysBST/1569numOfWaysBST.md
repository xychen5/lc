## 1569. 将子数组重新排序得到同一个二叉查找树的方案数

### 1 题目
[https://leetcode-cn.com/problems/number-of-ways-to-reorder-array-to-get-same-bst/](https://leetcode-cn.com/problems/number-of-ways-to-reorder-array-to-get-same-bst/)

### 2 解题思路
- 1 阅读提示即可，大致思路如下：
  - 1.1 首先，意识到第一个数必然为二叉树的root，那么找出左边的节点和右边的节点分别记为lt，和rt
  - 1.2 首先假设我们知道了以lt和rt的不改变子树结构的重排序方案数字为findWays(lt), findWays(rt)
  - 1.3 那么我们只需要思考，如何利用1.2的结果来获得当前root的结果：
    - 很显然，我们只需要确定lt和rt在root对应的整个序列(长度记录为n)中放置方法有多少种方案？进一步分析：在不改变lt序列内部相对顺序的情况下，找出有多少繁殖lt序列的方法？那么不就是n-1中选出lt长度记为k个位置的方法数字吗？
    - 上述答案显而易见： c(n-1, k) = (n-1)!/(n-1-k)!/(k)!;
- 2 接着就是大数问题：由于n最大为1000，它的阶乘显然溢出，于是上面的直接计算阶乘的方案就失效，采用动动态规划的方法去算阶乘：
  - c(n, k) = c(n-1, k) + c(n-1, k-1)
  - 直观上来看假设原来只有n-1个物品选择k个，现在多加了一个物品，还是选择k个，那么方案数增加了：从 n 个物品中选择 k 个的方案数，等于从前 n-1 个物品中选择 k 个的方案数，加上从前 n-1 个物品中选择 k-1个（再选上第 nn 个物品）的方案数之和。

```cpp
class Solution {
public:
    static constexpr long long largePrime = 1000000007;
    
    vector<long long> factorial;
    
    vector<vector<int>> c;

    int numOfWays(vector<int>& nums) {
        long long ans = 0;
        int n = nums.size();
        factorial.resize(1000, 1);
        // for(long long i = 1; i < 1000; ++i) {
        //     factorial[i] = i * (factorial[i-1] % largePrime);
        //     // cout << i << "->" << factorial[i] << endl;
        //     factorial[i] %= largePrime;
        // }
        
        c.assign(n, vector<int>(n));
        c[0][0] = 1;
        // cal c(n, m) = c(n-1, m) + c(n-1, m-1);
        for(int i = 1; i < n; ++i) {
            c[i][0] = 1;
            for(int j = 1; j < n; ++j) {
                c[i][j] = (c[i-1][j] + c[i-1][j-1]) % largePrime;
            }
        }
        
        ans = findWays(nums);

        return ans - 1;
    }

    long long findWays(vector<int>& nums) {
        int n = nums.size();
        if(n <= 2) {
            return 1;
        }
        
        int root = nums[0];
        vector<int> left;
        vector<int> right;
        for(int i = 1; i < nums.size(); ++i) {
            if(nums[i] < root) {
                left.emplace_back(nums[i]);
            } else {
                right.emplace_back(nums[i]);
            }
        }
        
        // that means:
        // for the left tree, all nodes shall seat in the other places(and not change the relative order)
        // except root pos find the way out(the way shall equal: 
        //     pick nodes size seat from all seats, that is c(n, m-1);
        // ) and mutiply the two subTree arrange way num
        int seats = n - 1;
        int nodesToSeat = left.size();
        // cout << "c(n, k) " << seats << " -> " << nodesToSeat << " = " << c[seats][nodesToSeat] << endl;
        // cout << "l r : " << findWays(left) << "  " << findWays(right) << endl;
        // return ((findWays(left)  % largePrime )* (findWays(right) % largePrime)) * (getWaysForCurLevel(seats, nodesToSeat) % largePrime);
        return findWays(left)  % largePrime * findWays(right) % largePrime * c[seats][nodesToSeat] % largePrime;
    }

    long long getWaysForCurLevel(int seats, int nodesToSeat) {
        cout << "c(n, k)2 :" << factorial[seats] << " " << factorial[nodesToSeat] << " " << factorial[seats - nodesToSeat] << endl;; 
        return factorial[seats] / factorial[nodesToSeat] / factorial[seats - nodesToSeat];
    }
};
```
