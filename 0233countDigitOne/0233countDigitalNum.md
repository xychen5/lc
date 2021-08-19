## 0233 1的个数

### 1 题目
[https://leetcode-cn.com/problems/number-of-digit-one/](https://leetcode-cn.com/problems/number-of-digit-one/)

### 2 思路
#### 2.1 单独求解每一位可能出现的1个个数，然后求和即可。
这里举例子：
5170
对于如下每一位的可能如下
10^0: 567
10^1: (51 + 1) * 10
10^2: (51 - 1) * 100 + 70 + 1
10^3: (1) * 1000
