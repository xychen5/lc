## 0295dataStreamMid 数据流中位数

### 1 题目
[https://leetcode-cn.com/problems/find-median-from-data-stream/](https://leetcode-cn.com/problems/find-median-from-data-stream/)

### 2 解题思路
- 1 首先考虑按照中位数将左右两边分开存放，那么左边要获取最大值，右边要获取最小值，于是左边最大堆，右边最小堆即可（注意默认的堆为大根堆！）
- 2 那么注意维护，左右两边的堆的大小差距不能超过一，然后根据中位数和即将需要填入的数字比较，有时需要交换大根堆和小根堆的top

```cpp
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
```