#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <limits.h>
#include <numeric>
#include <list>
#include <queue>
#include <unordered_set>
#include <unordered_map>
#include <map>

using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
public:
    ListNode* rotateRight(ListNode* head, int k) {
        if(head == nullptr) {
            return nullptr;
        }

        ListNode* p = head;
        ListNode* tail = head;
        int len = 0;
        while(p!=nullptr) {
            tail = p;
            p = p->next;
            ++len;
        }

        k = k % len;
        if(k == 0 || len == 1) {
            return head;
        }

        ListNode* newHead = head;
        ListNode* newTail = nullptr;
        for(int i = 0; i < len - k; ++i) {
            newTail = newHead;
            newHead = newHead->next;
        }

        tail->next = head;
        newTail->next = nullptr;
        return newHead;
    }
};

/**
 * Your BrowserHistory object will be instantiated and called as such:
 * BrowserHistory* obj = new BrowserHistory(homepage);
 * obj->visit(url);
 * string param_2 = obj->back(steps);
 * string param_3 = obj->forward(steps);
 */

int main() {
    // vector<int> nums = {1, 15, 5, 11};
    // vector<int> nums = {1, 3};
    // vector<int> nums = {1, 3};
    vector<int> nums = {1, 2, 2, 3};
    // Solution sl;
    // ListNode *n1 = new ListNode(1);
    // ListNode *n2 = new ListNode(2); n1->next = n2;
    // ListNode *n3 = new ListNode(3); n2->next = n3;
    // std::cout << ios::left << std::setw(20) << "Hello, World!" << std::setw(5) << "a s " << 1 << std::endl;
    return 0;
}
