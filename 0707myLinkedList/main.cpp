#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <limits.h>
#include <numeric>

using namespace std;
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class MyLinkedList {
public:


    struct ListNode {
        int val;
        ListNode *next;
        ListNode(int x) : val(x), next(NULL) {}
        ListNode(int x, ListNode* next): val(x), next(next) {}
    };
    
    int len = 0;
    ListNode* head = nullptr;
    ListNode* tail = nullptr;

    MyLinkedList() {
        
    }
    
    int get(int index) {
        if(index >= len || index < 0) {
            return -1;
        }
        
        ListNode* curPtr = head;
        ListNode* lastPtr = nullptr;
        for(int pos = 0; pos < len; ++pos) {
            if(pos == index) {
                return curPtr->val;
            }
            lastPtr = curPtr;
            curPtr = curPtr->next;
        }
        return 0;
    }
    
    void addAtHead(int val) {
        head = new ListNode(val, head);
        if(nullptr == tail) {
            tail = head;
        }
        ++len;
    }
    
    void addAtTail(int val) {
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
    
    void addAtIndex(int index, int val) {
        if(index > len || index < 0) {
            return;
        }
        if(index == len) {
            addAtTail(val);
            return;
        }
        
        ListNode* curPtr = head;
        ListNode* lastPtr = nullptr;
        for(int pos = 0; pos < len; ++pos) {
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
    
    void deleteAtIndex(int index) {
        if(index >= len || index < 0) {
            return;
        }
        
        ListNode* curPtr = head;
        ListNode* lastPtr = nullptr;
        for(int pos = 0; pos < len; ++pos) {
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
};

int main() {
    // vector<int> nums = {1, 15, 5, 11};
    // vector<int> nums = {1, 3};
    // vector<int> nums = {1, 3};
    vector<int> nums = {1, 2, 2, 3};
    Solution sl;
    ListNode *n1 = new ListNode(1);
    ListNode *n2 = new ListNode(2); n1->next = n2;
    ListNode *n3 = new ListNode(3); n2->next = n3;
    // std::cout << ios::left << std::setw(20) << "Hello, World!" << std::setw(5) << "a s " << 1 << std::endl;
    return 0;
}
