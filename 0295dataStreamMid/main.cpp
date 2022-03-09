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
class MedianFinder {
public:
    int cnt = 0;
    double mid = 0;
    priority_queue<int, vector<int>, greater<int>> smallHeap;
    priority_queue<int, vector<int>, less<int>> bigHeap;
    MedianFinder() {

    }
    
    void addNum(int num) {
        if(smallHeap.empty()) {
            smallHeap.push(num);
            mid = num;
        } else if(bigHeap.empty()){
            if(num > smallHeap.top()) {
                bigHeap.push(smallHeap.top());
                smallHeap.pop();
                smallHeap.push(num);
            } else {
                bigHeap.push(num);
            }
            mid = (bigHeap.top() + smallHeap.top())*1.0 / 2;
        } else {
            if(0 == cnt%2) {
                if(mid > num * 1.0) {
                    bigHeap.push(num);
                    mid = bigHeap.top();
                } else {
                    smallHeap.push(num);
                    mid = smallHeap.top();
                }
            } else {
                if(smallHeap.size() > bigHeap.size()) {
                    if(smallHeap.top() > num) {
                        bigHeap.push(num);
                    } else {
                        bigHeap.push(smallHeap.top());
                        smallHeap.pop();
                        smallHeap.push(num);
                    }
                } else {
                    if(bigHeap.top() < num) {
                        smallHeap.push(num);
                    } else {
                        smallHeap.push(bigHeap.top());
                        bigHeap.pop();
                        bigHeap.push(num);
                    }
                }
                mid = (smallHeap.top() + bigHeap.top())*1.0 / 2;
            }
        }
        ++cnt;
        // cout << cnt <<  "'s pusing: " << num << "with mid: " << mid << endl;
        // if(cnt >= 2) {
        //     cout << "bigTop/smallTop size: " << bigHeap.size() << "," << smallHeap.size() << " = " << bigHeap.top() << "/" << smallHeap.top() << endl;
        // }
    }
    
    double findMedian() {
        return mid;
    }
};

/**
 * Your MedianFinder object will be instantiated and called as such:
 * MedianFinder* obj = new MedianFinder();
 * obj->addNum(num);
 * double param_2 = obj->findMedian();
 */

int main()
{
    // vector<int> nums = {1, 15, 5, 11};
    // vector<int> nums = {1, 3};
    // vector<int> nums = {1, 3};
    int n = 2;
    vector<int> nums1d = { 1, 0 };
    vector<vector<int>> nums2d1 = { {1}, {0} };
    vector<vector<int>> nums2d4 = { {1,1,3,3},{3,1,4,2},{3,2,4,4},{1,3,2,4},{2,3,3,4} };
    // Solution sl;
    // std::cout << sl.medianSlidingWindow(nums1d, 3) << std::endl;

    // std::cout << ios::left << std::setw(20) << "Hello, World!" << std::setw(5) << "a s " << 1 << std::endl;
    return 0;
    std::cout << "Hello World!\n";
}