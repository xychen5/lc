## 2014 重复 K 次的最长子序列

### 1 题目
[https://leetcode-cn.com/problems/largest-color-value-in-a-directed-graph/](https://leetcode-cn.com/problems/largest-color-value-in-a-directed-graph/)

### 2 解题思路
- 1 自己的思路： 首先查出来哪些字符有k个，压入dq中，若一个字符有2k个，则压入两次(代表最终结果里可以有两个该字符)，而后将其逆序排序
- 2 那么最后的结果一定是从dq中来，我们可以枚举dq的所有子序列即可(枚举子序列需要按照逆序字典序，这样找到的第一个子序列即为我们的目标)
- 关键: 如何获得逆序子序列呢？ 
  - 1.1 最简单的想法，从dq(已经是最大的子序列了)中选择长度为n(7到1)的子序列，获取每个子序列(由于父序列为最大序列，那么子序列也一定是最大序列)所有的全排列
  - 1.2 但是这样做有问题，比如 有fd，fe两个子序列，那么优先对于fe去看其所有的排列是否满足要求，然而若是ef满足要求，那么其检测顺序在fd前面，
  - 这样就没有满足按照逆序字典序的方法去检测，于是对于长度为n的子序列，需要先生成所有的全排列，然后按照字典序排序，
```cpp
<省略>
    string tmp;
    vector<string> res;
    chooseN2(dq, len, 0, res, tmp);

    // 构建出同len的所有permutaion，然后sort然后再来以此比较
    vector<string> sameLenStr;
    for(int i = 0; i < res.size(); ++i) {
        do {

            // string tmp4 = "";
            // for(char& c : res[i]) tmp4 += c;
            // std::cout << "-d4 " << tmp4 << " with n = " << len <<std::endl;
            sameLenStr.push_back(res[i]);
        }while(prev_permutation(res[i].begin(), res[i].end()));
    }
    sort(sameLenStr.begin(), sameLenStr.end(), [](string a, string b){return a > b;})
<省略>

    void chooseN2(vector<char>& dq, int n, int st, vector<string>& res, string& tmpRes) {
        if(n == 0) {
            res.push_back(tmpRes);
            // std::cout << "-d2 " << tmpRes << " with n = " << tmpRes.size() <<std::endl;
            return;
        }
        for(int i = st; i < dq.size() - n + 1; ++i) {
            tmpRes.push_back(dq[i]);
            chooseN2(dq, n - 1, i + 1, res, tmpRes);
            tmpRes.pop_back();
        }
    }
```
> 所以根本原因在于这个chooseN2函数对于 fde的一个dq，当n=2的时候，只能生成 fd,fe,de
> 的序列，于是我们对这个函数进行改进，让他能够生成按照字典序排序所有长度为2的全排列
```cpp
    void chooseN3(vector<char>& dq, int n, priority_queue<string, vector<string>, std::function<bool(string, string)>>& res, string& tmpRes) {
        if(n == 0) {
            res.push(tmpRes);
            // std::cout << "-d2 " << tmpRes << " with n = " << tmpRes.size() <<std::endl;
            return;
        }
        for(int i = 0; i < dq.size(); ++i) {
            tmpRes.push_back(dq[i]);
            vector<char> tmpDq;
            tmpDq.insert(tmpDq.end(), dq.begin(), dq.begin() + i);
            tmpDq.insert(tmpDq.end(), dq.begin() + i + 1, dq.end());
            chooseN3(tmpDq, n - 1, res, tmpRes);
            tmpRes.pop_back();
        }
    }
```
最后中实现总代码：
```cpp
class Solution {
public:
    string longestSubsequenceRepeatedK(string s, int k) {
        // 找出大于等于k的字符记作kSet
        int n = s.size();

        vector<int> cnt(26, 0);
        vector<char> dq;
        for(int i = 0; i < n; ++i) {
            int charNo = s[i]-'a';
            ++cnt[charNo];
            if(cnt[charNo] % k == 0) {
                dq.push_back(s[i]);
            }
        }

        // 将kSet按照逆序字典序排序
        auto cmp = [](char a, char b) {return a > b;};
        sort(dq.begin(), dq.end(), cmp);

            // string tmp = "";
            // for(char& c : dq) tmp += c;
            // std::cout << "-d1 " << tmp << std::endl;


        // 找到第一个满足的最大长度为dq的字典序逆序的子序列的排列即为结果
        // 从子模式串的最大长度dq.size()一直遍历到1
        for(int len = dq.size(); len >= 1; --len) {
            // vector<char> tmp;
            // vector<vector<char>> res;
            // chooseN(dq, len, 0, res, tmp);
            // string tmp;
            // vector<string> res;
            // chooseN2(dq, len, 0, res, tmp);

            // // 构建出同len的所有permutaion，然后sort然后再来以此比较
            // vector<string> sameLenStr;
            // for(int i = 0; i < res.size(); ++i) {
            //     do {

            //         // string tmp4 = "";
            //         // for(char& c : res[i]) tmp4 += c;
            //         // std::cout << "-d4 " << tmp4 << " with n = " << len <<std::endl;
            //         sameLenStr.push_back(res[i]);
            //     }while(prev_permutation(res[i].begin(), res[i].end()));
            // }
            // sort(sameLenStr.begin(), sameLenStr.end(), [](string a, string b){return a > b;});
                        // for(int subIdx = 0; subIdx < sameLenStr.size(); ++subIdx) {
            //     // do {
            //     // 构造seq*k
            //     string tmpDq;
            //     for(int i = 0; i < k; ++i) {
            //         tmpDq += sameLenStr[subIdx];
            //     }
// 
            //     // string tmp3 = "";
            //     // for(char& c : tmpDq) tmp3 += c;
            //     // std::cout << "-d3 " << tmp3 << " with n = " << tmpDq.size() <<std::endl;
// 
            //     // 判断构造的seq*k是否存在于s中
            //     int tmpIdx = 0;
            //     int realIdx = 0;
            //     int cnt = 0;
            //     for(; tmpIdx < tmpDq.size(); ++tmpIdx) {
            //         for(; realIdx < n; ++realIdx) {
            //             if(s[realIdx] == tmpDq[tmpIdx]) {
            //                 ++cnt;
            //                 ++realIdx;
            //                 break;
            //             }
            //         }
            //     }
// 
            //     
            //     if(cnt == tmpDq.size()) {
            //         return sameLenStr[subIdx];
            //     }
            //         
            // }
            string tmp;
            std::function<bool(string, string)> cmp = [](string a, string b)->bool{return a < b;};
            priority_queue<string, vector<string>, std::function<bool(string, string)>> sameLenStr(cmp);
            chooseN3(dq, len, sameLenStr, tmp);
 
            // 看该子序列是否可以
            while(!sameLenStr.empty()) {
                string curStr = sameLenStr.top();
                sameLenStr.pop();
                string tmpDq;
                for(int i = 0; i < k; ++i) {
                    tmpDq += curStr;
                }

                // string tmp3 = "";
                // for(char& c : tmpDq) tmp3 += c;
                // if(curStr.size() <= 10)std::cout << "-d3 " << curStr << " with n = " << tmpDq.size() <<std::endl;

                // 判断构造的seq*k是否存在于s中
                int tmpIdx = 0;
                int realIdx = 0;
                int cnt = 0;
                for(; tmpIdx < tmpDq.size(); ++tmpIdx) {
                    for(; realIdx < n; ++realIdx) {
                        if(s[realIdx] == tmpDq[tmpIdx]) {
                            ++cnt;
                            ++realIdx;
                            break;
                        }
                    }
                }

                if(cnt == tmpDq.size()) {
                    return curStr;
                }
            }

        }
        return "";
    }

    void chooseN2(vector<char>& dq, int n, int st, vector<string>& res, string& tmpRes) {
        if(n == 0) {
            res.push_back(tmpRes);
            // std::cout << "-d2 " << tmpRes << " with n = " << tmpRes.size() <<std::endl;
            return;
        }
        for(int i = st; i < dq.size() - n + 1; ++i) {
            tmpRes.push_back(dq[i]);
            chooseN2(dq, n - 1, i + 1, res, tmpRes);
            tmpRes.pop_back();
        }
    }

    void chooseN3(vector<char>& dq, int n, priority_queue<string, vector<string>, std::function<bool(string, string)>>& res, string& tmpRes) {
        if(n == 0) {
            res.push(tmpRes);
            // std::cout << "-d2 " << tmpRes << " with n = " << tmpRes.size() <<std::endl;
            return;
        }
        for(int i = 0; i < dq.size(); ++i) {
            tmpRes.push_back(dq[i]);
            vector<char> tmpDq;
            tmpDq.insert(tmpDq.end(), dq.begin(), dq.begin() + i);
            tmpDq.insert(tmpDq.end(), dq.begin() + i + 1, dq.end());
            chooseN3(tmpDq, n - 1, res, tmpRes);
            tmpRes.pop_back();
        }
    }
  
};
```


### 3 全排列实现
首先需要明白：
- 1 一个排列，其优先交换靠右的位置的数字来获得下一个排列，比如1 2 3，他下一个必定是交换2 3,1不会参与其中，
- 2 意识到一个排列，左侧属于高位，打个比方，若全排列对应的都有一个数字表示该排列的大小，那么左侧值越大，那么排列越大

```sh   
ref: https://blog.51cto.com/u_4925054/884291
全排列（非递归求顺序）算法  
1、建立位置数组，即对位置进行排列，排列成功后转换为元素的排列；  
2、按如下算法求全排列：  
    设P是1～n(位置编号)的一个全排列：p = p1,p2...pn = p1,p2...pj-1,pj,pj+1...pk-1,pk,pk+1...pn  
    (1)从排列的尾部开始，找出第一个比右边位置编号小的索引j（j从首部开始计算），即j = max{i | pi < pi+1}  
    (2)在pj的右边的位置编号中，找出最后一个比pj大的位置编号索引k，即 k = max{i | pi > pj} (k > j)
    (3)交换pj与pk  
    (4)再将pj+1...pk-1,pk,pk+1...pn翻转得到排列p' = p1,p2...pj-1,pj,pn...pk+1,pk,pk-1...pj+1  
    (5)p'便是排列p的下一个排列  

例如：  
24310是位置编号0～4的一个排列，求它下一个排列的步骤如下：  
(1)从右至左找出排列中第一个比右边数字小的数字2；  
(2)在该数字后的数字中找出比2大的数中编号最大的3；  
(3)将2与3交换得到34210；  
(4)将原来2（当前3）后面的所有数字翻转，即翻转4210，得30124；  
(5)求得24310的下一个排列为30124。  
```

这里给出官方的可能实现：
5 6 1 2 3 4的下一个排列是： 6 1 2 3 4 5
```cpp
// 比如求 6 5 4 2 3 1的下一个排列
template<class BidirIt>
bool next_permutation(BidirIt first, BidirIt last)
{
    if (first == last) return false;
    BidirIt i = last;
    if (first == --i) return false;
 
    while (true) {
        BidirIt i1, i2;
 
        i1 = i;
        if (*--i < *i1) { // i = prev(i1), 找到了一个 i < i1的(2 < 3)相邻对子
            i2 = last;
            while (!(*i < *--i2)) // 从i的右边找最后一个比i大的数字
                ;
            std::iter_swap(i, i2); // 交换 i和i2 (2,3),变成6 5 4 3 2 1
            std::reverse(i1, last); // 从i1(原始数据中的3处)到最后，得到 6 5 4 3 1 2
            return true;
        }
        if (i == first) { // 若果找不到两个相邻的数，使得右边<左边,则认为是最大排列
            std::reverse(first, last);
            return false;
        }
    }
}
```


