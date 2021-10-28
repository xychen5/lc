## 1367isSubPath

### 1 题目：
[https://leetcode-cn.com/problems/rotate-list/](https://leetcode-cn.com/problems/rotate-list/)

### 2 解题思路：
观察到，长度为n的链表，转k次，那么就是让list[n-k]成为新的链表头部，
原来的尾部接到头部，新的尾部置空即可

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
    ListNode* rotateRight(ListNode* head, int k) {
        if(head == nullptr) {
            return nullptr;
        }

        ListNode* p = head;
        ListNode* tail = head;
        int len = 0;
        while(p!=nullptr) {
            tail = p;
            p = p->next;
            ++len;
        }

        k = k % len;
        if(k == 0 || len == 1) {
            return head;
        }

        ListNode* newHead = head;
        ListNode* newTail = nullptr;
        for(int i = 0; i < len - k; ++i) {
            newTail = newHead;
            newHead = newHead->next;
        }

        tail->next = head;
        newTail->next = nullptr;
        return newHead;
    }
};

/**
 * Your BrowserHistory object will be instantiated and called as such:
 * BrowserHistory* obj = new BrowserHistory(homepage);
 * obj->visit(url);
 * string param_2 = obj->back(steps);
 * string param_3 = obj->forward(steps);
 */
```