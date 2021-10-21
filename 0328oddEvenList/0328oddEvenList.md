## 0328 奇偶链表

### 1 题目：
[https://leetcode-cn.com/problems/odd-even-linked-list/](https://leetcode-cn.com/problems/odd-even-linked-list/)

### 2 解题思路：
首先假设已经形成了一个如下链表：
(oddList)->(evenList)->curNode->(not sort yet list)
那么我们主要关注，如何将curNode插入oddList和evenList中间，
以及将evenList的curNode的下一个加入evenList，
然后找到下一个curNode，
然后更新oddList和evenList即可。

```cpp
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
    ListNode* oddEvenList(ListNode* head) {
        int len = 0;
        ListNode* p = head;
        while(p != nullptr) {
            ++len;
            
            p = p->next;
        }

        if (!head || (!(head->next))) {
            return head;
        }
        // 1->2->3->4->5->6
        // 1->3->2->4->5->6

        // 1->2->3->null
        // 1->3->2->null
        ListNode* oddStPtr = head;
        ListNode* oddEdPtr = head;
        ListNode* evenStPtr = head->next;
        ListNode* evenEdPtr = head->next;
        ListNode* curPtr = evenEdPtr->next;

        // 1->2->3->4->5->6
        // 1->3->2->4->5->6

        // 1->2->3->4->5->6
        // 1->3->2->4->5->6
        while(1){
            if(!curPtr) {
                return head;
            }

            oddEdPtr->next = curPtr; // 3->5
            evenEdPtr->next = curPtr->next; // 4->6
            evenEdPtr = curPtr->next; // ed: 4 => 6
            curPtr->next = evenStPtr; // 5->2
            oddEdPtr = curPtr;

            // return head;
            if(evenEdPtr!=nullptr) {
                curPtr = evenEdPtr->next;
                if(curPtr == nullptr) {
                    return head;
                }
            }else {
                return head;
            }
        }
    }

};
```

