## 0707设计链表

### 1 题目：
[https://leetcode-cn.com/problems/design-front-middle-back-queue/](https://leetcode-cn.com/problems/design-front-middle-back-queue/)

### 2 解题思路：

```cpp


class FrontMiddleBackQueue {
public:

    struct ListNode {
        long long val;
        ListNode *next;
        ListNode(long long x) : val(x), next(NULL) {}
        ListNode(long long x, ListNode* next): val(x), next(next) {}
    };
    
    long long len = 0;
    ListNode* head = nullptr;
    ListNode* tail = nullptr;


    long long get(long long index) {
        if(index >= len || index < 0) {
            return -1;
        }
        
        ListNode* curPtr = head;
        ListNode* lastPtr = nullptr;
        for(long long pos = 0; pos < len; ++pos) {
            if(pos == index) {
                return curPtr->val;
            }
            lastPtr = curPtr;
            curPtr = curPtr->next;
        }
        return 0;
    }
    
    void addAtHead(long long val) {
        head = new ListNode(val, head);
        if(nullptr == tail) {
            tail = head;
        }
        ++len;
    }
    
    void addAtTail(long long val) {
        ListNode* newTailNode = new ListNode(val, nullptr);
        if(nullptr != tail) {
            tail->next = newTailNode;
            tail = newTailNode;
        } else {
            tail = newTailNode;
            if(nullptr == head) {
                head = tail;
            }
        }
        ++len;
    }
    
    void addAtIndex(long long index, long long val) {
        if(index > len || index < 0) {
            return;
        }
        if(index == len) {
            addAtTail(val);
            return;
        }
        
        ListNode* curPtr = head;
        ListNode* lastPtr = nullptr;
        for(long long pos = 0; pos < len; ++pos) {
            if(pos == index) {
                if(pos == 0) {
                    addAtHead(val);
                    break;
                } else {
                    lastPtr->next = new ListNode(val, curPtr);
                    break;
                }
            }
            lastPtr = curPtr;
            curPtr = curPtr->next;
        }
        ++len;
    }
    
    void deleteAtIndex(long long index) {
        if(index >= len || index < 0) {
            return;
        }
        
        ListNode* curPtr = head;
        ListNode* lastPtr = nullptr;
        for(long long pos = 0; pos < len; ++pos) {
            if(pos == index) {
                if(pos == 0) {
                    ListNode* curHead = head;
                    head = head->next;
                    delete curHead;
                    curPtr = nullptr;
                    break;
                } else {
                    lastPtr->next = curPtr->next;
                    delete curPtr;
                    curPtr = nullptr;
                    if(pos == len - 1) {
                        tail = lastPtr;
                    }
                    break;
                }
            }
            lastPtr = curPtr;
            curPtr = curPtr->next;
        }

        --len;
        if(len == 0) {
            tail = head = nullptr;
        }
    }

    FrontMiddleBackQueue() {

    }
    ~FrontMiddleBackQueue() {

    }
    
    void pushFront(long long val) {
        addAtHead(val);
    }
    // len->idx
    // 0    0
    // 1    0
    // 2    1
    // 3    1
    // 4    2
    // 5    2

        // long long midIdx = len % 2 == 0 ? len / 2 - 1 : len/2;
        long long midIdx = len /2;
        if(len == 1) {
            addAtHead(val);
            return;
        }
        addAtIndex(midIdx, val);
    }
    
    void pushBack(long long val) {
        addAtTail(val);
    }
    
    long long popFront() {
        if(len == 0) {
            return -1 ;
        }
        long long ret = get(0);
        deleteAtIndex(0);
        return ret;
    }
    
    long long popMiddle() {
        long long midIdx = len % 2 == 0 ? len/2-1 : len/2;
        if(len == 0) {
            return -1 ;
        }
        long long ret = get(midIdx);
        deleteAtIndex(midIdx);
        return ret;
    }
    // 2 3 1 -> 3 2 1 
    long long popBack() {
        if(len == 0) {
            return -1 ;
        }
        long long ret = get(len - 1);
        deleteAtIndex(len - 1);
        return ret;
    }
};

/**
 * Your FrontMiddleBackQueue object will be instantiated and called as such:
 * FrontMiddleBackQueue* obj = new FrontMiddleBackQueue();
 * obj->pushFront(val);
 * obj->pushMiddle(val);
 * obj->pushBack(val);
 * long long param_4 = obj->popFront();
 * long long param_5 = obj->popMiddle();
 * long long param_6 = obj->popBack();
 */
```
