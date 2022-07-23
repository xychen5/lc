## 1649createSortedArrCost 通过指令创建有序数组

### 1 题目
[https://leetcode.cn/problems/create-sorted-array-through-instructions/](https://leetcode.cn/problems/create-sorted-array-through-instructions/)

### 2 解题思路
- 1 解题思路:
  - 1.1 其实：考虑问题规模是逐渐增长的，那么首先不考虑增长，只考虑arr数组的最后一个数字的代价？
    - 比如对于 1 4 3 中的这个3，那么不就是考虑：1 4排序后比3小的个数和比3大的个数
    - 这和求逆序对的个数很像，那么我们考虑用二元索引树，
    - 考虑数组：arr 大小为 n 个，将元素的值改成排名
    - 那么我们使用bit，来记录每个元素的出现个数，那么正序的bit，对于bit[i],就意味着排名i以及小于i的所有元素的个数
    - asc[arr[n-1]]的BIT记录的是：当前数组arr[:-1]的小于arr[n-1]的元素出现个数的前缀，也就是小于arr[n-1]的个数，
    - des同理
        // eg:
        // 1 2 3 6 5 4 , when deal 4
        // asc: 1 2 3 4 5 6
        //      1 1 1 0 1 1 => cost on left: 3
        // des: 6 5 4 3 2 1
        //      1 1 0 1 1 1 => cost on right: 2
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