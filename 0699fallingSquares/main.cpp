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
#include <string>

using namespace std;
class RangeModule {
public:
    map<int, int, std::less<int>> intervals;
    RangeModule() {
        
    }
    
    void addRange(int left, int right) {
        if(intervals.size() == 0) {
            intervals[left] = right;
            print();
            return ;
        }
        for(auto it = intervals.begin(); it != intervals.end(); ++it) {
            if(it->first >= left) {
                if(it->first > right) {
                    continue;
                }
                while(it != intervals.end() && it->second <= right) {
                    it = intervals.erase(it);
                }
                if(it == intervals.end()){
                    intervals[left] = right;

                } else {
                    if(it->first <= right) {
                        int newRight = it->second;
                        intervals.erase(it);
                        intervals[left] = newRight;
                    }else {
                        intervals[left] = right;
                    }
                }
                print();
                return;
            } else { // it->first < left
                if(it->second < left) {
                    continue;
                }
                int newLeft = it->first;
                while(it != intervals.end() && it->second <= right) {
                    it = intervals.erase(it);
                }
                if(it == intervals.end()){
                    intervals[newLeft] = right;
                } else {
                    if(it->first <= right) {
                        int newRight = it->second;
                        intervals.erase(it);
                        intervals[newLeft] = newRight;
                    }else {
                        intervals[newLeft] = right;
                    }
                }
                print();
                return;
            }
        }
        intervals[left] = right;
        print();
    }
    
    bool queryRange(int left, int right) {
        if(intervals.empty()) {
            return false;
        }

        auto lBig = intervals.upper_bound(left);
        if(lBig != intervals.begin()) {
            --lBig;
            return  lBig->second >= right;
        } else {
            return false;
        }
        return false;
    }
    
    void removeRange(int left, int right) {
        // for(auto it = intervals.begin(); it != intervals.end(); ++it) {
        //     for(int i = 0)
        // }

        auto lBig = intervals.lower_bound(left);
        int newLeft = 0;
        if(lBig != intervals.begin()) {
                // cout << "d1.5" << endl;
            --lBig;
            if(right < lBig->second) {
                intervals[right] = lBig->second;
                intervals[lBig->first] = left;
                print();
                return ;
            } else {
                // cout << "d2" << endl;
                if(lBig->second > left) {
                    // cout << "d2.5" << endl;
                    intervals[lBig->first] = left;
                }
            }
            ++lBig;

            while (lBig != intervals.end() && lBig->second < right) {
                lBig = intervals.erase(lBig);
            }
            if(lBig != intervals.end()) {
                if(lBig->first < right) {
                    int secondRight = lBig->second;
                    intervals.erase(lBig);
                    intervals[right] = secondRight;
                }
            }
        } else {
            while (lBig != intervals.end() && lBig->second < right) {
                lBig = intervals.erase(lBig);
            }
            if(lBig != intervals.end()) {
                if(lBig->first < right) {
                    int secondRight = lBig->second;
                    intervals.erase(lBig);
                    intervals[right] = secondRight;
                }
            }
        }

        print();
        
    }

    void print() {
        // cout << "-----st-----" << endl;
        // for(auto it = intervals.begin(); it != intervals.end(); ++it) {
        //     cout << it->first << " " << it->second << endl;
        // }
        // cout << "-----ed-----" << endl;
    }
};

/**
 * Your RangeModule object will be instantiated and called as such:
 * RangeModule* obj = new RangeModule();
 * obj->addRange(left,right);
 * bool param_2 = obj->queryRange(left,right);
 * obj->removeRange(left,right);
 */



int main() {
    // vector<int> nums = {1, 15, 5, 11};
    // vector<int> nums = {1, 3};
    // vector<int> nums = {1, 3};
    vector<int> nums = {1, 2, 2, 3};
    Solution sl;
    // std::cout << sl.largestRectangleArea(nums) << std::endl;
    std::cout << "Hello, World!" << std::endl;
    return 0;
}
