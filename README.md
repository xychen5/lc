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
| 最大/最小堆/优先队列 | min/max heap |
| 数组 | arr |
| 链表 | linked list(ll) |
| 优先队列 | priority queue |
| 哈希 | hash |
| 二叉搜索树 | bst |
| 差分数组 | diff array(da) |
| 强联通子图 | scc(strongly connected components)|
| 二叉索引树(树状数组) | bst(binary indexed tree) |
----------------------
| 算法 |  |
| - | - |
| 动态规划 | dp |
| dfs | dfs |
| bfs | bfs |
| 并查集 | unionSet(us) |
| 二分查找 | binSear/bs |
| 排列组合 | permutation/combination(perm,comb) |
| 字典序 | lexical order/dictionary order(dictOrder) |
| 回溯 | back tracking(bt) |
| 递归 | recursive(recur) |
| 原地查找改变 | saveSpace |
| 前缀和 | prefixSum |
| 模拟 | sim |
| 数学 | math |
| 滑动窗口 | mw |
| 极大极小 | minimax |
| 拓扑排序 | topoSort |
| 逆向思维 | reverseThink |
| 取巧 | trick |

## 2 题解
| 题号 | 题名 | 类型 | 链接 | 使用算法 |
| - | - | - | - | - |
| 0000_interview_0409BSTSequence | 面试题 04.09. 二叉搜索树序列 | bst,recur | [https://leetcode-cn.com/problems/bst-sequences-lcci/](https://leetcode-cn.com/problems/bst-sequences-lcci/) | bst,recur |
| 0010 | 正则表达式匹配  | recur | [https://leetcode-cn.com/problems/regular-expression-matching](https://leetcode-cn.com/problems/regular-expression-matching) | recur |
| 0025 | k个一组翻转链表 | recur,ll | [https://leetcode-cn.com/problems/reverse-nodes-in-k-group/](https://leetcode-cn.com/problems/reverse-nodes-in-k-group/) | recur,ll |
| 0032 | 最长有效括号 | dp,arr,stack | [https://leetcode-cn.com/problems/longest-valid-parentheses/](https://leetcode-cn.com/problems/longest-valid-parentheses/) | - |
| 0043_1 | 数1的个数 | math | [https://leetcode-cn.com/problems/1nzheng-shu-zhong-1chu-xian-de-ci-shu-lcof/](https://leetcode-cn.com/problems/1nzheng-shu-zhong-1chu-xian-de-ci-shu-lcof/) | math |
| 0046 | 全排列 | perm |[https://leetcode-cn.com/problems/permutations/](https://leetcode-cn.com/problems/permutations/)  | perm |
| 0047 | 去重全排列 | perm | [https://leetcode-cn.com/problems/permutations-ii/](https://leetcode-cn.com/problems/permutations-ii/) | perm |
| 0051_1 | 数组中逆序数对个数 | bit | [https://leetcode-cn.com/problems/shu-zu-zhong-de-ni-xu-dui-lcof/](https://leetcode-cn.com/problems/shu-zu-zhong-de-ni-xu-dui-lcof/) | bit |
| 0053 | 最大子序和 | dp,arr | [https://leetcode-cn.com/problems/maximum-subarray/](https://leetcode-cn.com/problems/maximum-subarray/) | - |
| 0062 | 不同路径1 | dp | [https://leetcode-cn.com/problems/unique-paths/](https://leetcode-cn.com/problems/unique-paths/) | - |
| 0063 | 不同路径2 | dp | [https://leetcode-cn.com/problems/unique-paths-ii/](https://leetcode-cn.com/problems/unique-paths-ii/) | - |
| 0067 | 旋转链表 | ll | [https://leetcode-cn.com/problems/rotate-list/](https://leetcode-cn.com/problems/rotate-list/) | - |
| 0073 | 矩阵置零 | saveSpace | [https://leetcode-cn.com/problems/set-matrix-zeroes/](https://leetcode-cn.com/problems/set-matrix-zeroes/) | - |
| 0074 | 搜索二维矩阵 | bs | [https://leetcode-cn.com/problems/search-a-2d-matrix/](https://leetcode-cn.com/problems/search-a-2d-matrix/) | - |
| 0084 | 柱状图中最大矩形 | monoStack | [https://leetcode-cn.com/problems/largest-rectangle-in-histogram/](https://leetcode-cn.com/problems/largest-rectangle-in-histogram/) | - |
| 0085 | 最大矩形 | monoStack | [https://leetcode-cn.com/problems/maximal-rectangle/submissions/](https://leetcode-cn.com/problems/maximal-rectangle/submissions/) | - |
| 0095 | 不同的二叉搜索树 II | recur,bst | [https://leetcode-cn.com/problems/unique-binary-search-trees-ii/](https://leetcode-cn.com/problems/unique-binary-search-trees-ii/) | recur,bst |
| 0098 | 验证BST | bst | [https://leetcode-cn.com/problems/validate-binary-search-tree/](https://leetcode-cn.com/problems/validate-binary-search-tree/) | recur,bst |
| 0108 | 有序数组转BST | bst | [https://leetcode-cn.com/problems/convert-sorted-array-to-binary-search-tree/](https://leetcode-cn.com/problems/convert-sorted-array-to-binary-search-tree/) | recur,bst |
| 0109 | 链表转BST | ll,bst | [https://leetcode-cn.com/problems/convert-sorted-list-to-binary-search-tree/](https://leetcode-cn.com/problems/convert-sorted-list-to-binary-search-tree/) | 递归，分治,recur,bst |
| 0123 | 买卖股票的最佳时机 | dp | [https://leetcode-cn.com/problems/best-time-to-buy-and-sell-stock-iii/](https://leetcode-cn.com/problems/best-time-to-buy-and-sell-stock-iii/) | - |
| 0124 | 二叉树中的最大路径和 | dp | [https://leetcode-cn.com/problems/binary-tree-maximum-path-sum/](https://leetcode-cn.com/problems/binary-tree-maximum-path-sum/) | - |
| 0141 | 单向链表有回环 | ll, saveSpace | [https://leetcode-cn.com/problems/linked-list-cycle/](https://leetcode-cn.com/problems/linked-list-cycle/) | floyd判圈 |
| 0142 | 单向链表有回环2 | ll, saveSpace | [https://leetcode-cn.com/problems/linked-list-cycle-ii/](https://leetcode-cn.com/problems/linked-list-cycle-ii) | floyd判圈 |
| 0209 | 长度最小和大于k的子数组 | mw,prefixSum | [https://leetcode-cn.com/problems/shortest-subarray-with-sum-at-least-k/](https://leetcode-cn.com/problems/shortest-subarray-with-sum-at-least-k/) | 滑动窗口，前缀和 |
| 0218 | 获取天际线 | heap | [https://leetcode-cn.com/problems/the-skyline-problem](https://leetcode-cn.com/problems/the-skyline-problem) | heap,找出当前窗口的最高值 |
| 0233 | 数字1的个数 | perm/comb | [https://leetcode-cn.com/problems/number-of-digit-one/](https://leetcode-cn.com/problems/number-of-digit-one/) | - |
| 0313 | 超级丑数 | heap | [https://leetcode-cn.com/problems/super-ugly-number/](https://leetcode-cn.com/problems/super-ugly-number/) | - |
| 0315 | 计算右侧小于当前元素的个数 | bit | [https://leetcode-cn.com/problems/count-of-smaller-numbers-after-self/](https://leetcode-cn.com/problems/count-of-smaller-numbers-after-self/) | bit |
| 0327 | 区间和的个数 | bit | [https://leetcode-cn.com/problems/count-of-range-sum/](https://leetcode-cn.com/problems/count-of-range-sum/) | bit |
| 0328 | 奇偶链表 | ll, saveSpace | [https://leetcode-cn.com/problems/odd-even-linked-list/](https://leetcode-cn.com/problems/odd-even-linked-list/) | - |
| 0375 | 猜数字大小2的最低金额 | dp,minimax | [https://leetcode-cn.com/problems/guess-number-higher-or-lower-ii/](https://leetcode-cn.com/problems/guess-number-higher-or-lower-ii/) | 区间dp，极小极大算法 |
| 0391 | 完美矩形 | - | [https://leetcode-cn.com/problems/perfect-rectangle/](https://leetcode-cn.com/problems/perfect-rectangle/) | trick |
| 0413 | 等差数列划分 | arr | [https://leetcode-cn.com/problems/arithmetic-slices/](https://leetcode-cn.com/problems/arithmetic-slices/) | - |
| 0416 | 分割等和子集 | dp,arr | [https://leetcode-cn.com/problems/partition-equal-subset-sum](https://leetcode-cn.com/problems/partition-equal-subset-sum) | - |
| 0445 | 两数相加 | ll | [https://leetcode-cn.com/problems/add-two-numbers-ii/submissions/](https://leetcode-cn.com/problems/add-two-numbers-ii/submissions/) |  |
| 0466 | 等差数列划分 | dp,arr | [https://leetcode-cn.com/problems/arithmetic-slices-ii-subsequence/](https://leetcode-cn.com/problems/arithmetic-slices-ii-subsequence/) | - |
| 0480 | 滑动窗口中位数 | mw,mset | [https://leetcode-cn.com/problems/sliding-window-median/](https://leetcode-cn.com/problems/sliding-window-median/) | 滑动窗口,multiset |
| 0516 | 最长回文子序列 | dp | [https://leetcode-cn.com/problems/longest-palindromic-subsequence/](https://leetcode-cn.com/problems/longest-palindromic-subsequence/) | - |
| 0526 | 优美排列 | bt,arr | [https://leetcode-cn.com/problems/beautiful-arrangement](https://leetcode-cn.com/problems/beautiful-arrangement) | - |
| 0547 | 找无向图连通子图个数 | dfs,scc | [https://leetcode-cn.com/problems/number-of-provinces/](https://leetcode-cn.com/problems/number-of-provinces/) | 强连图子图，dfs |
| 0560 | 子串和为k | arr,hash | [https://leetcode-cn.com/problems/subarray-sum-equals-k/](https://leetcode-cn.com/problems/subarray-sum-equals-k/) | prefixSum |
| 0611 | 有效三角个数 | dp,arr | [https://leetcode-cn.com/problems/valid-triangle-number/](https://leetcode-cn.com/problems/valid-triangle-number/) | - |
| 0684 | 冗余链接 | tree,us,graph | [https://leetcode-cn.com/problems/redundant-connection](https://leetcode-cn.com/problems/redundant-connection) | 并查集 |
| 0685 | 冗余链接2 | tree,us,graph | [https://leetcode-cn.com/problems/redundant-connection-ii](https://leetcode-cn.com/problems/redundant-connection-ii) | 并查集 |
 makeLargestSpecial 
| 0761 | 特殊的二进制序列 | recur | [https://leetcode-cn.com/problems/special-binary-string](https://leetcode-cn.com/problems/special-binary-string) | recur |
| 0765 | 情侣交换最少 | us | [https://leetcode-cn.com/problems/couples-holding-hands/](https://leetcode-cn.com/problems/couples-holding-hands/) | 并查集 |
| 0778 | 泳池上升水位游泳 | graph,us | [https://leetcode-cn.com/problems/swim-in-rising-water/](https://leetcode-cn.com/problems/swim-in-rising-water/) | 并查集，dfs，bfs |
| 0785 | 是否为二分图 | graph,bfs,us,dfs,biPart | [https://leetcode-cn.com/problems/is-graph-bipartite/](https://leetcode-cn.com/problems/is-graph-bipartite/) | 二分图，并查集，电dfs，bfs |
| 0862 | 和大于k的最短子数组长度 | monoQueue,prefixSum | [https://leetcode-cn.com/problems/shortest-subarray-with-sum-at-least-k/](https://leetcode-cn.com/problems/shortest-subarray-with-sum-at-least-k/) | 单调队列，前缀和 |
| 0874 | 模拟机器人行走 | sim | [https://leetcode-cn.com/problems/walking-robot-simulation/](https://leetcode-cn.com/problems/walking-robot-simulation/) | - |
| 0904 | 水果成蓝(同0992) | mv,map | [https://leetcode-cn.com/problems/fruit-into-baskets/](https://leetcode-cn.com/problems/fruit-into-baskets/) | 滑动窗口,map |
| 0924 | 最小化病毒软件传播 | graph,us | [https://leetcode-cn.com/problems/minimize-malware-spread/](https://leetcode-cn.com/problems/minimize-malware-spread/) | 并查集 |
| 0952 | 最大质因数联通分量大小 | graph,us | [https://leetcode-cn.com/problems/largest-component-size-by-common-factor](https://leetcode-cn.com/problems/largest-component-size-by-common-factor) | 并查集 |
| 0928 | 最小化病毒软件传播2 | graph,us | [https://leetcode-cn.com/problems/minimize-malware-spread-ii/](https://leetcode-cn.com/problems/minimize-malware-spread-ii/) | 并查集 |
| 0992 | 不同元素不大于k个的子数组个数 | mw | [https://leetcode-cn.com/problems/subarrays-with-k-different-integers/submissions/](https://leetcode-cn.com/problems/subarrays-with-k-different-integers/submissions/) | 滑动窗口 |
| 0995 |  K 连续位的最小翻转次数 | mw,da | [https://leetcode-cn.com/problems/minimum-number-of-k-consecutive-bit-flips/](https://leetcode-cn.com/problems/minimum-number-of-k-consecutive-bit-flips/) | 滑动窗口，差分数组 |
| 1106 | 解析bool表达式 | recur | [https://leetcode-cn.com/problems/parsing-a-boolean-expression/](https://leetcode-cn.com/problems/parsing-a-boolean-expression/) | 递归 |
| 1124 | 最长良好表现时间段 | hash,monoStack,prefixSum | [https://leetcode-cn.com/problems/longest-well-performing-interval/](https://leetcode-cn.com/problems/longest-well-performing-interval/) | 前缀和，单调栈 |
| 1171 | 移除0和子链表 | ll,prefixSum | [https://leetcode-cn.com/problems/remove-zero-sum-consecutive-nodes-from-linked-list/](https://leetcode-cn.com/problems/remove-zero-sum-consecutive-nodes-from-linked-list/) | 前缀和 |
| 1292 | 最大正方形边长 | bs,prefixSum | [https://leetcode-cn.com/problems/maximum-side-length-of-a-square-with-sum-less-than-or-equal-to-threshold/](https://leetcode-cn.com/problems/maximum-side-length-of-a-square-with-sum-less-than-or-equal-to-threshold/) | 前缀和 |
| 1373 | 二叉搜索子树的最大键值和 | bst | [https://leetcode-cn.com/problems/maximum-sum-bst-in-binary-tree/](https://leetcode-cn.com/problems/maximum-sum-bst-in-binary-tree/) | 二叉搜索树 |
| 1472 | 浏览器历史 | stack | [https://leetcode-cn.com/problems/design-browser-history/](https://leetcode-cn.com/problems/design-browser-history/) | - |
| 1546 | 非重叠子数组和的个数 | prefixSum,hash | [https://leetcode-cn.com/problems/maximum-number-of-non-overlapping-subarrays-with-sum-equals-target/submissions/](https://leetcode-cn.com/problems/maximum-number-of-non-overlapping-subarrays-with-sum-equals-target/submissions/) | 前缀和 |
| 1569 | 将子数组重新排序得到同一个二叉查找树的方案数 | bst，recur | [https://leetcode-cn.com/problems/number-of-ways-to-reorder-array-to-get-same-bst/](https://leetcode-cn.com/problems/number-of-ways-to-reorder-array-to-get-same-bst/) | 二叉搜索树，recur |
| 1583 | 不开心朋友个数 | arr,hash | [https://leetcode-cn.com/problems/count-unhappy-friends/](https://leetcode-cn.com/problems/count-unhappy-friends/) | - |
| 1590 | 最短子数组移除被k整除 | prefixSum,hash | [https://leetcode-cn.com/problems/make-sum-divisible-by-p/](https://leetcode-cn.com/problems/make-sum-divisible-by-p/) | 前缀和，hash |
| 1669 | 合并两个链表 | ll | [https://leetcode-cn.com/problems/merge-in-between-linked-lists/](https://leetcode-cn.com/problems/merge-in-between-linked-lists/) | - |
| 1696 | 最大跳跃所得 | mw,heap | [https://leetcode-cn.com/problems/jump-game-vi/submissions/](https://leetcode-cn.com/problems/jump-game-vi/submissions/) | 滑动窗口，最大堆 |
| 1703 | 最小移动数量获得连续k个1 | math,prefixSum,mw | [https://leetcode-cn.com/problems/minimum-adjacent-swaps-for-k-consecutive-ones](https://leetcode-cn.com/problems/minimum-adjacent-swaps-for-k-consecutive-ones) | 滑动窗口,前缀和 |
| 1760 | 球的出口 | sim | [https://leetcode-cn.com/problems/where-will-the-ball-fall/](https://leetcode-cn.com/problems/where-will-the-ball-fall/) | - |
| 1808 | 最大好因子个数 | math | [https://leetcode-cn.com/problems/maximize-number-of-nice-divisors/](https://leetcode-cn.com/problems/maximize-number-of-nice-divisors/) | math |
| 1819 | 所有子序列不同最大公约数数目 | reverseThink,trick | [https://leetcode-cn.com/problems/number-of-different-subsequences-gcds/](https://leetcode-cn.com/problems/number-of-different-subsequences-gcds/) | 逆向思维，trick |
| 1857 | 有向图中最大颜色值 | graph,topoSort,dp | [https://leetcode-cn.com/problems/largest-color-value-in-a-directed-graph/](https://leetcode-cn.com/problems/largest-color-value-in-a-directed-graph/) | 拓扑排序，动态规划 |
| 1877 | 最小最大数对和 | arr | [https://leetcode-cn.com/problems/minimize-maximum-pair-sum-in-array/](https://leetcode-cn.com/problems/minimize-maximum-pair-sum-in-array/) | - |
| 1889 | 最小空间浪费 | arr,binSear,prefixSum | [https://leetcode-cn.com/problems/minimum-space-wasted-from-packaging/submissions/](https://leetcode-cn.com/problems/minimum-space-wasted-from-packaging/submissions/) | 二分查找,前缀和 |
| 2014 | 重复 K 次的最长子序列 | dictOrder,perm | [https://leetcode-cn.com/problems/largest-color-value-in-a-directed-graph/](https://leetcode-cn.com/problems/largest-color-value-in-a-directed-graph/) | 排列，字典序 |
| 2025 | 分割数组最多方案数 | hash,preSum | [https://leetcode-cn.com/problems/maximum-number-of-ways-to-partition-an-array/](https://leetcode-cn.com/problems/maximum-number-of-ways-to-partition-an-array/) | 前缀和，hash |
|  |  |  |  |  |
