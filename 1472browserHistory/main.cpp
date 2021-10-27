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
class BrowserHistory {
public:
    int curStep = -1;
    vector<string> allHis;
    bool fromForward = false;
    BrowserHistory(string homepage) {
        allHis.emplace_back(homepage);
        ++curStep;
    }
    
    void visit(string url) {
        // 移除当前指针之后所有的元素，也就是所谓的清除所有的历史
        allHis.erase(allHis.begin()+ curStep + 1, allHis.end());
        allHis.emplace_back(url);
        curStep = allHis.size() - 1;
    }
    
    string back(int steps) {
        fromForward = false;
        curStep = curStep - steps >= 0 ? curStep - steps : 0;
        return allHis[curStep];
    }
    
    string forward(int steps) {
        fromForward = true;
        curStep = (curStep + steps) >= allHis.size() ? allHis.size()-1 : curStep + steps;
        return allHis[curStep];
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
