## 0381randomizedCollection o1删除添加随机获取

### 1 题目
[https://leetcode-cn.com/problems/insert-delete-getrandom-o1-duplicates-allowed/](https://leetcode-cn.com/problems/insert-delete-getrandom-o1-duplicates-allowed/)

### 2 解题思路
- 1 解题思路： 首先需要o1随机获取，就知道必须用数组存，那么添加可以直接在末尾添加，删除呢？数组删除很麻烦，那怎么办？我们把末覆盖到要删除的地方，然后将最后一个有效元素的标记向0方向移动一下就完成了删除。
  - 1.1 具体的小问题：在上面的删除过程中，比如数组里为 0 1 2 3 3，现在删除1，我们会把数组覆盖为： 0 3 2 3 3，然后最后有效指向第2个3，那么问题来了，3的下标需要从原来的{3,4}改成{1, 3}，于是我们首先对{3,4}加入将要下标4处的3移动到目的地的下标1，然后在移除4即可，对删除的1，将其下标集合从{1}变成{}即可
  - 1.2 为何先加入，在移除？比如 对1，首先insert,然后rm，然后insert,那么1的下标集合变换应为：{0}, {}, {0}, 我们会发现，对1 rm的时候，我们会发现，移除的1和要交换的位置是同一个数字！ 首先因为移除1，那么1的下标从{0}变成{}，然后因为将0处位置的1交换到0处位置，我们如果先移除，在加入，会对{}做移除操作，然后加入一个0最终变成{0}，导致失败

```cpp
class RandomizedCollection {
public:
    vector<int> nums;
    int curLen = 0;
    unordered_map<int, multiset<int>> numToIndices;
    RandomizedCollection() {
        nums.resize(200000, 0);
    }
    
    bool insert(int val) {
        nums[curLen++] = val;
        if(numToIndices.count(val) == 0) {
            numToIndices[val] = {curLen - 1};
        } else {
            numToIndices[val].insert(curLen - 1);
        }
        
        return numToIndices[val].size() == 1;
    }
    
    bool remove(int val) {
        if(numToIndices.count(val) != 0 && numToIndices[val].size() != 0) {
            int rmIdx = *(numToIndices[val].begin());
            numToIndices[val].erase(rmIdx);
            nums[rmIdx] = nums[curLen - 1];
            numToIndices[nums[curLen - 1]].insert(rmIdx); // avoid rmIdx == curLen - 1
            numToIndices[nums[curLen - 1]].erase(curLen - 1);
            curLen--;
            
            return true;
        }
        return false;
    }
    
    int getRandom() {
        int st = 0;
        int ed = curLen;
        int randIdx = rand() % (ed - st) + st;
        return nums[randIdx];
    }
};

/**
 * Your RandomizedCollection object will be instantiated and called as such:
 * RandomizedCollection* obj = new RandomizedCollection();
 * bool param_1 = obj->insert(val);
 * bool param_2 = obj->remove(val);
 * int param_3 = obj->getRandom();
 */
```