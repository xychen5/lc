## 1944. 队列中可以看到的人数 canSeePersonsCount

### 1 题目
[https://leetcode-cn.com/problems/number-of-visible-people-in-a-queue/](https://leetcode-cn.com/problems/number-of-visible-people-in-a-queue/)

### 2 解题思路
- 1 很显然，这种看得见看不见的，需要递增排序和递减排序，很容易想到单调栈
  - 1.1 思路： 注意一点，由于题目说的是人的右边有多少自己是看得见的？于是，自然会想到从右往左使用单调栈，那么所谓的看得见，就是当前元素a[i]比右边的队里多少人要高，而且队里的人从右往左是单调增，那么由于我们反向遍历，单调栈就是递减栈
  - 1.2 然后考虑普通情况： 
    - a) 需要出栈： 比如： 8 1 2 3 4 10，对于8来说，单调栈为：10 4 3 2 1，那么一直出站到第一个比他大的，就是比他矮的他能看到的，然后再加上一个比他高的就行
    - b) 不需要出栈：1 2 3 4，遇到1的时候，1正常入栈，所以它的可见朋友就只有一个就是2 
  - 1.3 特殊情况： 
    - a) 8 1 2 3 4，那么遇到8的时候，栈会空，就不需要加1
    - b) 1 2 8，遇到8，它右边没有值，不需要加一
``` cpp
class Solution {
public:
    vector<int> canSeePersonsCount(vector<int>& heights) {
        // descending mono stack from end to start, 
        vector<int> mono = {INT_MAX};
        int n = heights.size();
        vector<int> res;
        for(int i = n - 1; i >= 0; --i) {
            int seeCnt = 0;
            // cout << "back/cur: " << mono.back() <<"/" << heights[i] << endl;
            bool popFlag = false;
            while(mono.back() < heights[i]) {
                ++seeCnt;
                popFlag = true;
                // cout << "pop : " << mono.back() << endl;
                mono.pop_back();
            }

            if(!popFlag && i != n-1) {
                seeCnt++;
            }

            // when pop and the mono stack is not empty
            if(popFlag && mono.size() != 1) {
                ++seeCnt;
            }
            // cout << "seeing: " << seeCnt << endl;
            res.push_back(seeCnt);
            mono.push_back(heights[i]);
        }
        reverse(res.begin(), res.end());
        return res;
    }
};
```