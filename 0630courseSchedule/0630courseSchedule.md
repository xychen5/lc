## 0630courseSchedule 课程表3

### 1 题目
[https://leetcode.cn/problems/course-schedule-iii/](https://leetcode.cn/problems/course-schedule-iii/)

### 2 解题思路
- 1 解题思路:
  - 首先考虑：对于前i-1个课程，我们已经获得最优的方案假设，然后对于当前到来的课程，若果可以上这个课程，那么直接加进来就是最优解，不能的话那就就看看是否能替换掉已经选择的课程，这样在保证最小总课时的情况下得到相同的门数


```cpp
class Solution {
public:
    using pii = pair<int, int>;

    using CMP = function<bool(const pii& a, const pii&b)>;

    
    int scheduleCourse(vector<vector<int>>& courses) {
        // 贪心思路： 总是用当前遍历到的课程，去替换掉之前选择的某个课程，达到更小的课程总时间
        
        sort(courses.begin(), courses.end(), [](const vector<int>& c1, const vector<int>& c2) {
            return c1[1] < c2[1];
        });

        CMP myCmp = [](const pii& a, const pii&b) {
            return a.first < b.first;
        };

        priority_queue<pii, vector<pii>, CMP> maxHeap(myCmp);

        // maxHeap.push({courses.front()[0], courses.front()[1]});
        int curEndDay = 0;

        for(int i = 0; i < courses.size(); ++i) {
            auto c = courses[i];
            // if we can use this course
            if(curEndDay + c[0] <= c[1]) {
                maxHeap.push({c[0], c[1]});
                curEndDay += c[0];
                // cout <<"using: " << c[0] << " " << c[1] << endl;
            } else {
                // cout <<"not us: " << c[0] << " " << c[1] << endl;
                // cannot use it, try to replace it using a bigger duration class chosen
                if(!maxHeap.empty() && maxHeap.top().first > c[0]) {
                    // cout <<"but rep: " << c[0] << " " << c[1] << endl;
                    curEndDay += (c[0] - maxHeap.top().first);
                    maxHeap.pop();
                    maxHeap.push({c[0], c[1]});
                } 
            }
        }

        return maxHeap.size();
    }
};

```