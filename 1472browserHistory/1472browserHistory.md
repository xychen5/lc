## 1367isSubPath

### 1 题目：
[https://leetcode-cn.com/problems/design-browser-history/](https://leetcode-cn.com/problems/design-browser-history/)

### 2 解题思路：
使用栈模拟存储历史记录，使用一个下表存储当前访问节点。
当清除向前历史，即为清除当前访问节点之后的所有顶点(也就是无法在向前访问)。

```cpp
class BrowserHistory {
public:
    int curStep = -1;
    vector<string> allHis;
    bool fromForward = false;
    BrowserHistory(string homepage) {
        allHis.emplace_back(homepage);
        ++curStep;
    }
    
    void visit(string url) {
        // 移除当前指针之后所有的元素，也就是所谓的清除所有的历史
        allHis.erase(allHis.begin()+ curStep + 1, allHis.end());
        allHis.emplace_back(url);
        curStep = allHis.size() - 1;
    }
    
    string back(int steps) {
        fromForward = false;
        curStep = curStep - steps >= 0 ? curStep - steps : 0;
        return allHis[curStep];
    }
    
    string forward(int steps) {
        fromForward = true;
        curStep = (curStep + steps) >= allHis.size() ? allHis.size()-1 : curStep + steps;
        return allHis[curStep];
    }
};

/**
 * Your BrowserHistory object will be instantiated and called as such:
 * BrowserHistory* obj = new BrowserHistory(homepage);
 * obj->visit(url);
 * string param_2 = obj->back(steps);
 * string param_3 = obj->forward(steps);
 */
```