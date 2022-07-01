## 2035minDiff 将数组分成两个数组并最小化数组和的差

### 1 题目
[https://leetcode.cn/problems/partition-array-into-two-arrays-to-minimize-sum-difference/](https://leetcode.cn/problems/partition-array-into-two-arrays-to-minimize-sum-difference/)

### 2 解题思路
- 1 解题思路：类似的题目：https://leetcode.cn/problems/partition-array-into-two-arrays-to-minimize-sum-difference/
  - 1.1 将数组分成左半边和右半边，分别用left[len][]存储左侧长度为len的子序列的和，右侧类似
  - 1.2 利用youngTable，在对于左侧的每一个长度len，去右侧的right[n/2 - len]中，找出一对儿他们的和与sum(原始数组)/2最接近，复杂度为o(left[len].size + right[n/2 - len].size()，这就是youngTalbe的魅力。


```cpp
class Solution {
public:

    vector<vector<long long>> makeSubseqSum(const vector<long long>& nums) {
        long long n = nums.size();
        long long sumCnt = (1 << n) - 1;
        vector<vector<long long>> ans(n + 1, vector<long long>{});
        
        for(long long bits = sumCnt; bits > 0; --bits) {
            long long setBitCnt = 0;
            long long curBits = bits;
            long long curSum = 0;
            // cout << bitset<8>(curBits) << endl;
            while(curBits > 0) {
                long long pos = ffs(curBits) - 1;
                ++setBitCnt;
                curSum += nums[pos];
                curBits = curBits - (1 << pos);
            }

            ans[setBitCnt].push_back(curSum);
            // cout << "setBitCnt: " << setBitCnt << " " << curSum << "\n";
        }
        return ans;
    }

    int minimumDifference(vector<int>& nums) {
        long long n = nums.size();
        double allSum = accumulate(nums.begin(), nums.end(), 0);
        double goal = allSum * 1.0 / 2.0;

        long long mid = nums.size() >> 1;
        auto left = makeSubseqSum(vector<long long>{nums.begin(), nums.begin() + mid});
        auto right = makeSubseqSum(vector<long long>{nums.begin() + mid, nums.end()});
        long long curRes = INT_MAX;
        // all fron left or all from right has the same result
        curRes = min((double)curRes, abs(allSum - 2*left[mid][0]));

        // suppose lCnt is choosed form left
        for(long long lCnt = 1; lCnt <= mid - 1; ++lCnt) {
            long long rCnt = mid - lCnt;
            auto& lVec = left[lCnt];
            auto& rVec = right[rCnt];
            sort(lVec.begin(), lVec.end());
            sort(rVec.begin(), rVec.end());
            
            // young table to search goal
            long long lPtr = lVec.size() - 1;
            long long rPtr = 0;
            while(lPtr >= 0 && rPtr < rVec.size()) {
                double curSum = lVec[lPtr] + rVec[rPtr];
                double curDiff = abs(allSum - 2*curSum);
                if(curDiff < curRes) {
                    curRes = curDiff;
                }

                if(abs(curDiff) < 0.00001) { 

                    return 0;
                } else if(curSum > goal) {
                    --lPtr;
                } else if (curSum < goal) {
                    ++rPtr;
                } else  {
                    
                }
            } 
        }

        return curRes;


    }
};
```