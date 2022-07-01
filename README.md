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
| 有序集合 | set |
| 差分数组 | diff array(da) |
| 强联通子图 | scc(strongly connected components)|
| 二叉搜索树 | bst |
| 二叉索引树(树状数组) | bit(binary indexed tree) |
| 线段树 | segTree(segment Tree) |
| 前缀树/字典树 | trie(prefix tree/dictTree) |

----------------------

| 算法 |  |
| - | - |
| 贪心 | greedy |
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
| 双指针 | twoPtr |
| 极大极小 | minimax |
| 拓扑排序 | topoSort |
| 逆向思维 | reverseThink |
| 取巧 | trick |
| 字符串-拉宾-卡普 | rabin-karp |
| 扫描线 | scanLine |
| 记忆化搜索 | memo |
| 排序 | sort |
| kmp字符串匹配 | kmp算法 |
| 状态压缩 | statusCompression |
| 二进制偏移 | binLift |
| 迪杰斯塔拉 | dijstra |
| tarjan算法 | tarjan算法 |


## 2 题解
| 题号 | 题名 | 类型 | 链接 | 使用算法 |
| - | - | - | - | - |
| 0000_interview_0409BSTSequence | 面试题 04.09. 二叉搜索树序列 | bst,recur | [https://leetcode-cn.com/problems/bst-sequences-lcci/](https://leetcode-cn.com/problems/bst-sequences-lcci/) | bst,recur |
| 0000_interview_1712trapWater | 0042 接雨水 | monoStack | [https://leetcode-cn.com/problems/volume-of-histogram-lcci/](https://leetcode-cn.com/problems/volume-of-histogram-lcci/) | 单调栈 |
| 0000_interview_maxGrade | 小易最好成绩 | dp | [https://www.nowcoder.com/questionTerminal/b83f4f4950d04154a6dc053b6d419782](https://www.nowcoder.com/questionTerminal/b83f4f4950d04154a6dc053b6d419782) | - |
| 0000_interview_maxTowerLen | 最高罗汉塔高度 | dp | [https://www.nowcoder.com/practice/c2afcd7353f84690bb73aa6123548770?tpId=182&tqId=34688&rp=1&ru=/exam/oj&qru=/exam/oj&sourceUrl=%2Fexam%2Foj%3Ftab%3D%25E5%2590%258D%25E4%25BC%2581%25E7%25AC%2594%25E8%25AF%2595%25E7%259C%259F%25E9%25A2%2598%26topicId%3D182%26page%3D1&difficulty=undefined&judgeStatus=undefined&tags=&title=](https://www.nowcoder.com/practice/c2afcd7353f84690bb73aa6123548770?tpId=182&tqId=34688&rp=1&ru=/exam/oj&qru=/exam/oj&sourceUrl=%2Fexam%2Foj%3Ftab%3D%25E5%2590%258D%25E4%25BC%2581%25E7%25AC%2594%25E8%25AF%2595%25E7%259C%259F%25E9%25A2%2598%26topicId%3D182%26page%3D1&difficulty=undefined&judgeStatus=undefined&tags=&title=) | - |
| 0000_interview_mergeKList | 合并k个升序链表 | ll | [https://www.nowcoder.com/practice/65cfde9e5b9b4cf2b6bafa5f3ef33fa6?tpId=295&tqId=724&ru=/exam/oj&qru=/ta/format-top101/question-ranking&sourceUrl=%2Fexam%2Foj](https://www.nowcoder.com/practice/65cfde9e5b9b4cf2b6bafa5f3ef33fa6?tpId=295&tqId=724&ru=/exam/oj&qru=/ta/format-top101/question-ranking&sourceUrl=%2Fexam%2Foj) | - |
| 0000_interview_subAddBinTree | 加减二叉树  | bst | [https://www.nowcoder.com/questionTerminal/39953c879b79412b85fbca2ffdeb0a4c?f=discussion](https://www.nowcoder.com/questionTerminal/39953c879b79412b85fbca2ffdeb0a4c?f=discussion) | 数学 |
| 0004 | 寻找两个正序数组的中位数 | binSear | [https://leetcode.cn/problems/median-of-two-sorted-arrays/](https://leetcode.cn/problems/median-of-two-sorted-arrays/) | - |
| 0010 | 正则表达式匹配  | recur | [https://leetcode-cn.com/problems/regular-expression-matching](https://leetcode-cn.com/problems/regular-expression-matching) | recur |
| 0015 | 三数之和 | twoPtr | [https://leetcode-cn.com/problems/3sum/](https://leetcode-cn.com/problems/3sum/) | - |
| 0025 | k个一组翻转链表 | recur,ll | [https://leetcode-cn.com/problems/reverse-nodes-in-k-group/](https://leetcode-cn.com/problems/reverse-nodes-in-k-group/) | recur,ll |
| 0030 | 串联所有单词的字串 | mw | [https://leetcode-cn.com/problems/substring-with-concatenation-of-all-words/](https://leetcode-cn.com/problems/substring-with-concatenation-of-all-words/) | - |
| 0032 | 最长有效括号 | dp,arr,stack | [https://leetcode-cn.com/problems/longest-valid-parentheses/](https://leetcode-cn.com/problems/longest-valid-parentheses/) | - |
| 0037 | 解数独 | dfs | [https://leetcode-cn.com/problems/sudoku-solver/](https://leetcode-cn.com/problems/sudoku-solver/) | - |
| 0043_1 | 数1的个数 | math | [https://leetcode-cn.com/problems/1nzheng-shu-zhong-1chu-xian-de-ci-shu-lcof/](https://leetcode-cn.com/problems/1nzheng-shu-zhong-1chu-xian-de-ci-shu-lcof/) | math |
| 0046 | 全排列 | perm |[https://leetcode-cn.com/problems/permutations/](https://leetcode-cn.com/problems/permutations/)  | perm |
| 0047 | 去重全排列 | perm | [https://leetcode-cn.com/problems/permutations-ii/](https://leetcode-cn.com/problems/permutations-ii/) | perm |
| 0051 | n皇后 | backTrack | [https://leetcode-cn.com/problems/n-queens/](https://leetcode-cn.com/problems/n-queens/) | - |
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
| 0115 | 目标子序列不同的个数 | dp | [https://leetcode-cn.com/problems/distinct-subsequences/](https://leetcode-cn.com/problems/distinct-subsequences/) | - |
| 0123 | 买卖股票的最佳时机 | dp | [https://leetcode-cn.com/problems/best-time-to-buy-and-sell-stock-iii/](https://leetcode-cn.com/problems/best-time-to-buy-and-sell-stock-iii/) | - |
| 0124 | 二叉树中的最大路径和 | dp | [https://leetcode-cn.com/problems/binary-tree-maximum-path-sum/](https://leetcode-cn.com/problems/binary-tree-maximum-path-sum/) | - |
| 0127 | 单词接龙 | bfs | [https://leetcode-cn.com/problems/word-ladder/](https://leetcode-cn.com/problems/word-ladder/) | - |
| 0135 | 分发糖果 | greedy | [https://leetcode-cn.com/problems/candy/](https://leetcode-cn.com/problems/candy/) | - |
| 0137 | 只出现一次的数字 II | hash | [https://leetcode-cn.com/problems/single-number-ii/](https://leetcode-cn.com/problems/single-number-ii/) | - |
| 0140 | 单词拆分 II | trie,backTrack | [https://leetcode-cn.com/problems/word-break-ii/](https://leetcode-cn.com/problems/word-break-ii/) | 字典树,回溯 |
| 0141 | 单向链表有回环 | ll, saveSpace | [https://leetcode-cn.com/problems/linked-list-cycle/](https://leetcode-cn.com/problems/linked-list-cycle/) | floyd判圈 |
| 0142 | 单向链表有回环2 | ll, saveSpace | [https://leetcode-cn.com/problems/linked-list-cycle-ii/](https://leetcode-cn.com/problems/linked-list-cycle-ii) | floyd判圈 |
| 0149 | 直线上最多的点 | math | [https://leetcode-cn.com/problems/max-points-on-a-line/](https://leetcode-cn.com/problems/max-points-on-a-line/) | - |
| 0164 | 最大间距 | sort | [https://leetcode-cn.com/problems/maximum-gap/](https://leetcode-cn.com/problems/maximum-gap/) | 桶排序 |
| 0174 | 地下城 | dp | [https://leetcode-cn.com/problems/dungeon-game/](https://leetcode-cn.com/problems/dungeon-game/) | - |
| 0208 | 实现 Trie (前缀树) | trie | [https://leetcode-cn.com/problems/implement-trie-prefix-tree/](https://leetcode-cn.com/problems/implement-trie-prefix-tree/) | trie |
| 0209 | 长度最小和大于k的子数组 | mw,prefixSum | [https://leetcode-cn.com/problems/shortest-subarray-with-sum-at-least-k/](https://leetcode-cn.com/problems/shortest-subarray-with-sum-at-least-k/) | 滑动窗口，前缀和 |
| 0212 | 单词搜索 II | trie,backTrack | [https://leetcode-cn.com/problems/word-search-ii](https://leetcode-cn.com/problems/word-search-ii) | 字典树 |
| 0214 | 最短回文串 | kmp | [https://leetcode-cn.com/problems/shortest-palindrome/](https://leetcode-cn.com/problems/shortest-palindrome/) | kmp算法 |
| 0218 | 获取天际线 | heap | [https://leetcode-cn.com/problems/the-skyline-problem](https://leetcode-cn.com/problems/the-skyline-problem) | heap,找出当前窗口的最高值 |
| 0233 | 数字1的个数 | perm/comb | [https://leetcode-cn.com/problems/number-of-digit-one/](https://leetcode-cn.com/problems/number-of-digit-one/) | - |
| 0295 | 数据流中位数 | min/max heap | [https://leetcode-cn.com/problems/find-median-from-data-stream/](https://leetcode-cn.com/problems/find-median-from-data-stream/) | 双堆对准中间位置 |
| 0297 | 二叉树序列化反序列化 | binTree | [https://leetcode-cn.com/problems/serialize-and-deserialize-binary-tree/](https://leetcode-cn.com/problems/serialize-and-deserialize-binary-tree/) | 二叉树序列化 |
| 0300 | 最长递增序列 | dp,lis | [https://leetcode-cn.com/problems/longest-increasing-subsequence/](https://leetcode-cn.com/problems/longest-increasing-subsequence/) | - |
| 0301 | 最少移除括号 | backTrack | [https://leetcode-cn.com/problems/remove-invalid-parentheses/submissions/](https://leetcode-cn.com/problems/remove-invalid-parentheses/submissions/) | - |
| 0304 | 二位区域和 | preSum | [https://leetcode-cn.com/problems/range-sum-query-2d-immutable/](https://leetcode-cn.com/problems/range-sum-query-2d-immutable/) | preSum |
| 0310 | 最小高度树 | bfs | [https://leetcode-cn.com/problems/minimum-height-trees/](https://leetcode-cn.com/problems/minimum-height-trees/) | - |
| 0313 | 超级丑数 | heap | [https://leetcode-cn.com/problems/super-ugly-number/](https://leetcode-cn.com/problems/super-ugly-number/) | - |
| 0315 | 计算右侧小于当前元素的个数 | bit | [https://leetcode-cn.com/problems/count-of-smaller-numbers-after-self/](https://leetcode-cn.com/problems/count-of-smaller-numbers-after-self/) | bit |
| 0312 | 戳气球获得最大硬币 | reverseThink,dp | [https://leetcode-cn.com/problems/dungeon-game/](https://leetcode-cn.com/problems/dungeon-game/) | - |
| 0321 | 拼接最大数 | monoStack | [https://leetcode-cn.com/problems/longest-duplicate-substring/](https://leetcode-cn.com/problems/longest-duplicate-substring/) | 单调栈 |
| 0327 | 区间和的个数 | bit | [https://leetcode-cn.com/problems/count-of-range-sum/](https://leetcode-cn.com/problems/count-of-range-sum/) | bit |
| 0328 | 奇偶链表 | ll, saveSpace | [https://leetcode-cn.com/problems/odd-even-linked-list/](https://leetcode-cn.com/problems/odd-even-linked-list/) | - |
| 0329 | 矩阵中的最长递增路径 | dfs/memo | [https://leetcode-cn.com/problems/longest-increasing-path-in-a-matrix/](https://leetcode-cn.com/problems/longest-increasing-path-in-a-matrix/) | dfs记忆化搜索 |
| 0332 | 重新安排行程 | dfs | [https://leetcode-cn.com/problems/reconstruct-itinerary/](https://leetcode-cn.com/problems/reconstruct-itinerary/) | hierholzer算法, 欧拉路 |
| 0335 | 相交路径 | math | [https://leetcode-cn.com/problems/self-crossing/](https://leetcode-cn.com/problems/self-crossing/) | - |
| 0336 | 回文对 | trie | [https://leetcode-cn.com/problems/palindrome-pairs/](https://leetcode-cn.com/problems/palindrome-pairs/) | 字典树 |
| 0354 | 套娃信件(2d 最长递增序列) | dp | [https://leetcode-cn.com/problems/russian-doll-envelopes/](https://leetcode-cn.com/problems/russian-doll-envelopes/) | - |
| 0363 | 最大子区域和 | set | [https://leetcode-cn.com/problems/max-sum-of-rectangle-no-larger-than-k/](https://leetcode-cn.com/problems/max-sum-of-rectangle-no-larger-than-k/) | 有序集合 |
| 0375 | 猜数字大小2的最低金额 | dp,minimax | [https://leetcode-cn.com/problems/guess-number-higher-or-lower-ii/](https://leetcode-cn.com/problems/guess-number-higher-or-lower-ii/) | 区间dp，极小极大算法 |
| 0381 | o1删除添加随机获取 | math | [https://leetcode-cn.com/problems/insert-delete-getrandom-o1-duplicates-allowed/](https://leetcode-cn.com/problems/insert-delete-getrandom-o1-duplicates-allowed/) | - |
| 0386 | 字典序排数 | dictTree | [https://leetcode-cn.com/problems/lexicographical-numbers/](https://leetcode-cn.com/problems/lexicographical-numbers/) | - |
| 0391 | 完美矩形 | - | [https://leetcode-cn.com/problems/perfect-rectangle/](https://leetcode-cn.com/problems/perfect-rectangle/) | trick |
| 0403 | 青蛙过河 | dp | [https://leetcode-cn.com/problems/frog-jump/](https://leetcode-cn.com/problems/frog-jump/) | - |
| 0407 | 接雨水2 | heap,dfs/bfs | [https://leetcode.cn/problems/trapping-rain-water-ii/](https://leetcode.cn/problems/trapping-rain-water-ii/) | dijstra |
| 0410 | 分割出最小的子数组最大值 | dp,bs | [https://leetcode-cn.com/problems/split-array-largest-sum/](https://leetcode-cn.com/problems/split-array-largest-sum/) |  |
| 0413 | 等差数列划分 | arr | [https://leetcode-cn.com/problems/arithmetic-slices/](https://leetcode-cn.com/problems/arithmetic-slices/) | - |
| 0416 | 分割等和子集 | dp,arr | [https://leetcode-cn.com/problems/partition-equal-subset-sum](https://leetcode-cn.com/problems/partition-equal-subset-sum) | - |
| 0420 | 强密码校验器 | math | [https://leetcode-cn.com/problems/strong-password-checker/submissions/](https://leetcode-cn.com/problems/strong-password-checker/submissions/) | - |
| 0429 | n叉树层序遍历 | bfs | [https://leetcode-cn.com/problems/n-ary-tree-level-order-traversal/submissions/](https://leetcode-cn.com/problems/n-ary-tree-level-order-traversal/submissions/) | - |
| 0436 | 寻找右区间 | map/binSear | [https://leetcode.cn/problems/find-right-interval/](https://leetcode.cn/problems/minimum-moves-to-equal-array-elements-ii/) | - |
| 0440 | 字典序的第K小数字 | trie | [https://leetcode-cn.com/problems/k-th-smallest-in-lexicographical-order/](https://leetcode-cn.com/problems/k-th-smallest-in-lexicographical-order/) | trie |
| 0445 | 两数相加 | ll | [https://leetcode-cn.com/problems/add-two-numbers-ii/submissions/](https://leetcode-cn.com/problems/add-two-numbers-ii/submissions/) |  |
| 0446 | 等差数列划分 | dp,arr | [https://leetcode-cn.com/problems/arithmetic-slices-ii-subsequence/](https://leetcode-cn.com/problems/arithmetic-slices-ii-subsequence/) | - |
| 0459 | 重复的子字符串 | kmp | [https://leetcode-cn.com/problems/repeated-substring-pattern/](https://leetcode-cn.com/problems/repeated-substring-pattern/) | - |
| 0462| 0462minMove2 | sort | [https://leetcode.cn/problems/minimum-moves-to-equal-array-elements-ii/](https://leetcode.cn/problems/minimum-moves-to-equal-array-elements-ii/) | 快排找第K大 |
| 0466 | 统计重复个数 | trick | [https://leetcode-cn.com/problems/count-the-repetitions/](https://leetcode-cn.com/problems/count-the-repetitions/) | - |
| 0479 | 最大回文数乘积 | reverseThink | [https://leetcode-cn.com/problems/largest-palindrome-product/](https://leetcode-cn.com/problems/largest-palindrome-product/) | - |
| 0488 | 祖玛游戏 | dfs/memo | [https://leetcode-cn.com/problems/zuma-game/](https://leetcode-cn.com/problems/zuma-game/) | 记忆化搜索 |
| 0472 | 连接词 | trie | [https://leetcode-cn.com/problems/concatenated-words/](https://leetcode-cn.com/problems/concatenated-words/) | 字典树 |
| 0480 | 滑动窗口中位数 | mw,mset | [https://leetcode-cn.com/problems/sliding-window-median/](https://leetcode-cn.com/problems/sliding-window-median/) | 滑动窗口,multiset |
| 0493 | 翻转对 | bit/segTree | [https://leetcode-cn.com/problems/reverse-pairs/](https://leetcode-cn.com/problems/reverse-pairs/) | bit/segTree |
| 0502 | ipo上市 | heap | [https://leetcode.cn/problems/ipo/](https://leetcode.cn/problems/ipo/) | - |
| 0514 | 自由之路 | dfs,memo | [https://leetcode-cn.com/problems/freedom-trail/](https://leetcode-cn.com/problems/freedom-trail/) | 记忆化搜索 |
| 0516 | 最长回文子序列 | dp | [https://leetcode-cn.com/problems/longest-palindromic-subsequence/](https://leetcode-cn.com/problems/longest-palindromic-subsequence/) | - |
| 0526 | 优美排列 | bt,arr | [https://leetcode-cn.com/problems/beautiful-arrangement](https://leetcode-cn.com/problems/beautiful-arrangement) | - |
| 0546 | 移除盒子 | dp | [https://leetcode-cn.com/problems/remove-boxes/](https://leetcode-cn.com/problems/remove-boxes/) | - |
| 0547 | 找无向图连通子图个数 | dfs,scc | [https://leetcode-cn.com/problems/number-of-provinces/](https://leetcode-cn.com/problems/number-of-provinces/) | 强连图子图，dfs |
| 0552 | 学生出勤记录 | dp | [https://leetcode-cn.com/problems/student-attendance-record-ii/](https://leetcode-cn.com/problems/student-attendance-record-ii/) | - |
| 0560 | 子串和为k | arr,hash | [https://leetcode-cn.com/problems/subarray-sum-equals-k/](https://leetcode-cn.com/problems/subarray-sum-equals-k/) | prefixSum |
| 0564 | 最近最小回文数 | math | [https://leetcode-cn.com/problems/find-the-closest-palindrome/](https://leetcode-cn.com/problems/find-the-closest-palindrome/) | - |
| 0600 | 不含连续1的非负整数 | dp | [https://leetcode-cn.com/problems/non-negative-integers-without-consecutive-ones/](https://leetcode-cn.com/problems/non-negative-integers-without-consecutive-ones/) | - |
| 0611 | 有效三角个数 | dp,arr | [https://leetcode-cn.com/problems/valid-triangle-number/](https://leetcode-cn.com/problems/valid-triangle-number/) | - |
| 0629 | k个逆序数对的方案数 | dp | [https://leetcode-cn.com/problems/k-inverse-pairs-array/](https://leetcode-cn.com/problems/k-inverse-pairs-array/) | 区间dp |
| 0632 | 最小区间 | heap,greedy | [https://leetcode-cn.com/problems/smallest-range-covering-elements-from-k-lists/](https://leetcode-cn.com/problems/smallest-range-covering-elements-from-k-lists/) | - |
| 0639 | 解码方法数 | dp | [https://leetcode-cn.com/problems/decode-ways-ii/](https://leetcode-cn.com/problems/decode-ways-ii/) | - |
| 0664 | 奇怪打印机 | dp | [https://leetcode-cn.com/problems/strange-printer](https://leetcode-cn.com/problems/strange-printer) | 区间dp |
| 0668 | 乘法表中第k小的数 | math/binSear | [https://leetcode.cn/problems/kth-smallest-number-in-multiplication-table/](https://leetcode.cn/problems/kth-smallest-number-in-multiplication-table/) | - |
| 0675 | 高尔夫砍树 | heap,bfs | [https://leetcode.cn/problems/cut-off-trees-for-golf-event/](https://leetcode.cn/problems/cut-off-trees-for-golf-event/) | - |
| 0684 | 冗余链接 | tree,us,graph | [https://leetcode-cn.com/problems/redundant-connection](https://leetcode-cn.com/problems/redundant-connection) | 并查集 |
| 0685 | 冗余链接2 | tree,us,graph | [https://leetcode-cn.com/problems/redundant-connection-ii](https://leetcode-cn.com/problems/redundant-connection-ii) | 并查集 |
| 0689 | 三个无重叠子数组的最大和 | dp | [https://leetcode-cn.com/problems/maximum-sum-of-3-non-overlapping-subarrays/](https://leetcode-cn.com/problems/maximum-sum-of-3-non-overlapping-subarrays/) | - |
| 0698 | 可以划分为k个等和子集 | backTrack/memo | [https://leetcode.cn/problems/partition-to-k-equal-sum-subsets/](https://leetcode.cn/problems/partition-to-k-equal-sum-subsets/) | - |
| 0699 | 掉落的方块 | set | [https://leetcode-cn.com/problems/falling-squares/](https://leetcode-cn.com/problems/falling-squares/) | 有序集合(坐标压缩) |
| 0710 | 黑名单中的随机数 | math | [https://leetcode-cn.com/problems/random-pick-with-blacklist/](https://leetcode-cn.com/problems/random-pick-with-blacklist/) | - |
| 0715 |  Range 模块 | map | [https://leetcode-cn.com/problems/range-module/](https://leetcode-cn.com/problems/range-module/) | map |
| 0719 | 第k小的数对距离 | bs | [https://leetcode.cn/problems/find-k-th-smallest-pair-distance/](https://leetcode.cn/problems/find-k-th-smallest-pair-distance/) | - |
| 0726 | 原子的数量 | tree | [https://leetcode-cn.com/problems/number-of-atoms/](https://leetcode-cn.com/problems/number-of-atoms/) |  |
| 0733 | 滑动到123450谜题 | bfs | [https://leetcode.cn/problems/sliding-puzzle/](https://leetcode.cn/problems/sliding-puzzle/) | - |
| 0745 | 前缀和后缀搜索 | trie | [https://leetcode-cn.com/problems/prefix-and-suffix-search/](https://leetcode-cn.com/problems/prefix-and-suffix-search/) | 字典树 |
| 0753 | 破解保险箱(变形欧拉路) | dfs | [https://leetcode-cn.com/problems/freedom-trail/](https://leetcode-cn.com/problems/freedom-trail/) | hierholzer算法/欧拉路 |
| 0757 | 设置交集为2 | greedy | [https://leetcode.cn/problems/set-intersection-size-at-least-two/](https://leetcode.cn/problems/set-intersection-size-at-least-two/) |  |
|0761 | 特殊的二进制序列 | recur | [https://leetcode-cn.com/problems/special-binary-string](https://leetcode-cn.com/problems/special-binary-string) | recur |
| 0765 | 情侣交换最少 | us | [https://leetcode-cn.com/problems/couples-holding-hands/](https://leetcode-cn.com/problems/couples-holding-hands/) | 并查集 |
| 0768 | 最多能完成排序的块 | monoStack | [https://leetcode-cn.com/problems/max-chunks-to-make-sorted-ii](https://leetcode-cn.com/problems/max-chunks-to-make-sorted-ii) | monoStack |
| 0778 | 泳池上升水位游泳 | graph,us | [https://leetcode-cn.com/problems/swim-in-rising-water/](https://leetcode-cn.com/problems/swim-in-rising-water/) | 并查集，dfs，bfs |
| 0780 | 到达终点 | math,reverseThink | [https://leetcode-cn.com/problems/reaching-points/](https://leetcode-cn.com/problems/reaching-points/) | - |
| 0785 | 是否为二分图 | graph,bfs,us,dfs,biPart | [https://leetcode-cn.com/problems/is-graph-bipartite/](https://leetcode-cn.com/problems/is-graph-bipartite/) | 二分图，并查集，电dfs，bfs |
| 0815 | 最少换乘数 | bfs | [https://leetcode-cn.com/problems/bus-routes/](https://leetcode-cn.com/problems/bus-routes/) | - |
| 0827 | 最大岛屿 | uf | [https://leetcode.cn/problems/making-a-large-island/](https://leetcode.cn/problems/making-a-large-island/) | - |
| 0834 | 树中距离之和 | dp/dfs | [https://leetcode.cn/problems/sum-of-distances-in-tree/](https://leetcode.cn/problems/sum-of-distances-in-tree/) | - |
| 0839 | 相似字符串组数 | uf | [https://leetcode.cn/problems/similar-string-groups/](https://leetcode.cn/problems/similar-string-groups/) | - |
| 0847 | 访问所有节点最短路径 | 状态bfs/statusCompression | [https://leetcode.cn/problems/shortest-path-visiting-all-nodes/](https://leetcode.cn/problems/shortest-path-visiting-all-nodes/) | 带状态压缩的bfs |
| 0850 | 矩形面积2 | scanLine | [https://leetcode-cn.com/problems/rectangle-area-ii/solution](https://leetcode-cn.com/problems/rectangle-area-ii/solution) | 扫描线 |
| 0854 | 相似度为k的字符串 | bfs | [https://leetcode.cn/problems/k-similar-strings/](https://leetcode.cn/problems/k-similar-strings/) | - |
| 0862 | 和大于k的最短子数组长度 | monoQueue,prefixSum | [https://leetcode-cn.com/problems/shortest-subarray-with-sum-at-least-k/](https://leetcode-cn.com/problems/shortest-subarray-with-sum-at-least-k/) | 单调队列，前缀和 |
| 0864 | 获取所有钥匙的最短路径 | 状态bfs/statusCompression | [https://leetcode.cn/problems/shortest-path-to-get-all-keys/submissions/](https://leetcode.cn/problems/shortest-path-to-get-all-keys/submissions/) | 带状态压缩的bfs |
| 0874 | 模拟机器人行走 | sim | [https://leetcode-cn.com/problems/walking-robot-simulation/](https://leetcode-cn.com/problems/walking-robot-simulation/) | - |
| 0878 | 第 N 个神奇数字 | binSear/math | [https://leetcode.cn/problems/nth-magical-number/](https://leetcode.cn/problems/nth-magical-number/) | - |
| 0882 | 细分图中的可到达结点 | graph/dijstra | [https://leetcode.cn/problems/reachable-nodes-in-subdivided-graph/](https://leetcode.cn/problems/reachable-nodes-in-subdivided-graph/) | dijstra |
| 0891 | 子序列宽度和 | math | [https://leetcode.cn/problems/sum-of-subsequence-widths/](https://leetcode.cn/problems/sum-of-subsequence-widths/) | - |
| 0895 | 最大频率栈 | map/hash_stack | [https://leetcode-cn.com/problems/maximum-frequency-stack/](https://leetcode-cn.com/problems/maximum-frequency-stack/) | 哈希存栈 |
| 0899 | 有序队列 | math | [https://leetcode.cn/problems/orderly-queue/](https://leetcode.cn/problems/orderly-queue/) | - |
| 0902 | 最大为 N 的数字组合 | dp | [https://leetcode.cn/problems/numbers-at-most-n-given-digit-set/](https://leetcode.cn/problems/numbers-at-most-n-given-digit-set/) | 数位dp |
| 0904 | 水果成蓝(同0992) | mv,map | [https://leetcode-cn.com/problems/fruit-into-baskets/](https://leetcode-cn.com/problems/fruit-into-baskets/) | 滑动窗口,map |
| 0912 | 三种基础排序 |  | [https://leetcode-cn.com/problems/sort-an-array/](https://leetcode-cn.com/problems/sort-an-array/) |  |
| 0924 | 最小化病毒软件传播 | graph,us | [https://leetcode-cn.com/problems/minimize-malware-spread/](https://leetcode-cn.com/problems/minimize-malware-spread/) | 并查集 |
| 0952 | 最大质因数联通分量大小 | graph,us | [https://leetcode-cn.com/problems/largest-component-size-by-common-factor](https://leetcode-cn.com/problems/largest-component-size-by-common-factor) | 并查集 |
| 0928 | 最小化病毒软件传播2 | graph,us | [https://leetcode-cn.com/problems/minimize-malware-spread-ii/](https://leetcode-cn.com/problems/minimize-malware-spread-ii/) | 并查集 |
| 0968 | 监控二叉树 | graph/dfs/memo | [https://leetcode-cn.com/problems/binary-tree-cameras/submissions/](https://leetcode-cn.com/problems/binary-tree-cameras/submissions/) | 记忆化搜索 |
| 0980 | 不同路径3 | backTrack | [https://leetcode.cn/problems/unique-paths-iii/](https://leetcode.cn/problems/unique-paths-iii/) | - |
| 0982 | 按位与为1的三元组个数 | hash | [https://leetcode-cn.com/problems/triples-with-bitwise-and-equal-to-zero/submissions/](https://leetcode-cn.com/problems/triples-with-bitwise-and-equal-to-zero/submissions/) | - |
| 0987 | 垂序遍历 | dfs, hash | [https://leetcode-cn.com/problems/vertical-order-traversal-of-a-binary-tree/](https://leetcode-cn.com/problems/vertical-order-traversal-of-a-binary-tree/) | - |
| 0992 | 不同元素不大于k个的子数组个数 | mw | [https://leetcode-cn.com/problems/subarrays-with-k-different-integers/submissions/](https://leetcode-cn.com/problems/subarrays-with-k-different-integers/submissions/) | 滑动窗口 |
| 0995 |  K 连续位的最小翻转次数 | mw,da | [https://leetcode-cn.com/problems/minimum-number-of-k-consecutive-bit-flips/](https://leetcode-cn.com/problems/minimum-number-of-k-consecutive-bit-flips/) | 滑动窗口，差分数组 |
| 0996 | 正方形数组的排列个数 | perm,backTrack,memo | [https://leetcode.cn/problems/number-of-squareful-arrays/](https://leetcode.cn/problems/number-of-squareful-arrays/)
 | - |
| 1028 | 前序和深度恢复二叉树 | sim | [https://leetcode.cn/problems/recover-a-tree-from-preorder-traversal/](https://leetcode.cn/problems/recover-a-tree-from-preorder-traversal/) | - |
| 1032 | 字符流检测 | trie | [https://leetcode-cn.com/problems/stream-of-characters/](https://leetcode-cn.com/problems/stream-of-characters/) | 字典树 |
| 1036 | 逃离巨大迷宫 | dfs | [https://leetcode.cn/problems/escape-a-large-maze/submissions/](https://leetcode.cn/problems/escape-a-large-maze/submissions/) | - |
| 1044 | 最长重复字串 | rabin-karp | [https://leetcode-cn.com/problems/longest-duplicate-substring/](https://leetcode-cn.com/problems/longest-duplicate-substring/) | 拉宾-卡普算法(o(n)字符串匹配) |
| 1095 | 山脉数组中查找目标值 | binSear | [https://leetcode.cn/problems/find-in-mountain-array/](https://leetcode.cn/problems/find-in-mountain-array/) | - |
| 1106 | 解析bool表达式 | recur | [https://leetcode-cn.com/problems/parsing-a-boolean-expression/](https://leetcode-cn.com/problems/parsing-a-boolean-expression/) | 递归 |
| 1124 | 最长良好表现时间段 | hash,monoStack,prefixSum | [https://leetcode-cn.com/problems/longest-well-performing-interval/](https://leetcode-cn.com/problems/longest-well-performing-interval/) | 前缀和，单调栈 |
| 1157 | 子数组中占绝大多数的元素 | binSear | [https://leetcode.cn/problems/online-majority-element-in-subarray/](https://leetcode.cn/problems/online-majority-element-in-subarray/) | - |
| 1163 | 最大字典序字串 | suffixArr | [https://leetcode.cn/problems/last-substring-in-lexicographical-order/](https://leetcode.cn/problems/last-substring-in-lexicographical-order/) | - |
| 1171 | 移除0和子链表 | ll,prefixSum | [https://leetcode-cn.com/problems/remove-zero-sum-consecutive-nodes-from-linked-list/](https://leetcode-cn.com/problems/remove-zero-sum-consecutive-nodes-from-linked-list/) | 前缀和 |
| 1192 | 查找集群内的「关键连接」 | graph/dfs | [https://leetcode.cn/problems/critical-connections-in-a-network/](https://leetcode.cn/problems/critical-connections-in-a-network/) | tarjan算法 |
| 1240 | 贴瓷砖 | backTrack | [https://leetcode.cn/problems/tiling-a-rectangle-with-the-fewest-squares/](https://leetcode.cn/problems/tiling-a-rectangle-with-the-fewest-squares/) | - |
| 1255 | 最大单词分数从字母集合中 | backTrack/statusCompression | [https://leetcode.cn/problems/maximum-score-words-formed-by-letters/](https://leetcode.cn/problems/maximum-score-words-formed-by-letters/) | - |
| 1292 | 最大正方形边长 | bs,prefixSum | [https://leetcode-cn.com/problems/maximum-side-length-of-a-square-with-sum-less-than-or-equal-to-threshold/](https://leetcode-cn.com/problems/maximum-side-length-of-a-square-with-sum-less-than-or-equal-to-threshold/) | 前缀和 |
| 1316 | 不同的循环子字符串 | rabin-karp | [https://leetcode-cn.com/problems/distinct-echo-substrings/](https://leetcode-cn.com/problems/distinct-echo-substrings/) | 拉宾-卡普算法(o(n)字符串匹配) |
| 1368 | 使网格图至少有一条有效路径的最小代价 | bfs/dijstra | [https://leetcode.cn/problems/minimum-cost-to-make-at-least-one-valid-path-in-a-grid/](https://leetcode.cn/problems/minimum-cost-to-make-at-least-one-valid-path-in-a-grid/) | 01bfs，迪杰斯特拉 |
| 1373 | 二叉搜索子树的最大键值和 | bst | [https://leetcode-cn.com/problems/maximum-sum-bst-in-binary-tree/](https://leetcode-cn.com/problems/maximum-sum-bst-in-binary-tree/) | 二叉搜索树 |
| 1377 | T秒后青蛙的位置 | bfs | [https://leetcode.cn/problems/frog-position-after-t-seconds/](https://leetcode.cn/problems/frog-position-after-t-seconds/) | - |
| 1402 | 做菜顺序 | sort,dp | [https://leetcode.cn/problems/reducing-dishes/](https://leetcode.cn/problems/reducing-dishes/) | - |
| 1472 | 浏览器历史 | stack | [https://leetcode-cn.com/problems/design-browser-history/](https://leetcode-cn.com/problems/design-browser-history/) | - |
| 1483 | 树节点的第 K 个祖先 | binLift,dp | [https://leetcode.cn/problems/kth-ancestor-of-a-tree-node/](https://leetcode.cn/problems/kth-ancestor-of-a-tree-node/) | 二进制偏移 |
| 1526 | 形成目标数组的子数组最少增加次数 | segTree | [https://leetcode-cn.com/problems/minimum-number-of-increments-on-subarrays-to-form-a-target-array/](https://leetcode-cn.com/problems/minimum-number-of-increments-on-subarrays-to-form-a-target-array/) | 数学 |
| 1537 | 最大得分 | twoPtr | [https://leetcode.cn/problems/get-the-maximum-score/submissions/](https://leetcode.cn/problems/get-the-maximum-score/submissions/) | - |
| 1546 | 非重叠子数组和的个数 | prefixSum,hash | [https://leetcode-cn.com/problems/maximum-number-of-non-overlapping-subarrays-with-sum-equals-target/submissions/](https://leetcode-cn.com/problems/maximum-number-of-non-overlapping-subarrays-with-sum-equals-target/submissions/) | 前缀和 |
| 1569 | 将子数组重新排序得到同一个二叉查找树的方案数 | bst，recur | [https://leetcode-cn.com/problems/number-of-ways-to-reorder-array-to-get-same-bst/](https://leetcode-cn.com/problems/number-of-ways-to-reorder-array-to-get-same-bst/) | 二叉搜索树，recur |
| 1579 | 保证图可完全遍历的最大删除边数 | uf,reverseThink | [https://leetcode.cn/problems/remove-max-number-of-edges-to-keep-graph-fully-traversable/](https://leetcode.cn/problems/remove-max-number-of-edges-to-keep-graph-fully-traversable/) | 逆向思维 |
| 1583 | 不开心朋友个数 | arr,hash | [https://leetcode-cn.com/problems/count-unhappy-friends/](https://leetcode-cn.com/problems/count-unhappy-friends/) | - |
| 1590 | 最短子数组移除被k整除 | prefixSum,hash | [https://leetcode-cn.com/problems/make-sum-divisible-by-p/](https://leetcode-cn.com/problems/make-sum-divisible-by-p/) | 前缀和，hash |
| 1606 | 找到处理最多请求的服务器 | map/set,sim | [https://leetcode-cn.com/problems/find-servers-that-handled-most-number-of-requests/](https://leetcode-cn.com/problems/find-servers-that-handled-most-number-of-requests/) | 有序集合，模拟 |
| 1617 | 统计子树中城市之间最大距离 | bfs | [https://leetcode.cn/problems/count-subtrees-with-max-distance-between-cities/](https://leetcode.cn/problems/count-subtrees-with-max-distance-between-cities/) | - |
| 1669 | 合并两个链表 | ll | [https://leetcode-cn.com/problems/merge-in-between-linked-lists/](https://leetcode-cn.com/problems/merge-in-between-linked-lists/) | - |
| 1696 | 最大跳跃所得 | mw,heap | [https://leetcode-cn.com/problems/jump-game-vi/submissions/](https://leetcode-cn.com/problems/jump-game-vi/submissions/) | 滑动窗口，最大堆 |
| 1703 | 最小移动数量获得连续k个1 | math,prefixSum,mw | [https://leetcode-cn.com/problems/minimum-adjacent-swaps-for-k-consecutive-ones](https://leetcode-cn.com/problems/minimum-adjacent-swaps-for-k-consecutive-ones) | 滑动窗口,前缀和 |
| 1719 | 重构一棵树的方案数 | trick/tree | [https://leetcode.cn/problems/number-of-ways-to-reconstruct-a-tree/](https://leetcode.cn/problems/number-of-ways-to-reconstruct-a-tree/) | - |
| 1755 | 最接近目标值的子序列和
 | twoPtr,statusCompression | [https://leetcode.cn/problems/closest-subsequence-sum/](https://leetcode.cn/problems/closest-subsequence-sum/) | 杨氏矩阵 |
| 1760 | 球的出口 | sim | [https://leetcode-cn.com/problems/where-will-the-ball-fall/](https://leetcode-cn.com/problems/where-will-the-ball-fall/) | - |
| 1793 | 好子数组的最大分数 | monoStack | [https://leetcode-cn.com/problems/maximum-score-of-a-good-subarray/](https://leetcode-cn.com/problems/maximum-score-of-a-good-subarray/) | 单调栈 |
| 1808 | 最大好因子个数 | math | [https://leetcode-cn.com/problems/maximize-number-of-nice-divisors/](https://leetcode-cn.com/problems/maximize-number-of-nice-divisors/) | math |
| 1819 | 所有子序列不同最大公约数数目 | reverseThink,trick | [https://leetcode-cn.com/problems/number-of-different-subsequences-gcds/](https://leetcode-cn.com/problems/number-of-different-subsequences-gcds/) | 逆向思维，trick |
| 1857 | 有向图中最大颜色值 | graph,topoSort,dp | [https://leetcode-cn.com/problems/largest-color-value-in-a-directed-graph/](https://leetcode-cn.com/problems/largest-color-value-in-a-directed-graph/) | 拓扑排序，动态规划 |
| 1877 | 最小最大数对和 | arr | [https://leetcode-cn.com/problems/minimize-maximum-pair-sum-in-array/](https://leetcode-cn.com/problems/minimize-maximum-pair-sum-in-array/) | - |
| 1889 | 最小空间浪费 | arr,binSear,prefixSum | [https://leetcode-cn.com/problems/minimum-space-wasted-from-packaging/submissions/](https://leetcode-cn.com/problems/minimum-space-wasted-from-packaging/submissions/) | 二分查找,前缀和 |
| 1928 | 规定时间内到达终点的最小花费 | graph/dp | [https://leetcode.cn/problems/minimum-cost-to-reach-destination-in-time/](https://leetcode.cn/problems/minimum-cost-to-reach-destination-in-time/) | - |
| 1944 | 队列中可以看到的人数 | monoStack | [https://leetcode-cn.com/problems/number-of-visible-people-in-a-queue/](https://leetcode-cn.com/problems/number-of-visible-people-in-a-queue/) | 单调栈 |
| 2014 | 重复 K 次的最长子序列 | dictOrder,perm | [https://leetcode-cn.com/problems/largest-color-value-in-a-directed-graph/](https://leetcode-cn.com/problems/largest-color-value-in-a-directed-graph/) | 排列，字典序 |
| 2025 | 分割数组最多方案数 | hash,preSum | [https://leetcode-cn.com/problems/maximum-number-of-ways-to-partition-an-array/](https://leetcode-cn.com/problems/maximum-number-of-ways-to-partition-an-array/) | 前缀和，hash |
| 2030 | 含特定字母的最小子序列 | monoStack | [https://leetcode-cn.com/problems/smallest-k-length-subsequence-with-occurrences-of-a-letter/](https://leetcode-cn.com/problems/smallest-k-length-subsequence-with-occurrences-of-a-letter/) | 单调栈 |
| 2035 | 将数组分成两个数组并最小化数组和的差 | statusCompression,twoPtr | [https://leetcode.cn/problems/partition-array-into-two-arrays-to-minimize-sum-difference/](https://leetcode.cn/problems/partition-array-into-two-arrays-to-minimize-sum-difference/) | 杨氏矩阵 |
| 2065 | 规定时间内路径的最大价值 | graph/backTrack | [https://leetcode.cn/problems/maximum-path-quality-of-a-graph/](https://leetcode.cn/problems/maximum-path-quality-of-a-graph/) |  |
| lcp10 | 二叉树任务调度 | bt | [https://leetcode.cn/problems/er-cha-shu-ren-wu-diao-du/](https://leetcode.cn/problems/er-cha-shu-ren-wu-diao-du/)
 | - |
|  |  |  |  |  |
