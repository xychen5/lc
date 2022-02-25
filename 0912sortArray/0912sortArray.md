
## 0912sortArray 三种基础排序

### 1 题目：
[https://leetcode-cn.com/problems/sort-an-array/](https://leetcode-cn.com/problems/sort-an-array/)

### 2 解题思路：
- 1 分别详细解释 快速排序，归并排序，堆排序
  - 1.1 快速排序
    - 算法核心：选择一个数字，然后将比他大的都移动到他左边，比他小的都是右边，然后分别对左侧区域和右侧区域递归执行即可
    - 速度和稳定性：在单调情况下达到最坏，为O(n**2)，不稳定的原因，中枢元素会和最后一个比他小的数字交换位置(以此将左侧分为比他小的，右侧比他大的)；
  - 1.2 归并排序
    - 算法核心：切分成左右两部分，然后对于左右两部分分别执行算法本身，知道之剩下2个以及1个元素，返回后合并即可
    - 速度稳定性：速度稳定，元素之间次序稳定
  - 1.3 堆排序：
    - 算法核心：首先建立一个大根堆，之后第i次将大根堆的top移动到nums的nums[n-i]处，而后将nums[0:n-i-1]重新排列成大根堆，一次选出一个最大元素排在末尾，可以看出这里主要代价在于将maxHeapfiy(nums[0:n-i-1])
    - 速度稳定性：速度稳定，元素之间次序不稳定，因为对于7,5,5 你会发现一开始将最后的5移动到了第一个，打乱了次序


```cpp
class Solution {
public:
    vector<int> sortArray(vector<int>& nums) {
        // quick sort, most bad when it is sorted o(n**2), not stable
        // quickSort(0, nums.size() - 1, nums); 

        // merge sort, stable
        // mergeSort(0, nums.size() - 1, nums);

        // heap sort, not stable
        head_sort(0, nums.size() - 1, nums);
        return nums;
    }

    void head_sort(int st, int ed, vector<int>& nums) {
        // init
        buildMaxHeap(nums);

        // everytime select max and put to end and call maxHeapify
        int len = nums.size();
        for(int ed = len - 1; ed >= 0; --ed) {
            swap(st, ed, nums);
            // nums[ed:] is sorted
            maxHeapify(st, ed - 1, nums);
        }
    }

    void buildMaxHeap(vector<int>& nums) {
        // start from the last dad node, till all dad node be the max heap root
        int len = nums.size();
        for(int dad = len / 2 - 1; dad >= 0; --dad) {
            maxHeapify(dad, len - 1, nums);
        }
    }

    void maxHeapify(int st, int ed, vector<int>& nums) {
        if(ed <= st) {
            return;
        }

        while(st <= ed) {
            // cmp the st and its lChild and rChild and decide which side to descend
            int lChild = st * 2 + 1;
            int rChild = st * 2 + 2;
            // cout << "l/r: " << lChild << " " << rChild << endl;
            if(lChild > ed) {
                return;
            } else if(rChild > ed) {
                if(nums[st] < nums[lChild]) {
                    swap(st, lChild, nums);
                }
                return;
            }
            if(nums[st] >= nums[lChild] && nums[st] >= nums[rChild]) {
                return;
            } else {
                if(nums[lChild] > nums[rChild]) {
                    swap(st, lChild, nums);
                    st = lChild;
                } else {
                    swap(st, rChild, nums);
                    st = rChild;
                }
            }
        }
    }

    void mergeSort(int st, int ed, vector<int>& nums) {
        // sort when |st - ed| <= 1
        if(ed - st == 1) {
            if(nums[ed] < nums[st]) {
                swap(ed, st, nums);
            }
            return;
        } else if(ed == st) {
            return;
        }
        int mid = (st + ed) / 2;
        cout << mid << endl;
        mergeSort(st, mid, nums);
        mergeSort(mid + 1, ed, nums);
        
        // merge
        int curL = 0;
        int curR = 0;
        vector<int> tmpL(nums.begin() + st, nums.begin() + mid + 1);
        vector<int> tmpR(nums.begin() + mid + 1, nums.begin() + ed + 1);

        for(int i = st; i <= ed; ++i) {
            if(curL == mid - st + 1) {
                // cout << "using R to fullly fill from " << curR << endl;
                for(; curR < ed - mid; ++curR) {
                    nums[i++] = tmpR[curR];
                }
                break;
            } else if(curR == ed - mid) {
                // cout << "using L to fullly fill from " << curL << endl;
                for(; curL < mid - st + 1; ++curL) {
                    nums[i++] = tmpL[curL];
                }
                break;
            } else if(tmpL[curL] < tmpR[curR]) {
                nums[i] = tmpL[curL++];
                // cout << "using L: " << nums[i] << endl;
            } else {
                nums[i] = tmpR[curR++];
                // cout << "using R: " << nums[i] << endl;
            }
        }
    }

    void quickSort(int st, int ed, vector<int>& nums) {
        if(st >= ed) {
            return;
        }
        
        int newPivot = partition(st, ed, nums);
        quickSort(st, newPivot-1, nums);
        quickSort(newPivot + 1, ed, nums);
    }

    int partition(int st, int ed, vector<int>& nums) {
        // put 'smaller than st' to left, others right
        int r = ed;
        int l = st;
        // st is the first blank place
        int pivot = nums[st];
        while(l < r){
            // r form right to left
            while(r > l && nums[r] > pivot) {
                r--;
            }
            nums[l] = nums[r];

            // l form left to right
            while(l < r && nums[l] <= pivot) {
                l++;
            }
            nums[r] = nums[l];
        }
        nums[l] = pivot;
        return l;
    }

    void swap(int& a, int& b, vector<int>& nums) {
        // cout << "swaping! " << a << " " << b << endl;
        int tmp = nums[a];
        nums[a] = nums[b];
        nums[b] = tmp;
    }

    void print(vector<int>& nums) {
        for(auto& i : nums) {
            cout << i << " ";
        }
        cout << "\n";
    }
};
```