## 1889 最小浪费空间

### 1 题目
[https://leetcode-cn.com/problems/minimum-space-wasted-from-packaging/submissions/](https://leetcode-cn.com/problems/minimum-space-wasted-from-packaging/submissions/)

### 2 解题思路
- 1 普通思路： 对包裹和箱子方案都排序，然后对于每个方案都去遍历包裹，看最小的空间浪费即可，这带来一个问题，比如包裹为：1,2,3,4,5，然后箱子为4,5,6，则对于每个包裹都要去找适合他的最小箱子，这是冗余的计算，第二条采用逆向思路
- 2 用箱子去找它能装下的最大包裹，那么它能装下的包裹前面所有比他小的包裹都只有用这个箱子去装，比1快
- 3 具体的优化： 使用#include <algorithm>中的upper_bound(vec.begin(), vec.end(), tarValue)去查找(二分查找)更快。

```cpp
class Solution {
public:
    int minWastedSpace(vector<int>& packages, vector<vector<int>>& boxes) {
        long long r = boxes.size();

        // // sort(packages.begin(), packages.end());
        // long long minWaste = INT_MAX;
        // bool oneWayWork = false;
        // for(int supIdx = 0; supIdx < r; supIdx ++) {
        //     long long curWaste = 0;
        //     bool curWayWork = true;
        //     vector<int> tmpPackages(packages.begin(), packages.end());
        //     for(int i = 0; i < packages.size(); ++i) {
        //         long long costForPackI = boxes[supIdx].back() >= packages.back() ? minCostFind(packages[i], boxes[supIdx]) : -1;
        //         if( costForPackI >= 0) {
        //             curWaste += costForPackI;
        //         } 
        //         if(costForPackI < 0) {
        //             curWayWork = false;
        //             break;
        //         }
        //     }
        //     if(curWayWork) {
        //         minWaste = std::min(curWaste, minWaste);
        //     }
        //     oneWayWork = oneWayWork || curWayWork;
        // }
        
        sort(packages.begin(), packages.end(), [](long long a, int b){return a < b;});

        vector<long long> preSum = {0};
        for(int i = 0; i < packages.size(); ++i) {
            preSum.emplace_back(preSum.back() + packages[i]);
        }

        long long minWaste = LLONG_MAX;
        bool oneWayWork = false;
        for(int supIdx = 0; supIdx < r; supIdx ++) {
            sort(boxes[supIdx].begin(), boxes[supIdx].end(), [](int a, int b){return a < b;});

            long long curWaste = 0;
            bool curWayWork = boxes[supIdx].back() >= packages.back();
            if(curWayWork) {
                int curSt = 0;
                // vector<int> tmpPackages(packages.begin(), packages.end());
                for(int i = 0; i < boxes[supIdx].size(); ++i) {
                    long long costUsingBoxI = 0;
                    // long long costUsingBoxI = minCostFind2(boxes[supIdx][i], packages, preSum, curSt, finish);
                        int l = curSt;
                        int r = packages.size() - 1;
                        int maxPackIdx = -1;
                        if(boxes[supIdx][i] < packages[0]) {
                            costUsingBoxI = -1;
                        } else {
                            auto pt_next = prev(upper_bound(packages.begin() + l, packages.end(), boxes[supIdx][i]));
                            maxPackIdx = pt_next - packages.begin();

                            long long res = maxPackIdx < 0 ? -1 : (long long)(maxPackIdx + 1 - curSt) * (long long)boxes[supIdx][i] - (preSum[maxPackIdx + 1] - preSum[curSt]);
                            if(maxPackIdx != -1) {
                                curSt = maxPackIdx + 1;
                            }
                            costUsingBoxI = res;
                        }
                        
                    if( costUsingBoxI >= 0) {
                        curWaste += costUsingBoxI;
                    }
                    if(curSt > preSum.size() - 1) break;
                }
                minWaste = std::min(curWaste, minWaste);
            }

            oneWayWork = oneWayWork || curWayWork;
        }

        return oneWayWork ? minWaste % (1000000000 + 7) : -1;
    }

    int minCostFind(int tarPack, vector<int>& boxes) {
        
        int l = 0;
        int r = boxes.size() - 1;
        int  minCost = INT_MAX;
        while(l <= r) {
            if(boxes[r] >= tarPack) {
                minCost = std::min(boxes[r] - tarPack, minCost);
            }
            if(boxes[l] >= tarPack) {
                minCost = std::min(boxes[l] - tarPack, minCost);
            }
            int mid = (l + r) / 2;
            if(boxes[mid] > tarPack) {
                r = mid - 1;
            } else if(boxes[mid] < tarPack) {
                l = mid + 1;
            } else {
                return 0;
            }
            if(boxes[mid] >= tarPack) {
                minCost = std::min(boxes[mid] - tarPack, minCost);
            }
        }
        
        return minCost == INT_MAX ? -1 : minCost;
    }

   int minCostFind2(int tarBox, vector<int>& packages, vector<long long>& preSum, int& curSt, bool& finish) {
        int l = curSt;
        int r = packages.size() - 1;
        int maxPackIdx = -1;
        if(tarBox < packages[0]) {
            return -1;
        }

        auto pt_next = prev(upper_bound(packages.begin() + l, packages.end(), tarBox));
        maxPackIdx = pt_next - packages.begin();

        // while(l <= r) {
        //     if(packages[l] <= tarBox) {
        //         maxPackIdx = std::max(l, maxPackIdx);
        //     }
        //     int mid = (l + r) / 2;
        //     if(packages[mid] > tarBox) {
        //         r = mid - 1;
        //     } else if(packages[mid] <= tarBox) {
        //         maxPackIdx = std::max(mid, maxPackIdx);
        //         l = mid + 1;
        //     }
        //     // else {

        //     //     maxPackIdx = std::max(mid, maxPackIdx);
        //     //     break;
        //     // }
        // }
        // packages.erase(packages.begin(), packages.begin() + maxPackIdx + 1);
        long long res = maxPackIdx < 0 ? -1 : (long long)(maxPackIdx + 1 - curSt) * (long long)tarBox - (preSum[maxPackIdx + 1] - preSum[curSt]);
        if(maxPackIdx != -1) {
            curSt = maxPackIdx + 1;
        }
        if(curSt > preSum.size() - 1) {
            finish = true;
        }
        return res;
    }
};
```

- 4 关于upper_bound的实现：
```
template <class ForwardIterator, class T>
ForwardIterator upper_bound (ForwardIterator first, ForwardIterator last, const T& val)
{
    ForwardIterator it;
    iterator_traits<ForwardIterator>::difference_type count, step;
    count = std::distance(first,last);
    while (count>0)
    {
        it = first; step=count/2; std::advance (it,step);
        if (!(val<*it))  // 或者 if (!comp(val,*it)), 对应第二种语法格式
            { first=++it; count-=step+1;  }
        else count=step;
    }
    return first;
}
```