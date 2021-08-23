## 0313 n大超级丑数

### 1 题目：

[https://leetcode-cn.com/problems/super-ugly-number/](https://leetcode-cn.com/problems/super-ugly-number/)


### 2 解题思路：
- 1 最小堆：
  - 主要想法是，维护一个最小堆，先压入1，然后每次取出堆顶的元素，和primes[]里面的每一个质因数乘积，这样下去第n次然后取出的堆顶必然是第n小的值，这里做一个思想假设，假设最小值一是质因数的第一个数字的n次方（比如primes里有一个2，其他都是无穷大的质数），那么上面的算法就能选择出2的n次方为最小值。
- 2 动态规划：
  - 参考：[https://leetcode-cn.com/problems/super-ugly-number/solution/313-chao-ji-chou-shu-dong-tai-gui-hua-by-1cfu/](https://leetcode-cn.com/problems/super-ugly-number/solution/313-chao-ji-chou-shu-dong-tai-gui-hua-by-1cfu/)
  - 核心思想: 维护一个和primes等长的数组pointer，该数组的第i个值，记录了（在根据当前丑数数组选出下一个数组时）primes里面第i个质数应该和丑数数组里的哪一个丑数相乘，这个pointer[i]显然会随着计算过程而递增

