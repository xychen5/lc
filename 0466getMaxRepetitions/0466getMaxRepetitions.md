## 0466getMaxRepetitions 获取最大重叠数

### 1 题目
[https://leetcode-cn.com/problems/count-the-repetitions/](https://leetcode-cn.com/problems/count-the-repetitions/)

### 2 解题思路
- 1 找到字符串s2在s1中的循环节，然后做即可，最关键的是，循环节寻找方法：
  - 1.1 记录每次进入新的s1中第一个匹配的s2中的字符在s2的下标，当该下标开始重复，则说明找到循环节

```cpp
class Solution {
public:
    int getMaxRepetitions(string s1, int n1, string s2, int n2) {
        // find how many s1 can construct a s2
        string matchStr;
        int len1 = s1.length();
        int len2 = s2.length();
        int p1 = 0, p2 = 0;
        vector<int> firstMatchInS1;
        vector<int> lastMatchInS2;
        int headS1UnUsedCnt = 0;
        map<int, int> posToS1Repeat;
        map<int, int> posToMatchStrPos;
        bool firstMatch = true;
        int s1Cnt = 0;
        int nS1EqualKS2 = -1;
        int kS2 = -1;
        while(s1Cnt < n1) {
            if(s1[p1] == s2[p2]) {
                if(firstMatch) {
                    if(posToS1Repeat.find(p2) == posToS1Repeat.end()) {
                        posToS1Repeat[p2] = s1Cnt;
                        posToMatchStrPos[p2] = matchStr.size();
                    } else {
                        headS1UnUsedCnt = posToS1Repeat[p2];
                        nS1EqualKS2 = s1Cnt - posToS1Repeat[p2];
                        kS2 = (matchStr.size() - posToMatchStrPos[p2]) / len2;
                        break;
                    }
                    firstMatchInS1.push_back(p2);
                    firstMatch = false;
                }
                matchStr.push_back(s1[p1]);
                p2 = (p2 + 1) % len2;
            }
            p1 = (p1 + 1) % len1;
            if(p1 == 0) {
                ++s1Cnt;
                firstMatch = true;
            }
        }



        // recycle node found
        int entirePart = 0; 
        // cout << nS1EqualKS2 << "/" << kS2 << endl;
        // entire:

        double repeatS2InS1 =  (double)(n1 - headS1UnUsedCnt) / nS1EqualKS2 * kS2;
        entirePart += floor(repeatS2InS1 / n2);
        int leftS1Cnt = n1 - round((double)entirePart * n2 * 1.0/ kS2 * nS1EqualKS2);
		// partly: 
        repeatS2InS1 = 0;
        
        // no recycle node found!
        if(nS1EqualKS2 == -1) {
            repeatS2InS1 = 0;
            leftS1Cnt = n1;
            entirePart = 0;

        }

        p1 = 0, p2 = 0;
        matchStr.clear();
        while(leftS1Cnt != 0) {
            if(s1[p1] == s2[p2]) {
                matchStr.push_back(s1[p1]);
                p2 = (p2 + 1) % len2;
            }
            p1 = (p1 + 1) % len1;
            if(p1 == 0) {
                --leftS1Cnt;
            }
        }
        repeatS2InS1 += matchStr.length() / len2;
        
        return (int)repeatS2InS1 / n2 + entirePart;
    }
};
```