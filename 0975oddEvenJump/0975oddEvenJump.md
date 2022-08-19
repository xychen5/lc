## 0975oddEvenJump 奇偶跳

### 1 题目
[https://leetcode.cn/problems/odd-even-jump/](https://leetcode.cn/problems/odd-even-jump/)

### 2 解题思路
- 1 解题思路:
  - 关键的是，假设我们直到每一个位置的i的偶数和奇数的下一跳的喜下标为：oddNext[j]，evenNext[j]
  - 如何dp求方案总数？
    - 我们记录：bool dp[i][0] 和dp[i][1]为，偶数跳能从i跳到最后的结果，奇数跳能从i跳到最后的结果
    - init:         
      - dp[n-1][0] = true;
      - dp[n-1][1] = true;
      - int res = 1
    - dp:
      - i = n-2 -> 0
        - 奇数跳：如果能跳出去 && dp[i][1] 
          - 那么记录dp[i][1] = true; ++res;
        - 偶数跳奇数跳：如果能跳出去 && dp[i][0]
          - 那么记录dp[i][0] = true;
  - 那么如何求oddNext和evennext?
  - 我们以oddnext来算：对于i，求吓一跳j，也就是求大于等于arr[i]的最小的值，如果有多个这样的值，取最小的下标
  - 这种求i的左边最小比他大的数字，用单调栈就很合适
  - 对于 10 13 12 14 15
  - 对于10的话，那么就是12，我们如何做呢？
  - 首先将他们按照从小到大排序，因为我们求的是右边比他大的最小的值，获得下标列表为： 0 2 1 3 4
  - 然后单调栈存什么？值？错，要找的是数字，存的必定是下标，递减还是递增？因为我们要找的是右边的第一个大于我们的数字，找到以后必然要从栈内pop，所以对于当前的下标j，是作为栈内的已经入栈的下标们那些i的下一跳，由于后面进入的数字必然保证大小肯定比已经入栈的大，而且从小到大遍历，必然是最小的比他们大的数字，且下标i需要被j出栈，由于i又小于j，所以是下标递减栈啊，因为一旦递增意味着找到目标了
  - 在考虑找右边最大的比我们小的数字，
    - 因为是找比我们小，所以是递减排序，递减排序的值的下标变成：4 3 1 2 0
    - 那么对于单调栈遍历到j，能保证j比栈内部的元素都是第一个小，然后又因为j要大于i，i就出栈，所以还是递减栈，
    - 单调栈变化为：
    - 4 3 1
    - 4 3 2 ： 下标1偶数跳到下标2
    - 4 3 2 0
    - 所以偶数下一跳为：-1 2 -1 -1 -1 -1


```cpp
class Solution {
public:
    using pii = pair<int, int>;
    int oddEvenJumps(vector<int>& arr) {
        // get sorted arrays 's id[]
        vector<pii> myArr;
        int n = arr.size();
        for(int i = 0; i < n; ++i) {
            myArr.push_back({i, arr[i]});
        }
        
        auto getIdArr = [](vector<pii>& ids) {
            vector<int> ans(ids.size(), -1);
            vector<int> stack;
            for(int i = 0; i < ids.size(); ++i) {
                while(!stack.empty() && ids[i].first > stack.back()) {
                    ans[stack.back()] = ids[i].first;
                    stack.pop_back();
                }
                
                stack.push_back(ids[i].first);
            }
            return ans;
        };

        // make oddNext and evenNext
        auto myArr1 = myArr;
        sort(myArr1.begin(), myArr1.end(), [](const pii& a, const pii& b) {
            return a.second < b.second || (a.second == b.second && a.first < b.first);
        });
       
        auto oddNext = getIdArr(myArr1);

        // auto myArr2 = myArr;
        // reverse(myArr2.begin(), myArr2.end());
        sort(myArr1.begin(), myArr1.end(), [](const pii& a, const pii& b) {
            return a.second > b.second || (a.second == b.second && a.first < b.first);
        });
        auto evenNext = getIdArr(myArr1);

        // cal reach to final pos's chance
        // dp[i][0] means: from i to terminal point by evenJump, if we can?
        // dp[i][1] means: from j to terminal point by oddJump, if we can?
        vector<vector<bool>> dp(n, vector<bool>(2, false));
        dp[n-1][0] = true;
        dp[n-1][1] = true;
        int res = 1;
        for(int i = n-2; i >= 0; --i) {
            int next = oddNext[i];
            if(next != -1 && dp[next][0]) { // odd Jump from i to next
                ++res;
                dp[i][1] = true;
            }
            next = evenNext[i];
            if(next != -1 && dp[next][1]) { // even Jump from i to next
                dp[i][0] = true;
            }
        }

        return res;
    }
};
```