## 0141 单项链表是否有圈

### 1 题目：
[https://leetcode-cn.com/problems/linked-list-cycle-ii/](https://leetcode-cn.com/problems/linked-list-cycle-ii)

### 2 解题思路：
首先考虑利用标志位判断是否已经遍历过，但是使用O(n)空间；
则思考一个问题： 跑步快的和跑步慢的，若一直跑下去，发生相遇，是不是说明有回环？

于是采用快慢指针的方法：
那么如何判断回环入点呢？
从head节点开始，遍历剩下的每个节点，要是没有节点和该节点地址相同，则对head->next的节点做上述的事情，这样搜索下去一定能够找到入口点
```cpp
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    ListNode *detectCycle(ListNode *head) {
        ListNode * slow = head;
        ListNode * fast = head;

        int cycleLen = 0;
        int fastMov = 0;
        int slowMov = 0;
        // fast: 3 0 2 4 0 2 4 0 2 4 0
        // slow: 3 2 0 4 2 0 4
        // fast: 1 1 1 1
        // slow: 1 2 1

        while(fast != nullptr) {
            // move fast ptr
            if(!fast) {
                return nullptr; // has end
            }
            fast = fast->next;
            if(!fast) {
                return nullptr; // has end
            }
            fast = fast->next;
            fastMov += 2;

            // move slow
            slow = slow->next;
            slowMov += 1;
            
            // judge if fast catch slow
            if(slow == fast) {
                break;
            }
        }
        if(!fast){
            return nullptr;
        }

        cycleLen = fastMov - slowMov;
        ListNode *pRes = head;
        ListNode *curRes = head;
        for (int i = 0; i < slowMov+1; ++i) {
            for(int k = 0; k < fastMov+1; ++k) {
                curRes = curRes->next;
                if(pRes == curRes) {
                    return pRes;
                }
            }
            pRes = pRes->next;
            curRes = pRes;
        }
        return nullptr;
    }
};
```

