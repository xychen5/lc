## 2030. 含特定字母的最小子序列 smallestSubsequence

### 1 题目：
[https://leetcode-cn.com/problems/smallest-k-length-subsequence-with-occurrences-of-a-letter/](https://leetcode-cn.com/problems/smallest-k-length-subsequence-with-occurrences-of-a-letter/)

### 2 解题思路：
- 1 考虑一个简单化的问题，选出长度为k的最小字典序的字符串，算法如下：
  - 1.1 采用单调栈维护一个递增栈，自然的保持了最小字典序
```cpp
class Solution {
public:
    string smallestSubsequence(string s, int k, char letter, int repetition) {
        // first, using monostack to get the min sub arr whose len = k
        // and check if there are rep's 'letter' in sub arr
        
        vector<int> mono; // abscending chars
        int n = s.size();
        int specialCharCnt = 0;
        int avaliableSpeChar = 0;
        for(auto c : s) {
            avaliableSpeChar += (c == letter);
        }


        for(int i = 0; i < n; ++i) {
            while(!mono.empty() && s[mono.back()] >= s[i] && mono.size() - 1 + n - i >= k) {
                specialCharCnt -= static_cast<int>(s[mono.back()] == letter);
                mono.pop_back();
            }

            mono.emplace_back(i);
            if(s[i] == letter) {
                --avaliableSpeChar;
                ++specialCharCnt;
            }
        }

        string res = "";
        for(auto i : mono){
            res += s[i];
        }

        return res;
    }
};
```
- 2 考虑另一个子问题，需要选出含有rep个特殊字符的子序列，可以使用一个队列存储特殊字符的下标，当队列长度达到rep个，则记为一个子序列
- 3 将两个问题结合起来考虑就是是说：
  - 3.1 在递增栈构造的过程中，要保证当前位置后面剩余的特殊字符加上当前栈内的字符大于等于repetition，否则将不能出栈特殊字符（因为如果出栈则无法满足有repetition个特殊字符的要求
  - 3.2 经过3.1步骤，单调栈内含有我们的答案，但是一定有一些额外的字符存在，那么如下说明从栈内获得答案的方式：
    - 3.2.1 eg: 当aaabbbcccddd为输入，则单调栈为aaabbbcccddd，那么我们想要的结果为在至少有2个b的字符串，那么我们获得最终结果的方式为：**在保证有大于repetition个letter的情况下，从尾部开始删除字符串直到单调栈内剩下k个字符即可**
```
"aaabbbcccddd"
3
"b"
2
```

```cpp
class Solution {
public:
    string smallestSubsequence(string s, int k, char letter, int repetition) {
        // first, using monostack to get the min sub arr whose len = k
        // and check if there are rep's 'letter' in sub arr
                
        clock_t start,end;　　　//定义clock_t变量
        start = clock();  　　　//开始时间

        string mono; // abscending chars
        int n = s.size();
        int specialCharCnt = 0;
        int avaliableSpeChar = 0;
        for(auto &c : s) {
            avaliableSpeChar += (c == letter);
        }


        for(int i = 0; i < n; ++i) {
            while(!mono.empty() && mono.back() > s[i] && mono.size() - 1 + n - i >= k) {
                if(mono.back() == letter) {
                    // when not enough special letter, we do not pop special char
                    if(avaliableSpeChar <= repetition - specialCharCnt) {
                        break;
                    }
                    --specialCharCnt;
                }
                mono.pop_back();
            }

            mono.push_back(s[i]);
            if(s[i] == letter) {
                --avaliableSpeChar;
                ++specialCharCnt;
            }
        }

        start = clock();  　　　//开始时间
        string res = "";
        // eliminate some extra chars reversely
        int delNum = mono.size() - k;
        // cout << "letter Cnt: " << specialCharCnt << endl;
        for(int i = mono.size() - 1; i >= 0; --i){
            // make sure there are more than rep's 'letter'
            if(delNum != 0 ) {
                if(specialCharCnt > repetition) {
                    specialCharCnt -= (mono[i] == letter);
                    --delNum;
                    continue;
                } else {
                    if(mono[i] != letter) {
                        --delNum;
                        continue;
                    }
                }
            }
            // spend: 0.311s
            // res = mono[i] + res; // this spend two much time, ocuppy nearly 100% time! so we change our policy
            // spend: 0.000153s, 1000 times faster!
            res.push_back(mono[i]);
        }

        reverse(res.begin(), res.end());
        end = clock();   //结束时间
        cout<<"time = "<<double(end-start)/CLOCKS_PER_SEC<<"s"<<endl;  //输出
        return res;
    }
};


```

### 3 关于string的+和push_back
如果是一个字符一个字符的话，使用push_back会比+快1000倍！如上代码可以自己尝试统计
```cpp
            // spend: 0.311s
            // res = mono[i] + res; // this spend two much time, ocuppy nearly 100% time! so we change our policy
            // spend: 0.000153s, 1000 times faster!
            res.push_back(mono[i]);
```