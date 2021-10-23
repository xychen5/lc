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
int main() {
    // vector<int> nums = {1, 15, 5, 11};
    // vector<int> nums = {1, 3};
    // vector<int> nums = {1, 3};
    vector<int> nums = {1, 2, 2, 3};
    Solution sl;
    ListNode *n1 = new ListNode(1);
    ListNode *n2 = new ListNode(2); n1->next = n2;
    ListNode *n3 = new ListNode(3); n2->next = n3;
    sl.detectCycle(n1);
    // std::cout << ios::left << std::setw(20) << "Hello, World!" << std::setw(5) << "a s " << 1 << std::endl;
    return 0;
}
