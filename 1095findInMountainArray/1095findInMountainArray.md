## 1095findInMountainArray 山脉数组中查找目标值

### 1 题目
[https://leetcode.cn/problems/find-in-mountain-array/](https://leetcode.cn/problems/find-in-mountain-array/)

### 2 解题思路
- 1 解题思路：
  - 1.1 二分法：首先找到山顶，接着在两边分别二分找target就行 

```cpp
class Solution {
public:
    int findInMountainArray(int target, MountainArray &mountainArr) {
        int len = mountainArr.length();
        int ed = len-1, st = 0; 
        int peakIdx;
        while(st < ed) {
            peakIdx = (st + ed) >> 1;
            // cout << "st/ed/mid: " << st << " " << ed << " " << peakIdx << endl;
            int h = mountainArr.get(peakIdx);
            int lh = mountainArr.get(peakIdx - 1);
            int rh = mountainArr.get(peakIdx + 1);
            if(lh < h && h < rh) {
                st = peakIdx + 1;
            } else if(lh > h && h > rh){
                ed = peakIdx;
            } else {
                st = peakIdx;
                break;
            }
        }
        peakIdx = st;
        // cout << "peak is : " << st << "  " << mountainArr.get(st) <<endl;
        
        ed = peakIdx, st = 0; 
        int mid;
        while(st < ed) {
            mid = (st + ed) >> 1;
            int h = mountainArr.get(mid);
            if(h < target) {
                st = mid + 1;
            } else {
                ed = mid;
            }
        }
        if(mountainArr.get(st) == target) {
            return st;
        }

        ed = len-1, st = peakIdx; 
        while(st < ed) {
            mid = (st + ed) >> 1;
            int h = mountainArr.get(mid);
            if(h > target) {
                st = mid + 1;
            } else {
                ed = mid;
            }
        }
        if(mountainArr.get(st) == target) {
            return st;
        }

        return -1;
    }
};
```