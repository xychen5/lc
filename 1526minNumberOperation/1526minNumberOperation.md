## 1526. 形成目标数组的子数组最少增加次数 minNumberOperation

### 1 题目
[https://leetcode-cn.com/problems/minimum-number-of-increments-on-subarrays-to-form-a-target-array/](https://leetcode-cn.com/problems/minimum-number-of-increments-on-subarrays-to-form-a-target-array/)

### 2 解题思路
- 1 普通思路：(注意：**将这些数字从0堆起来到数组a等于将数组a慢慢减到0**)
  - 1.1 采用模拟的思路，对于例子： arr = [0 5 4 7 4 6 0]，记录总的操作步数为res
  - 1.2 首先找到最小的，为0，然后找到第二小，为4，于是第一个个操作为：对arr[0 : 6]区间的数全部减4，res = 4
  - 1.3 然后arr = [0,1,0,3,0,2,0]，然后我们发现，数字被0分割成了3小堆，那么正好每一堆的操作步数分别为： 1,3,2，最终res = 4 + 1 + 3 + 2 = 10
  - 1.4 总结上述过程：
    - 可以知道们总是需要进行区间最值查找，那么采用线段树的数据结构可以加速这一过程，这里给出一个线段树节点的模板
```cpp
class SegmentTreeNode {
public:
    int start, end, max;
    SegmentTreeNode *left, *right;
    SegmentTreeNode(int start, int end, int max) {
        this->start = start;
        this->end = end;
        this->max = max;
        this->left = this->right = NULL;
    }
}
```
- 2 数学思路：[https://leetcode-cn.com/problems/minimum-number-of-increments-on-subarrays-to-form-a-target-array/solution/xing-cheng-mu-biao-shu-zu-de-zi-shu-zu-zui-shao-ze/](https://leetcode-cn.com/problems/minimum-number-of-increments-on-subarrays-to-form-a-target-array/solution/xing-cheng-mu-biao-shu-zu-de-zi-shu-zu-zui-shao-ze/)
``` cpp
class Solution {
public:
    int minNumberOperations(vector<int>& target) {
        int res = target[0];
        for(int i = 1; i < target.size(); ++i) {
            res += max(0, target[i] - target[i-1]);
        }
        return res;
    }
};
```