# lc
记录lc中的题解, 所有文件夹的命名是以<题号><题目名称>命名的<br>

每个文件夹里有原题的题目描述以及解答和源码。
![https://cdn.jsdelivr.net/gh/xychen5/blogImgs@main/imgs/index.2nk8zx8gogc0.jpg](https://cdn.jsdelivr.net/gh/xychen5/blogImgs@main/imgs/index.2nk8zx8gogc0.jpg)
# solve list
## 1 帮助符号
这里给出问题类型的简称：
| 数据结构 |  |
| - | - |
| 树结构 | tree |
| 图结构 | graph |
| 栈 | stack |
| 单调栈 | monotonous stack(monoStack) |
| 单调队列 | monotonous queue(monoQueue) |
| 最大/最小堆 | min/max heap |
| 数组 | arr |
| 链表 | linked list(ll) |
| 优先队列 | priority queue |
| 哈希 | hash |
| 二叉搜索树 | BST |
----------------------
| 算法 |  |
| - | - |
| 动态规划 | dp |
| dfs | dfs |
| bfs | bfs |
| 并查集 | unionSet(us) |
| 二分查找 | binSear/bs |
| 排列组合 | permutation/combination(perm&comb) |
| 回溯 | back tracking(bt) |
| 原地查找改变 | saveSpace |
| 前缀和 | prefixSum |
| 模拟 | sim |
| 数学 | math |
| 滑动窗口 | mw |

## 2 题解
| 题号 | 题名 | 类型 | 链接 | 使用算法 |
| - | - | - | - | - |
| 0032 | 最长有效括号 | dp,arr,stack | [https://leetcode-cn.com/problems/longest-valid-parentheses/](https://leetcode-cn.com/problems/longest-valid-parentheses/) | - |
| 0053 | 最大子序和 | dp,arr | [https://leetcode-cn.com/problems/maximum-subarray/](https://leetcode-cn.com/problems/maximum-subarray/) | - |
| 0062 | 不同路径1 | dp | [https://leetcode-cn.com/problems/unique-paths/](https://leetcode-cn.com/problems/unique-paths/) | - |
| 0063 | 不同路径2 | dp | [https://leetcode-cn.com/problems/unique-paths-ii/](https://leetcode-cn.com/problems/unique-paths-ii/) | - |
| 0067 | 旋转链表 | ll | [https://leetcode-cn.com/problems/rotate-list/](https://leetcode-cn.com/problems/rotate-list/) | - |
| 0073 | 矩阵置零 | saveSpace | [https://leetcode-cn.com/problems/set-matrix-zeroes/](https://leetcode-cn.com/problems/set-matrix-zeroes/) | - |
| 0074 | 搜索二维矩阵 | bs | [https://leetcode-cn.com/problems/search-a-2d-matrix/](https://leetcode-cn.com/problems/search-a-2d-matrix/) | - |
| 0084 | 柱状图中最大矩形 | monoStack | [https://leetcode-cn.com/problems/largest-rectangle-in-histogram/](https://leetcode-cn.com/problems/largest-rectangle-in-histogram/) | - |
| 0085 | 最大矩形 | monoStack | [https://leetcode-cn.com/problems/maximal-rectangle/submissions/](https://leetcode-cn.com/problems/maximal-rectangle/submissions/) | - |
| 0109 | 链表转BST | ll,bst | [https://leetcode-cn.com/problems/convert-sorted-list-to-binary-search-tree/](https://leetcode-cn.com/problems/convert-sorted-list-to-binary-search-tree/) | 递归，分治 |
| 0123 | 买卖股票的最佳时机 | dp | [https://leetcode-cn.com/problems/best-time-to-buy-and-sell-stock-iii/](https://leetcode-cn.com/problems/best-time-to-buy-and-sell-stock-iii/) | - |
| 0124 | 二叉树中的最大路径和 | dp | [https://leetcode-cn.com/problems/binary-tree-maximum-path-sum/](https://leetcode-cn.com/problems/binary-tree-maximum-path-sum/) | - |
| 0141 | 单向链表有回环 | ll, saveSpace | [https://leetcode-cn.com/problems/linked-list-cycle/](https://leetcode-cn.com/problems/linked-list-cycle/) | floyd判圈 |
| 0142 | 单向链表有回环2 | ll, saveSpace | [https://leetcode-cn.com/problems/linked-list-cycle-ii/](https://leetcode-cn.com/problems/linked-list-cycle-ii) | floyd判圈 |
| 0209 | 长度最小和大于k的子数组 | mw,prefixSum | [https://leetcode-cn.com/problems/shortest-subarray-with-sum-at-least-k/](https://leetcode-cn.com/problems/shortest-subarray-with-sum-at-least-k/) | 滑动窗口，前缀和 |
| 0233 | 数字1的个数 | perm/comb | [https://leetcode-cn.com/problems/number-of-digit-one/](https://leetcode-cn.com/problems/number-of-digit-one/) | - |
| 0313 | 超级丑数 | heap | [https://leetcode-cn.com/problems/super-ugly-number/](https://leetcode-cn.com/problems/super-ugly-number/) | - |
| 0328 | 奇偶链表 | ll, saveSpace | [https://leetcode-cn.com/problems/odd-even-linked-list/](https://leetcode-cn.com/problems/odd-even-linked-list/) | - |
| 0413 | 等差数列划分 | arr | [https://leetcode-cn.com/problems/arithmetic-slices/](https://leetcode-cn.com/problems/arithmetic-slices/) | - |
| 0416 | 分割等和子集 | dp,arr | [https://leetcode-cn.com/problems/partition-equal-subset-sum](https://leetcode-cn.com/problems/partition-equal-subset-sum) | - |
| 0445 | 两数相加 | ll | [https://leetcode-cn.com/problems/add-two-numbers-ii/submissions/](https://leetcode-cn.com/problems/add-two-numbers-ii/submissions/) |  |
| 0466 | 等差数列划分 | dp,arr | [https://leetcode-cn.com/problems/arithmetic-slices-ii-subsequence/](https://leetcode-cn.com/problems/arithmetic-slices-ii-subsequence/) | - |
| 0516 | 最长回文子序列 | dp | [https://leetcode-cn.com/problems/longest-palindromic-subsequence/](https://leetcode-cn.com/problems/longest-palindromic-subsequence/) | - |
| 0526 | 优美排列 | bt,arr | [https://leetcode-cn.com/problems/beautiful-arrangement](https://leetcode-cn.com/problems/beautiful-arrangement) | - |
| 0560 | 子串和为k | arr,hash | [https://leetcode-cn.com/problems/subarray-sum-equals-k/](https://leetcode-cn.com/problems/subarray-sum-equals-k/) | prefixSum |
| 0611 | 有效三角个数 | dp,arr | [https://leetcode-cn.com/problems/valid-triangle-number/](https://leetcode-cn.com/problems/valid-triangle-number/) | - |
| 0684 | 冗余链接 | tree,us,graph | [https://leetcode-cn.com/problems/redundant-connection](https://leetcode-cn.com/problems/redundant-connection) | 并查集 |
| 0685 | 冗余链接2 | tree,us,graph | [https://leetcode-cn.com/problems/redundant-connection-ii](https://leetcode-cn.com/problems/redundant-connection-ii) | 并查集 |
| 0862 | 和大于k的最短子数组长度 | monoQueue,prefixSum | [https://leetcode-cn.com/problems/shortest-subarray-with-sum-at-least-k/](https://leetcode-cn.com/problems/shortest-subarray-with-sum-at-least-k/) | 单调队列，前缀和 |
| 0874 | 模拟机器人行走 | sim | [https://leetcode-cn.com/problems/walking-robot-simulation/](https://leetcode-cn.com/problems/walking-robot-simulation/) | - |
| 1171 | 移除0和子链表 | ll,prefixSum | [https://leetcode-cn.com/problems/remove-zero-sum-consecutive-nodes-from-linked-list/](https://leetcode-cn.com/problems/remove-zero-sum-consecutive-nodes-from-linked-list/) | 前缀和 |
| 1292 | 最大正方形边长 | bs,prefixSum | [https://leetcode-cn.com/problems/maximum-side-length-of-a-square-with-sum-less-than-or-equal-to-threshold/](https://leetcode-cn.com/problems/maximum-side-length-of-a-square-with-sum-less-than-or-equal-to-threshold/) | 前缀和 |
| 1472 | 浏览器历史 | stack | [https://leetcode-cn.com/problems/design-browser-history/](https://leetcode-cn.com/problems/design-browser-history/) | - |
| 1546 | 非重叠子数组和的个数 | prefixSum,hash | [https://leetcode-cn.com/problems/maximum-number-of-non-overlapping-subarrays-with-sum-equals-target/submissions/](https://leetcode-cn.com/problems/maximum-number-of-non-overlapping-subarrays-with-sum-equals-target/submissions/) | 前缀和 |
| 1583 | 不开心朋友个数 | arr,hash | [https://leetcode-cn.com/problems/count-unhappy-friends/](https://leetcode-cn.com/problems/count-unhappy-friends/) | - |
| 1590 | 最短子数组移除被k整除 | prefixSum,hash | [https://leetcode-cn.com/problems/make-sum-divisible-by-p/](https://leetcode-cn.com/problems/make-sum-divisible-by-p/ | 前缀和，hash |
| 1669 | 合并两个链表 | ll | [https://leetcode-cn.com/problems/merge-in-between-linked-lists/](https://leetcode-cn.com/problems/merge-in-between-linked-lists/) | - |
| 1703 | 最小移动数量获得连续k个1 | math,prefixSum,mw | [https://leetcode-cn.com/problems/minimum-adjacent-swaps-for-k-consecutive-ones](https://leetcode-cn.com/problems/minimum-adjacent-swaps-for-k-consecutive-ones) | 滑动窗口,前缀和 |
| 1760 | 球的出口 | sim | [https://leetcode-cn.com/problems/where-will-the-ball-fall/](https://leetcode-cn.com/problems/where-will-the-ball-fall/) | - |
| 1877 | 最小最大数对和 | arr | [https://leetcode-cn.com/problems/minimize-maximum-pair-sum-in-array/](https://leetcode-cn.com/problems/minimize-maximum-pair-sum-in-array/) | - |
|  |  |  |  |  |
