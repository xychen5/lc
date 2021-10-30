## 0109storedListToBST

### 1 题目：
[https://leetcode-cn.com/problems/merge-in-between-linked-lists/](https://leetcode-cn.com/problems/merge-in-between-linked-lists/)

### 2 解题思路：

- 最普通的链表拼接
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
    ListNode* mergeInBetween(ListNode* list1, int a, int b, ListNode* list2) {
        
        ListNode* tail2 = list2;
        while(tail2->next != nullptr) {
            tail2 = tail2->next;
        }

        int curIdx = 0;
        ListNode* beforeCut = list1;
        for(int i = 0; i < a-1; ++i) {
            beforeCut = beforeCut->next;
        }

        ListNode* behindCut = beforeCut->next;
        for(int i = a; i < b+1; i++) {
            behindCut = behindCut->next;
        }

        beforeCut->next = list2;
        tail2->next = behindCut;
        
        // todo: delete cut nodes
        
        return list1;
    }
};
```