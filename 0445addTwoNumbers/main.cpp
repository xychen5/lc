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
