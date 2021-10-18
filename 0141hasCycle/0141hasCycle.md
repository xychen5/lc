## 0141 单项链表是否有圈

### 1 题目：
[https://leetcode-cn.com/problems/linked-list-cycle/](https://leetcode-cn.com/problems/linked-list-cycle/)

### 2 解题思路：
首先考虑利用标志位判断是否已经遍历过，但是使用O(n)空间；
则思考一个问题： 跑步快的和跑步慢的，若一直跑下去，发生相遇，是不是说明有回环？

于是采用快慢指针的方法：
```cpp
class Solution {
public:
    bool hasCycle(ListNode *head) {
        ListNode * slow = head;
        ListNode * fast = head;

        while(fast != nullptr) {
            // move fast ptr
            if(!fast) {
                return false; // has end
            }
            fast = fast->next;
            if(!fast) {
                return false; // has end
            }
            fast = fast->next;

            // move slow
            slow = slow->next;
            
            // judge if fast catch slow
            if(slow == fast) {
                return true;
            }
        }
    }
};
```

