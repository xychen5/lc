## 0462minMove2 最少移动步数2（让所有数相等）

### 1 题目
[https://leetcode.cn/problems/minimum-moves-to-equal-array-elements-ii/](https://leetcode.cn/problems/minimum-moves-to-equal-array-elements-ii/)

### 2 解题思路
- 1 解题思路：
  - 1.1 首先容易想到，结果必然是，所有数看齐中位数即可
  - 1.2 问题转换为找到中位数 -> 最简单： 排序即可
  - 1.3 findKBig? : 使用快排，每次能够减少一半搜索范围，只要找到中位数即可
  - 1.4 最关键的partition介绍：
    - 1.4.1 最开始的想法： 
      - A: nums[st, ed]，随机找一个数，为了方便，我们把目标数组移到头部
      - B: l = st+1, r = ed,遍历l
      - C: nums[l]l比目标大，将其和ed交换，进入下一个循环，否则直接l++进入下一个循环
      - D: 最后，由于l == r退出循环，但是我们不知道最后一个l和r谁动了，如果l动了，那么nums[l] >= tar，否则nums[l] <= tar,那么我们考虑其中nums[l] >= tar，也就是最后是l++的情况，最后需要把我们一开始放在最前面的nums[st]放到nums[l-1]的位置，因为nums[st+1 : l-1]中的所有数都 <= nums[st]，所以用小半部分的最后一个数和tar也就是nums[st]交换即可
   - 1.4.2 更加简单的paritition:
    - A: nums[st, ed]，随机找一个数，为了方便，我们把目标数组移到头部
    - 考虑：nums[cursor]始终存贮的是游标，cursor = st + 1,(代码中千万别直接用st代表最终的结果，最后cursor为比tar大的第一个数字的小标，然后st的下标的位置存的就是tar，全程不参与交换)
    - 那么：for(i = st + 1 : ed) {
    -    若 nums[i]比游标小，交换nums[cursor] 和 nums[i] // 也就是i位置，变成了游 ~~标，然后游标右边所有数都比游标小，然后++cur
    - }
    - 最关键的是什么： 理解cursor的含义： nums[1:cursor - 1]存储了所有比tar要小的值，第一个位置st存储了tar，最后把它和cursor-1的位置进行交换即可

```cpp
class Solution {
public:

    void swap(int& a, int& b) {
        int tmp = a;
        a = b;
        b = tmp;
    }

    int findKBig(vector<int>& nums, int k, int st, int ed) {
        if(st == ed) {
            return nums[st];
        }
        int mid = randomPartition(nums, st, ed);
        if(mid < k - 1) {
            if(ed > mid) {
                return findKBig(nums, k, mid + 1, ed);
            }
        } else if(mid > k - 1) {
            if(st < mid) {
                return findKBig(nums, k, st, mid - 1);
            }
        }
        return nums[k - 1];
    }

    void quickSort(vector<int>& nums, int st, int ed) {
        if(st == ed) {
            return ;
        }

        int mid = randomPartition2(nums, st, ed);

        // cout << " ->>>>> " << mid << endl;
        if(st < mid) {
            quickSort(nums, st, mid - 1);
        }
        if(ed > mid) {
            quickSort(nums, mid + 1, ed);
        }
    }


    int randomPartition2(vector<int>& nums, int st, int ed){        
        int mid = rand() % (ed - st + 1) + st;
        swap(nums[st], nums[mid]);
        
        int tar = nums[st];
        int cur = st+1;

        for(int i = st + 1; i <= ed; ++i) {
            if(nums[i] <= tar) {
                swap(nums[i], nums[cur]);
                ++cur;
            }
        }
        swap(nums[st], nums[cur-1]);
        
        // nums[st] = tar;
        return cur-1;
    }

    int randomPartition(vector<int>& nums, int st, int ed) {
        // cout << "st/ed: " << st << " " << ed << endl;
        int mid = rand() % (ed - st + 1) + st;
        swap(nums[st], nums[mid]);
        
        // swap grater right
        int tar = nums[st];

        int l = st + 1;
        int r = ed;

        while(l < r) {
            if(nums[l] > tar) {
                swap(nums[r], nums[l]);
                --r;
            } else {
                ++l;
            }
        }
        // print(nums, oldSt, oldEd);
        
        if(nums[l] < tar) {
            swap(nums[st], nums[l]);
            return l;
        } else {
            swap(nums[st], nums[l-1]);
            return l-1;
        }
        
        return st;
    }

    int minMoves2(vector<int>& nums) {
        // sort nums:
        // quickSort(nums, 0, nums.size() - 1);
        // print(nums, 0, nums.size() - 1);

        // find mid nums:
        int n = nums.size();
        int mid = n / 2;
        int tar = findKBig(nums, mid + 1, 0, n-1);
        // cout << tar << endl;

        int steps = 0;
        for(auto num : nums) {
            steps += abs(tar - num);
        }
        return steps;
    }

    void print(vector<int>& nums, int st, int ed) {
        for(int i = st; i <= ed; ++i) {
            cout << " " << nums[i];
        }cout << "\n";
    }
};
```