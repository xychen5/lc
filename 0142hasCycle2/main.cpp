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
    ListNode *detectCycle(ListNode *head) {
        ListNode * slow = head;
        ListNode * fast = head;

        int cycleLen = 0;
        int fastMov = 0;
        int slowMov = 0;
        // fast: 3 0 2 4 0 2 4 0 2 4 0
        // slow: 3 2 0 4 2 0 4
        // fast: 1 1 1 1
        // slow: 1 2 1

        while(fast != nullptr) {
            // move fast ptr
            if(!fast) {
                return nullptr; // has end
            }
            fast = fast->next;
            if(!fast) {
                return nullptr; // has end
            }
            fast = fast->next;
            fastMov += 2;

            // move slow
            slow = slow->next;
            slowMov += 1;
            
            // judge if fast catch slow
            if(slow == fast) {
                break;
            }
        }
        if(!fast){
            return nullptr;
        }

        cycleLen = fastMov - slowMov;
        ListNode *pRes = head;
        ListNode *curRes = head;
        for (int i = 0; i < slowMov+1; ++i) {
            for(int k = 0; k < fastMov+1; ++k) {
                curRes = curRes->next;
                if(pRes == curRes) {
                    return pRes;
                }
            }
            pRes = pRes->next;
            curRes = pRes;
        }
        return nullptr;
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
