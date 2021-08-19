## 0466 等差数列划分

### 1 题目：
[https://leetcode-cn.com/problems/arithmetic-slices-ii-subsequence/submissions/](https://leetcode-cn.com/problems/arithmetic-slices-ii-subsequence/submissions/)

### 2 解题思路：
#### 2.1 个人解法
- 1 求出所有的等差数列，对每一个等差数列求解出其能够划分的子数列的长度。
  - 1.1 首先O(n^2)两两数字凑对，然后用map记录出现的公差，对于每一个公差使用O(n)搜索一遍得到等差数列
  - 1.2 对于上述每一个求出来的等差数列，等差数列划分出子数列的个数是较为容易求解的：见如下代码：
    - 主要思路就是：划分出子数列可以看成抽稀的过程，即为： 每k个数字中取1个，这就是主要思路，计算如下：遍历k需要O(n)复杂度(可以使用map存对应的等差数列的长度对应的值来加速)
```cpp
class Solution {
public:
    int numberOfArithmeticSlices(vector<int>& nums) {
        if(nums.size() <= 2) {
            return 0;
        }
        // sort
        // sort(nums.begin(), nums.end(), [](int a, int b){return a < b;});

        // get all arithemetic slices length and sum it
        int curItv = 0;
        bool interupted = true;
        int curLen = 0;
        int res = 0;
        for(int i = 1; i < nums.size(); ++i) {
            if(interupted) {
                curItv = nums[i] - nums[i-1];
                curLen = 2;
                interupted = false;
                continue;
            }
            if(nums[i] - nums[i-1] == curItv) {
                curLen++;
            } else {
                --i;
                res += subSlicesNum(curLen, curItv);
                interupted = true;
            }
        }
        res += subSlicesNum(curLen, curItv);
        return res;
    }

    int subSlicesNum(int n, int itv) {
        if(n <= 2) {
            return 0;
        }
        int res = 0;
        if(itv != 0) {
            res = ((n-2) * (n-1))/2;
            // 
            int k = 1; // the delete one part length
            while( n % (k+1) + n / (k+1) >= 3) { // the vector after del must have at least 3 elem
                int redundantNum = n % (k+1);

                if( n % (k+1) == 0) { // the ori length became: ori = ori / (k+1)
                    res += ((n/(k+1)-2) * (n/(k+1)-1))/2 * (k+1);
                } 
                else if( n % (k+1) == 1) {
                    // res += ((n/(k+1)-1) * (n/(k+1)-0))/2 - 1; // with redundant one
                    res += n/(k+1) + 1 - 2; // with redundant one
                    res += (k+1) * ((n/(k+1)-2) * (n/(k+1)-1))/2;
                } 
                else {
                    res += (n%(k+1)) * ((n/(k+1)-1) * (n/(k+1)-0))/2; // left part
		    //                         here: the del part no covered by the left part
                    res += (n/(k+1) >= 3) ? (k+1 - n%(k+1)) * ((n/(k+1)-2) * (n/(k+1)-1))/2 : 0;
                }
                ++k;
            }
        } else {
            res = 1;
            for(int i = 1; i < n - 2; ++i) {
                res += frac(n) / frac(n-i) / frac(i);
            }
        }
        return res;
    }

    // n!
    int frac(int n) {
        int res = 1;
        while(n!=0) {
            res *= n;
            --n;
        }
        return res;
    }
};
```

#### 2.2 官方解法
- 2 动态规划：
  - 2.1 对于输入数据num[], 使用 vector<unordered_map<long long, int>> m(n), 对于所有的0 <= j <= i, m[i][d] 记录了： (对于每一个d = nums[i] - nums[j]，以num[i]作为结尾，公差为d的数列的) 长度 - 1，于是可以使用：
  - 2.2 于是对于每一个j以及其于当前数nums[i]对应的d可以用： ans += m[j][d]来代表以num[i]为结尾的等差数列的划分方法。
  - 2.3 然后很容易想到： m[i][d] = m[j][d] + 1; (见2.1, 因为m本身记录的是对于某个i，其所有可能的公差的数组的长度减去1)

