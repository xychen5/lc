## 0321 拼接最大数

### 1 题目
[https://leetcode-cn.com/problems/longest-duplicate-substring/](https://leetcode-cn.com/problems/longest-duplicate-substring/)

### 2 解题思路
- 1 首先分解问题：
  - 1.1 从长度为m和n(假设m <= n)中的字符串里选出k个，然后这个字串要求最大，遍历的思路：
    - 1.2 首先一共要选k个，自然想到从m和n中各挑选几个？那就是遍历了，m中的挑选长度的起点为： max(0, k - n)，最少一个不挑，然后从m中挑的个数身下还有k - m个一定能够从n中挑出，所以起点是从0到k-n，(为什么区最大值？因为当n，m均大于k的时候，k-n为负数)，挑选终点：自然是k，或者没有那么多可以调k个，则挑m个，则min(k, m)
    - 1.3 那么已经知道所有从m,n中挑选出k个字符串的方法，那么对于每一个方法，如何获取最大字符串呢？**其实就是分别从该方法的m和n串中各选出他们的最大字串，然后合并即可**，于是问题转化为：从m中如何选出某个长度记为l的最大字串？
      - 1.3.1 我们考虑一个使用单调递减栈，因为它的栈顶总是当前字符串最大的值，然后后面都是递减的，这正是我们需要的，比如 9 1 2 5 8 3选择3个的时候，使用单调栈可以直接获得9,8,3，但是有个问题，比如从 9 1 2 5 8，单调栈遍历完则为9 5,这3个没选够，所以何时停止从单调栈里弹出呢？遍历位置以及后面剩余的元素刚好够挑选长度的时候，就不再弹出了（即使单调栈内的元素已经不单调了）
    - 1.4 在下一个问题，对于一个挑选方法，m中挑选l个，n中挑选k-l个，分别得到一个最大字串，如何合并成最终字串呢？
      - 1.4.1 其实很简单，两个字符串分别维护一个head叫ha，hb吧，若ha比hb大，那么就把ha的值压入最终结果，直到ha < hb，同理移动b即可，但是需要考虑ha == hb的情况，直接比较ha,hb对应的尾串即可，参考如下测试样例即可：
```cpp
eg1: 
[2,5,6,4,4,0]
[7,3,8,0,6,5,7,6,2]
15

eg2:
[6,7]
[6,0,4]
5
```
``` cpp
class Solution {
public:

    string getMaxConcat(vector<int>& longVec, vector<int>& shortVec, int lenInLonger, int lenInShorter) {
        string monoLong, monoShort;

        // choose biggest lenInLonger's subArr from  longer vec
        for(int i = 0; i < longVec.size(); ++i) {
            while(monoLong.size() > 0 && monoLong.back() - '0' < longVec[i] && monoLong.size() + longVec.size() - i > lenInLonger) {
                // cout << "pop_long: " << monoLong.back() << " monoLong's std len: " << lenInLonger << " curback: " << monoLong.back() << endl;
                monoLong.pop_back();
            }
            if(monoLong.size() < lenInLonger) {
                // cout << "push_long: in " << static_cast<char>(longVec[i] + '0') << endl;
                monoLong.push_back(static_cast<char>(longVec[i] + '0'));
            }
        }
        for(int i = 0; i < shortVec.size(); ++i) {
            // while(monoLong.back() < longVec[i] && monoLong.size() <= lenInLonger && monoLong.size() + longVec.size() - i + 1 < lenInLonger) {
            while(!monoShort.empty() && monoShort.back() - '0' < shortVec[i] && monoShort.size() + shortVec.size() - i > lenInShorter) {
                // cout << "pop_short: " << monoShort.back() << " monoLong's std len: " << lenInShorter << " curback: " << monoShort.back() << endl;
                monoShort.pop_back();
            }
            if(monoShort.size() < lenInShorter) {
                // cout << "push_short: in " << static_cast<char>(longVec[i] + '0') << endl;
                monoShort.push_back(static_cast<char>(shortVec[i] + '0'));
            }
        }

        int j = 0;
        // merger the two biggest substr,
        string finalRes = "";
        // cout << "longMax and shortMax str: " << monoLong << " " << monoShort << endl;
        for(int i = 0; i < monoShort.size(); ++i) {
            while(j < monoLong.size() && monoLong[j] > monoShort[i]) {
                finalRes.push_back(monoLong[j++]);
            }
            // decided whether to use long str or short when the char compared is true
            if(monoLong[j] == monoShort[i]) {
                if(monoLong.substr(j) > monoShort.substr(i)) {
                    finalRes.push_back(monoLong[j++]);
                    i--;
                    continue;
                }
            }
            finalRes.push_back(monoShort[i]);
        }
        finalRes += monoLong.substr(j);
        // cout << "finalRes string is: " << finalRes << endl;
        return finalRes;
    }

    vector<int> maxNumber(vector<int>& nums1, vector<int>& nums2, int k) {
        int m = nums1.size();
        int n = nums2.size();
        // cout << "m/n" << m << " " << n << endl;

        // let k split into nums1 and nums2
        string maxStr(k, '0');
        if(m <= n) {
            for(int lenInShorter = max(0, k - n); lenInShorter <= min(m, k); ++lenInShorter) {
                int lenInLonger = k - lenInShorter;
                // cout << "lenInLong/short" << lenInLonger << " " << lenInShorter << endl;
                string curMax = getMaxConcat(nums2, nums1, lenInLonger, lenInShorter);
                maxStr = maxStr > curMax ? maxStr : curMax;
            }
        } else {
            for(int lenInShorter = max(0, k - m); lenInShorter <= min(n, k); ++lenInShorter) {
                int lenInLonger = k - lenInShorter;
                string curMax = getMaxConcat(nums1, nums2, lenInLonger, lenInShorter);
                maxStr = maxStr > curMax ? maxStr : curMax;
            }
        }

        vector<int> res;
        for(auto& c : maxStr) {
            res.emplace_back(c - '0');
        }
        return res;
    }
};
```