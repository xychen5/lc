## 1537maxScore 最大得分

### 1 题目
[https://leetcode.cn/problems/get-the-maximum-score/submissions/](https://leetcode.cn/problems/get-the-maximum-score/submissions/)

### 2 解题思路
- 1 解题思路：
  - 1.1 考虑这样一个感觉： 以相同点作为joint，将整个数列分成好几段，然后每一段取最大即可
  - 1.2 那么我们用sum1和sum2记录，分别遍历nums1和nums2的时候的和，每次将ssum1和sum2移动到同一个joint，然后才开始下一个joint，最后一个joint的后面加起来然后取模即可
  - 1.3 要注意，处理每个joint的过程中不要去取模，否则容易导致sum大小不是本来的大小，应该在到达同一个joint之后去取模，然后同步sum1和sum2为更大的那个sum
```cpp
class Solution {
public:
static const int mod = 1'000'000'007;
    int maxSum(vector<int>& nums1, vector<int>& nums2) {
        long long n1 = nums1.size();
        long long n2 = nums2.size();

        vector<long long> preSum1(n1 + 1, 0);
        vector<long long> preSum2(n2 + 1, 0);
        
        for(long long i = 1; i <= n1; ++i) {
            preSum1[i] = preSum1[i-1] + nums1[i-1];
        }
        for(long long i = 1; i <= n2; ++i) {
            preSum2[i] = preSum2[i-1] + nums2[i-1];
        }
        
        unordered_map<long long, long long> toIdx;
        long long idx = 0;
        for(auto num : nums1) {
            toIdx[num] = idx;
            ++idx;
        }

        // jolong long: <idx in nums1, idx in nums2>
        vector<pair<long long, long long>> joints;
        long long idx2 = 0;
        for(auto num2 : nums2) {
            if(toIdx.count(num2) != 0) {
                joints.emplace_back(toIdx[num2], idx2);
            }
            ++idx2;
        }

        if(0 == joints.size()) {
            return max(preSum1.back(), preSum2.back());
        }

        long long sum1 = 0;
        int cur1 = 0, cur2 = 0;
        long long sum2 = 0;
        
        for(auto& [tar1, tar2] : joints) {
            // move cur1 and cur2
            while(cur1 <= tar1) {
                sum1 += nums1[cur1];
                ++cur1;
            }

            while(cur2 <= tar2) {
                sum2 += nums2[cur2];
                ++cur2;
            }

            sum1 = sum2 = max(sum1, sum2) % mod;
        }

        while(cur1 < n1) {
            sum1 += nums1[cur1];
            ++cur1;
        }
        while(cur2 < n2) {
            sum2 += nums2[cur2];
            ++cur2;
        }

        return max(sum1, sum2) % mod;

        // // deal each jolong long
        // long long res = max(
        //     preSum1[joints[0].first],
        //     preSum2[joints[0].second]
        // );
        // // cout << "init res: " << res << endl;
        // // cout << "new jolong long in 1/2: " << joints[0].first << "/" << joints[0].second << endl;

        // for(long long i = 1; i < joints.size(); ++i) {
        //     // if()
        //     res += max(
        //         preSum1[joints[i].first] - preSum1[joints[i-1].first],
        //         preSum2[joints[i].second] - preSum2[joints[i-1].second]
        //     );
        //     // cout << "next Res: " <<res <<endl;
        // }

        // // cout << "last jolong long: " << joints.back().first << "/" << joints.back().second << endl;
        // res += max(
        //     preSum1[n1] - preSum1[joints.back().first],
        //     preSum2[n2] - preSum2[joints.back().second]
        // );

        // return res;
    }
};
```