## 0726atomCnt 原子的数量

### 1 题目
[https://leetcode-cn.com/problems/number-of-atoms/](https://leetcode-cn.com/problems/number-of-atoms/)

### 2 解题思路
- 1 解题思路：建树，从叶子节点到根节点计算，如下例子：
  - 1.1 Ag((N2)4Cu(OH)3)5，建立的树为：
  - 1.2 对于这个树，最关键的是，我们每次找到最外层的括号，采用栈法，当左边括号栈为空的时候，意味着最外层括号，递归建树即可，建好如下
  - 1.3 计算就从孩子节点开始计算就行
            1
          / |
         A  5
          / | \
         4  Cu  3
         |      |
         N2     OH 

```cpp
class Solution {
public:
    map<string, int, std::less<string>> res;

    struct TreeNode {
    public:
        int time;
        string str;
        bool isLeaf = false;
        map<string ,int, std::less<string>> res;
        TreeNode* father;
        vector<TreeNode*> sons;
        TreeNode(int t, string str, bool isLeaf, TreeNode* f):time(t), str(str), isLeaf(isLeaf), father(f), sons(0) {}
    };
    
    vector<TreeNode*> leaves;
    string countOfAtoms(string formula) {
        TreeNode* root = new TreeNode(1, "", false, nullptr);
        buildTree(root, formula);

        // cal from leaves
        for(auto l : leaves) {
            // get Times
            long long time = 1;
            auto f = l->father;
            while(f != nullptr) {
                time *= f->time;
                f = f->father;
            }
            dealNoBracket(l->str, time);
        }

        string ret("");
        for(auto& p : res) {
            if(1 == p.second) {
                ret += p.first;
            } else {
                ret += p.first + to_string(p.second);
            }
        }
        return ret;
    }

    void buildTree(TreeNode* root, string formula) {
        auto pos1 = formula.find_first_of('(');
        if(pos1 == string::npos) {
            TreeNode* leaf = new TreeNode(1, formula, true, root);
            leaves.push_back(leaf);
            // cout << "final leaf: " << formula << endl;
            return;
        }

        // build the tree
        if(pos1 != 0) {
            TreeNode* leaf = new TreeNode(1, formula.substr(0, pos1), true, root);
            leaves.push_back(leaf);
        }
        vector<int> brackets{static_cast<int>(pos1)};
        int st = pos1 + 1;
        while(st < formula.size()) {
            if(formula[st] == '(') {
                brackets.push_back(st);
                // cout << "push left: " <<st << endl;
            } else if(')' == formula[st]) {
                
                int lastLB = brackets.back();
                // cout << "pop right: " << lastLB << endl;
                brackets.pop_back();
                
                // only dive to next when the substr is the most outside bracket pair
                if(0 == brackets.size()) {
                    // cout << "cur mostout : " << st << endl;
                   size_t timeEndPos = st + 1;
                    while(timeEndPos < formula.size() && formula[timeEndPos] >= '0' && formula[timeEndPos] <= '9') {
                        ++timeEndPos;
                    }
                    
                    int nextTime;
                    if(timeEndPos == st + 1) {
                        nextTime = 1;
                    } else {
                        nextTime = atoi(formula.substr(st + 1, timeEndPos - st - 1).c_str());
                    }

                    TreeNode* nextRoot = new TreeNode(nextTime, "", false, root);
                    // cout << "push timeNode: " << formula.substr(lastLB + 1, st - lastLB - 1) << " with time = " << nextTime << endl;
                    buildTree(nextRoot, formula.substr(lastLB + 1, st - lastLB - 1));
                    // cout << "build " << formula.substr(lastLB + 1, st - lastLB - 1) << " done!" << endl;

                    st = timeEndPos;
                    if(st == formula.size()) break;
                    // try To find next most outside bracket pair
                    // cout << "the left strign: "  << formula.substr(st) << endl;
                    pos1 = formula.substr(st).find_first_of('(');
                    if(string::npos == pos1) {
                        TreeNode* leaf = new TreeNode(1, formula.substr(st), true, root);
                        leaves.push_back(leaf);
                        break;
                    } else {
                        pos1 += st;
                        // cout << "next ( found at: " << pos1 << " st: " << st << endl;
                        if(pos1 != st) {
                            TreeNode* leaf = new TreeNode(1, formula.substr(st, pos1 - st), true, root);
                            leaves.push_back(leaf);

                        } 
                        st = pos1;
                        continue;
                    }
                }
            }
            ++st;
        }
    }

    void dealNoBracket(string str, int times) {
        int st = 0;
        map<string, int> nameCnt;
        while(st < str.size()) {
            size_t nameEndPos = st + 1;
            while(nameEndPos < str.size() && str[nameEndPos] >= 'a' && str[nameEndPos] <= 'z') {
                ++nameEndPos;
            }
            string name = str.substr(st, nameEndPos - st);
            size_t timeEndPos = nameEndPos;
            while(timeEndPos < str.size() && str[timeEndPos] >= '0' && str[timeEndPos] <= '9') {
                ++timeEndPos;
            }

            int time;
            if(timeEndPos == nameEndPos) {
                time = 1;
            } else {
                time = atoi(str.substr(nameEndPos, timeEndPos - nameEndPos).c_str());
            }
            
            if(0 != nameCnt.count(name)) {
                nameCnt[name] += time;
            } else {
                nameCnt[name] = time;
            }
            st = timeEndPos;
        }

        for(auto& p : nameCnt) {
            string name = p.first;
            int cnt = p.second;
            if(0 != res.count(p.first)) {
                res[name] += times * cnt;
            } else {
                res[name] = times * cnt;
            }
        }
    }
};

```