## 0023mergeKSortedList 合并k个升序链表

### 1 题目
[https://leetcode.cn/problems/merge-k-sorted-lists/](https://leetcode.cn/problems/merge-k-sorted-lists/)

### 2 解题思路
- 1 解题思路:
  - 1.1 用一个优先队列维护目前所有队列的游标，每次取顶部的游标，将该游标的后继节点加入优先队列即可

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
    constexpr static auto cmp = [](const pair<int, ListNode*>& a, const pair<int, ListNode*>& b) {
        return a.second->val > b.second->val;
    };

    ListNode* mergeKLists(vector<ListNode*>& lists) {
        int n = lists.size();
        if(0 == n) {
            return nullptr;
        }

        // using a pq to store the cursor of each linklist
        // of course: the int is not need ^~^
        priority_queue<pair<int, ListNode*>, vector<pair<int, ListNode*>>, decltype(cmp)> pq(cmp);
        // init it
        vector<ListNode*> cursors(lists);
        for(int i = 0; i < n; ++i) {
            // only merge not null linklist
            if(nullptr != cursors[i]) {
                pq.push({i, cursors[i]});
            }
        }
        
        ListNode* root = nullptr;
        ListNode* curNode = root;
        bool init = false;
        while(!pq.empty()) {
            auto top = pq.top();
            pq.pop();
            if(!init) {
                root = top.second;
                curNode = root;
                init = true;
            } else {
                curNode->next = top.second;
                curNode = curNode->next;
            }

            if(nullptr != top.second->next) {
                pq.push({top.first, top.second->next});
            }
        }
        return root;
    }
};
```