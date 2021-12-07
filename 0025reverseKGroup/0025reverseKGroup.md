## 0025 最大因数联通分量大小

### 1 题目
[https://leetcode-cn.com/problems/reverse-nodes-in-k-group/](https://leetcode-cn.com/problems/reverse-nodes-in-k-group/)

### 2 解题思路
- 1 个人思路：
  - 首先很明显能够发现子问题的痕迹，子问题就是翻转长度为k的链表
  - 翻转用长度为k的栈去模拟即可
- 2 优化： 使用常数空间：
  - 使用三个指针，a->b->c的链表的话，那么就是说(三个指针相当于滑动窗口的感觉)：
  - 记录下a,b,c的指针，然后把a<-b<-c,然后移动这三个指针即可

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
    ListNode* reverseKGroup(ListNode* head, int k) {
        // return headK -> reverse(afterHeadK, k);
        return reverse(head, k);
    }

    ListNode* reverse(ListNode* head, int k ) {
        ListNode* tmp = head;
        vector<ListNode*> vec = {};
        for(int i = 0; i < k; ++i) {
            if(tmp != nullptr) {
                vec.emplace_back(tmp);
                tmp = tmp -> next;
            }
        }

        if(vec.size() != k) {
            return head;
        }

        ListNode* nextHead = vec.back()->next;

        for(int i = k-1; i >= 1; --i) {
            // cout << i << "**" << endl;
            vec[i]->next = vec[i-1];
            // cout << vec[i]->val << " -> " << vec[i-1]->val << endl;
        }
        vec[0]->next = reverse(nextHead, k);
        
        // cout << "asdf**" << endl;
        return vec.back();
    }
};
```
