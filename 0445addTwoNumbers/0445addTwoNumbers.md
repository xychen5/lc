## 0445 两数相加

### 1 题目：
[https://leetcode-cn.com/problems/add-two-numbers-ii/submissions/](https://leetcode-cn.com/problems/add-two-numbers-ii/submissions/)

### 2 解题思路：
首先理解题目为10进制加法即可，
然后注意到结果需存放到长的一个链表即可。
最后注意到链表的长度有可能不够。
于是现将两个链表的值依次拿出来放到vector中进行逆转，这样好逆转的多，然后可以开始执行加法，
注意最好将两个vector设置的长一样。

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
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        // reverse two of them
        vector<int> list1;
        vector<int> list2;
        ListNode * h1 = l1;
        while(h1 != nullptr) {
            list1.emplace_back(h1->val);
            h1 = h1->next;
        }
        ListNode * h2 = l2;
        while(h2 != nullptr) {
            list2.emplace_back(h2->val);
            h2 = h2->next;
        }
        
        int addLen = std::max(list1.size(), list2.size());
        reverse(list1.begin(), list1.end());
        reverse(list2.begin(), list2.end());
        
        bool lt10 = false;
        if(list1.size() > list2.size()) {
            list2.resize(addLen, 0);
            for(size_t i = 0; i < addLen; ++i) {
                int nextBit = (int)lt10 + list1[i] + list2[i];
                if(nextBit >= 10){
                    list1[i] = nextBit - 10;
                    lt10 = true;
                } else {
                    list1[i] = nextBit;
                    lt10 = false;
                }
            }
            reverse(list1.begin(), list1.end());

            h1 = l1;
            int tmpI = 0;
            while(h1 != nullptr) {
                h1->val = list1[tmpI++];
                h1 = h1->next;
            }
            if(lt10) {
                ListNode* newHead = new ListNode(1, l1);
                return newHead;
            }
            return l1;
        }else {
            list1.resize(addLen, 0);
            for(size_t i = 0; i < addLen; ++i) {
                int nextBit = (int)lt10 + list1[i] + list2[i];
                if(nextBit >= 10){
                    list2[i] = nextBit - 10;
                    lt10 = true;
                } else {
                    list2[i] = nextBit;
                    lt10 = false;
                }
            }
            reverse(list2.begin(), list2.end());

            h2 = l2;
            int tmpI = 0;
            while(h2 != nullptr) {
                h2->val = list2[tmpI++];
                h2 = h2->next;
            }
            if(lt10) {
                ListNode* newHead = new ListNode(1, l2);
                return newHead;
            }
            
            return l2;
        }
        return nullptr;
    }
};
```
