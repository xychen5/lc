
## 0895maxFreqStack 最大频率栈

### 1 题目：
[https://leetcode-cn.com/problems/maximum-frequency-stack/](https://leetcode-cn.com/problems/maximum-frequency-stack/)

### 2 解题思路：map/hash栈
- 1 参考官方思路的扫描线：[https://leetcode-cn.com/problems/maximum-frequency-stack/solution/zui-da-pin-lu-zhan-by-leetcode/](https://leetcode-cn.com/problems/maximum-frequency-stack/solution/zui-da-pin-lu-zhan-by-leetcode/)
- 2 总结过程：
  - 2.1 首先用map维持每一个变量的频率
    - 2.1.1 维持方法： push中对应的key加一，pop对应的key减一
  - 2.2 如何获得当前最大频率？
    - 2.2.1 在每个变量push和pop的时候我们可以获得对应的key的频率，那么所有的key的频率变动都是在push和pop执行完成之后，那么只需要用一个变量maxFreq维持最大频率即可
  - 2.3 知道最大频率，如何获得当前最大频率的变量？
    - 2.3.1 使用map<频率，频率对应的数的集合>来记录即可，然后用2.2中使用maxFreq获取最大频率对应的数字的集合，那如何从这个集合中获取在栈顶的数据呢？map<频率，频率对应的数的集合>中 **频率对应的数的集合** 使用stack去存就好了，因为stack的栈顶总是存着最新来的数据
  - 2.4 一个实例： 3，3，3都是push，那么在频率为1，2，3的栈中，很自然的都有一个3，自然体现在哪里呢？现在pop一下，频率为3对应的stack为空，然后最大频率变为2，然后2里面同样是3
```cpp
class FreqStack {
public:
    int opNum;
    map<int, int> opNumMap;
    map<int, int> freqMap;
    map<int, vector<int>*> groupByFreq;
    int maxFreq;
    FreqStack() {

    }
    
    void push(int val) {
        // cout << "pushing st: with max freq: " << maxFreq << endl;
        freqMap[val]++;
        if(groupByFreq[freqMap[val]] == nullptr) {
            groupByFreq[freqMap[val]] = new vector<int>();
        }
        groupByFreq[freqMap[val]]->emplace_back(val);
        maxFreq = max(maxFreq, freqMap[val]);
        // cout << "pushing done: " << val << "with maxFreq: " << maxFreq << endl;
    }

    int pop() {
        // cout << "pop st with maxFreq: " << maxFreq << endl;
        // find biggest frequency and most newly element to rm
        int popRes = groupByFreq[maxFreq]->back();
        groupByFreq[maxFreq]->pop_back();
        if(groupByFreq[maxFreq]->size() == 0) {
            delete groupByFreq[maxFreq];
            groupByFreq[maxFreq] = nullptr;
            --maxFreq;
        }
        // cout << "pop ed" << popRes << " with maxFreq: " << maxFreq << endl;
        freqMap[popRes]--;
        return popRes;
    }
};

/**
 * Your FreqStack object will be instantiated and called as such:
 * FreqStack* obj = new FreqStack();
 * obj->push(val);
 * int param_2 = obj->pop();
 */
```