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
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};
    ListNode* reverseKGroup(ListNode* head, int k) {
        // return headK -> reverse(afterHeadK, k);
        return reverse(head, k);
    }

    ListNode* reverse(ListNode* head, int k ) {
        ListNode* tmp = head;
        vector<ListNode*> vec = {};
        for(int i = 0; i < k; ++i) {
            if(tmp != nullptr) {
                vec.emplace_back(tmp);
                tmp = tmp -> next;
            }
        }

        if(vec.size() != k) {
            return head;
        }

        ListNode* nextHead = vec.back()->next;

        for(int i = k-1; i >= 1; --i) {
            // cout << i << "**" << endl;
            vec[i]->next = vec[i-1];
            // cout << vec[i]->val << " -> " << vec[i-1]->val << endl;
        }
        vec[0]->next = reverse(nextHead, k);
        
        // cout << "asdf**" << endl;
        return vec.back();
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