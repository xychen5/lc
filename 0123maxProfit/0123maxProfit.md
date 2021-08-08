## 0123买卖股票最佳时机

### 1 题目：
[https://leetcode-cn.com/problems/best-time-to-buy-and-sell-stock-iii/](https://leetcode-cn.com/problems/best-time-to-buy-and-sell-stock-iii/)

### 2 解题思路：
首先如何表示两次交易？
- 1 采用 buy1， sell1，buy2，sell2
- 2 首先考虑一点： 对于只有一次交易机会，那么问题就很简单：
```cpp
        int b1 = -prices[0], s1 = 0, b2 = -prices[2], s2 = 0;
        for(dayIdx: 0 -> n):
            b1 = max(b1, -prices[dayIdx]);
            s1 = max(s1, b1 + prices[dayIdx]);
```
注意s1，记录的是过往最高收入和今天的最高收益的比较后的最大值，也就是s1记录了过去的那些b1们对应的最大收入。
- 3 以上是第一次交易，加上第二次交易呢？
```cpp
        int b1 = -prices[0], s1 = 0, b2 = -prices[2], s2 = 0;

        for(size_t dayIdx = 1; dayIdx < prices.size(); ++dayIdx) {
            b1 = max(b1, -prices[dayIdx]);
            s1 = max(s1, b1 + prices[dayIdx]);
            b2 = max(b2, s1-prices[dayIdx]);
            s2 = max(s2, b2 + prices[dayIdx]);
        }
```
无非就是，首先，什么时候买入？肯定是离我卖出也就是s1达到距离最大的时候买入，于是有了b2的状态转移，
卖出当然是在所有b2们里，能达到的最大收益的时候卖出。

很巧妙的一点： s1和b2联系上了，因为在第一第二笔交易之间，必须先完成第一笔，才有第二笔。

### 2.1 我能想到的思路，有些暴力
首先我想到的是2次交易，那么两次交易有个分水岭，我记做k，
遍历k，在k的左右分别寻求最大交易即可达到最优。
