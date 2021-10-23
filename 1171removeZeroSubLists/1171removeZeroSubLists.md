## 1171移除和为0的子链表

### 1 题目：
[https://leetcode-cn.com/problems/remove-zero-sum-consecutive-nodes-from-linked-list/](https://leetcode-cn.com/problems/remove-zero-sum-consecutive-nodes-from-linked-list/)

### 2 解题思路：
个人暴力思路：
- 1 每次移除一个和为0的子数组，返回一个新的链表
- 2 重复上述过程直到没有和为0的子数组

前缀和思路参考：
[采用前缀和判断和为0方法](https://leetcode-cn.com/problems/remove-zero-sum-consecutive-nodes-from-linked-list/solution/c-jian-ji-dai-si-lu-by-philhsu/)：
我们可以考虑如果给的入参不是链表是数组的话，只需要求出前缀和，对于前缀和相同的项，那他们中间的部分即是可以消除掉的，比如以 [1, 2, 3, -3, 4] 为例，其前缀和数组为 [1, 3, 6, 3, 7] ，我们发现有两项均为 3，则 6 和 第二个 3 所对应的原数组中的数字是可以消掉的。

```cpp
class Solution {
public:
    ListNode* newHead;

    ListNode* removeZeroSumSublists(ListNode* head) {
        newHead = head;
        while(removeOneZeroSubList(newHead)){ }
        return newHead;
    }

    bool removeOneZeroSubList(ListNode* newHead) {
        vector<int> valVec;
        ListNode* head = newHead;
        ListNode* p = head;
        while(p != nullptr) {
            valVec.emplace_back(p->val);
            p = p->next;
        }
        size_t len = valVec.size();
        vector<vector<int>> sumMat(len, vector<int>(len));

        // cal all the sub len
        // sumMat[a, b] = sumMat[a, b-1] + a
        ListNode* stPtr = head;
        ListNode* lastStPtr = nullptr;
        for(int st = 0; st < len; ++st) {
            sumMat[st][st] = valVec[st];
            if(sumMat[st][st] == 0) {
                if(nullptr == lastStPtr) {
                    this->newHead = head->next;
                    return true;
                }
                lastStPtr->next = stPtr->next;
                return true;
            }
            ListNode* edPtr = stPtr->next;
            for(int ed = st + 1; ed < len; ++ed) {
                sumMat[st][ed] = sumMat[st][ed-1] + valVec[ed];
                if(sumMat[st][ed] == 0) {
                    if(nullptr == lastStPtr) {
                        this->newHead = edPtr->next;
                        return true;
                    }
                    lastStPtr->next = edPtr->next;
                    return true;
                }
                edPtr = edPtr->next;
            }
            lastStPtr = stPtr;
            stPtr = stPtr->next;
        }
        return false;
    }
};
```
