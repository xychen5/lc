## 0517superWashingMachines 超级洗衣机

### 1 题目
[https://leetcode.cn/problems/super-washing-machines/](https://leetcode.cn/problems/super-washing-machines/)

### 2 解题思路
- 1 解题思路:
  - 首先考虑：衣服交换只能在相邻的洗衣机之间发生，这样我们手先将每个数字减去平均数，正负代表要给出衣服和收入衣服
  - 然后注意到，由于是相邻才能交换，那么我们可以将整个数组分成左边A右边B，A的累计和就是AB要交换的衣服的个数，求个最大值
  - 然后就是看AB中要给出衣服的最大数目的洗衣机，因为收入衣服一次移动可能收入2个，不具有代表性，但是给出衣服一次必须是只能给出1个，联合步骤2的最大值即可

```cpp
class Solution {
public:
    int findMinMoves(vector<int>& machines) {
        //  0  0 11 5
        // -4 -4 7  1 after 2
        // -3 -3 6  0 then 6

        // maxCost: cost1: front part and back part's transfer
        //          cost3: the biggest machine to be zero, must be positive one, 
        //                 cause nega ones, could change 2 in one move

        int sum = 0;
        int n = machines.size();

        for(auto m : machines) {
            sum += m;
        }
        
        if(sum % n != 0) {
            return -1;
        }

        int avg = sum / n;
        int res = INT_MIN;
        int signleMax = INT_MIN;
        int acc = 0;
        for(auto& m : machines) {
            m -= avg;
            acc += m;
            signleMax = max(signleMax, m);
            res = max(res, max(abs(acc), signleMax));
        }
        return res;

    }
};
```