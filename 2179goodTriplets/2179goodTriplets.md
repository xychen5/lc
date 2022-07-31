## 2179goodTriplets 好三元组的个数

### 1 题目
[https://leetcode.cn/problems/count-good-triplets-in-an-array/](https://leetcode.cn/problems/count-good-triplets-in-an-array/)

### 2 解题思路
- 1 解题思路:
  - 首先：
    - 将nums1用map[nums[i]] = i;这么一个映射映射到0，1，2，到n-1，同理nums2也用map映射，那么结果会发生改变吗？
    - 不会，因为对于nums1和nums2的相同的元素，他们会映射到同一个值，且在数组的位置没发生改变，所以最后不会影响结果
  - 那么，由于nums1已经严格升序，问题就简单了，对于nums2每一个y，是不是仅仅需要从找到左侧比他小，右侧比他大的个数就行了？这不就和求逆序对的个数一样吗?
  - 我们采用二元索引树，或者叫树状数组来解决，记为tree
    - 那么对于nums2[i]，我们如何计算左侧比他小的呢？
    - 由于tree记录的是前缀和，所以我们每次更新都是用tree.update(nums2[i], 1)，意思是，tree背后记录每一个元素出现个数的那个数组里，nums2[i]出现了1次，那么求nums2[i+1]左侧有多少个数字出现，不就是：tree.getSum(i+1)就可以了吗（不包含下标i+1求的前缀和），因为tree背后记录的是，直到下标i（包含i），出现了的值都被标记为1（这反映了左侧），所以求比他小的值的个数，不就是求tree背后的标记数组下标从0到nums2[i+1]的元素（记录了这些数字出现的次数）前缀和（不包含nums2[i+1]本身）
  
    
```cpp
class Solution {
public:
    static int constexpr BIG_INT = 1'000'000'007;
    class BIT {
    public:
        vector<int> tree;
        BIT(int size) : tree(size + 1, 0){};

        // will affect all of its son, because BIT used to get preFixSum
        void update(int idx, int delta) {
            idx += 1;
            while(idx < tree.size()) {
                tree[idx] += delta;
                // update its son
                idx += (idx & (-idx));
            }
        }

        int query(int idx) {
            idx += 1;
            int sum = 0;
            while(idx >= 1) {
                sum += tree[idx];
                idx -= (idx & (-idx)); // to its parent
            }
            return sum;
        }
    };


    // we only care about the relevant big or small between elements
    int createSortedArray(vector<int>& instructions) {
        vector<int> ori(instructions);
        sort(ori.begin(), ori.end());
        
        unordered_map<int, int> numToNo;
        int curNo = 0;
        int curNum = ori[0];
        numToNo[ori[0]] = curNo;
        for(int i = 1; i < ori.size(); ++i) {
            if(curNum < ori[i]) {
                numToNo[ori[i]] = curNo + 1;
                ++curNo;
                curNum = ori[i];
            }
        }

        // update the instructions
        for(auto& i : instructions) {
            i = numToNo[i];
        }

        // a ascending and descending counter, using binary idx tree for the prefixSum 
        // use their prefixSum to record the left and right cost
        // eg:
        // 1 2 3 6 5 4 , when deal 4
        // asc: 1 2 3 4 5 6
        //      1 1 1 0 1 1 => cost on left: 3
        // des: 6 5 4 3 2 1
        //      1 1 0 1 1 1 => cost on right: 2
        int n = curNo + 1;
        BIT asc(n);
        BIT des(n);
        // cout << "size: " << n << endl;
        int finCos = 0;
        for(auto i : instructions) {
            asc.update(i, 1);
            // cout << "asc: " << i << endl;
            // cout << "des: " << n - i - 1 << endl;
            des.update(n - i - 1, 1);
            // cout << "sum: asc/des: " << asc.query(i - 1) << "/" << des.query(n - i - 2) << endl;
            finCos += min(asc.query(i - 1), des.query(n - i - 2));
            finCos %= BIG_INT;
        }
        return finCos;
    }
};
```