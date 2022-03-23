## 0000_interview_mergeKList 合并k个升序链表

### 1 题目
[https://www.nowcoder.com/practice/65cfde9e5b9b4cf2b6bafa5f3ef33fa6?tpId=295&tqId=724&ru=/exam/oj&qru=/ta/format-top101/question-ranking&sourceUrl=%2Fexam%2Foj](https://www.nowcoder.com/practice/65cfde9e5b9b4cf2b6bafa5f3ef33fa6?tpId=295&tqId=724&ru=/exam/oj&qru=/ta/format-top101/question-ranking&sourceUrl=%2Fexam%2Foj)

### 2 解题思路
- 1 每次取最小的头，那么如何快速获取最小的头？使用优先队列维护

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
    ListNode *mergeKLists(vector<ListNode *> &lists) {
        auto cmp = [](ListNode& a, ListNode& b) {
            return a.val > b.val;
        };
        priority_queue<ListNode, vector<ListNode>, decltype(cmp)> pq(cmp);
        
        if(0 == lists.size()) {
            return nullptr;
        }
        
        // push all head
        for(auto& node : lists) {
            if(node == nullptr) {
                continue;
            }
            pq.push(*node);
        }
        
        ListNode* head = nullptr;
        ListNode* root = nullptr;
        
        // merge all heads
        while(!pq.empty()) {
            auto curTop = pq.top();
            pq.pop();
            if(nullptr == head) {
                head = new ListNode(curTop.val);
                root = head;
            } else {
                head->next = new ListNode(curTop.val);
                head = head->next;
            }
            
            if(nullptr != curTop.next) {
                pq.push(*(curTop.next));
            }
        }
        
        return root;

    }
};
```
