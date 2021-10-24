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
