// ConsoleApplication1.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
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
#include <set>

using namespace std;
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
    ListNode *mergeKLists(vector<ListNode *> &lists) {
        auto cmp = [](ListNode& a, ListNode& b) {
            return a.val > b.val;
        };
        priority_queue<ListNode, vector<ListNode>, decltype(cmp)> pq(cmp);
        
        if(0 == lists.size()) {
            return nullptr;
        }
        
        // push all head
        for(auto& node : lists) {
            if(node == nullptr) {
                continue;
            }
            pq.push(*node);
        }
        
        ListNode* head = nullptr;
        ListNode* root = nullptr;
        
        // merge all heads
        while(!pq.empty()) {
            auto curTop = pq.top();
            pq.pop();
            if(nullptr == head) {
                head = new ListNode(curTop.val);
                root = head;
            } else {
                head->next = new ListNode(curTop.val);
                head = head->next;
            }
            
            if(nullptr != curTop.next) {
                pq.push(*(curTop.next));
            }
        }
        
        return root;

    }
};
int main()
{
    // vector<int> nums = {1, 15, 5, 11};
    // vector<int> nums = {1, 3};
    // vector<int> nums = {1, 3};
    int n = 2;
    vector<int> nums1d = { 1, 0 };
    vector<vector<int>> nums2d1 = { {1}, {0} };
    vector<vector<int>> nums2d4 = { {1,1,3,3},{3,1,4,2},{3,2,4,4},{1,3,2,4},{2,3,3,4} };
    Solution sl;
    // std::cout << sl.medianSlidingWindow(nums1d, 3) << std::endl;

    // std::cout << ios::left << std::setw(20) << "Hello, World!" << std::setw(5) << "a s " << 1 << std::endl;
    return 0;
    std::cout << "Hello World!\n";
}