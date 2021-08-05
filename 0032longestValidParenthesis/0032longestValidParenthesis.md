# 0032最长有效字符串

## 1 题目描述
> 给你一个只包含 '(' 和 ')' 的字符串，找出最长有效（格式正确且连续）括号子串的长度。 
>  
>  示例 1： 
> 
>  
> 输入：s = "(()"
> 输出：2
> 解释：最长有效括号子串是 "()"
>  
> 
>  示例 2： 
> 
>  
> 输入：s = ")()())"
> 输出：4
> 解释：最长有效括号子串是 "()()"
>  
> 
>  示例 3： 
> 
>  
> 输入：s = ""
> 输出：0
>  
> 
>  
> 
>  提示： 
> 
>  
>  0 <= s.length <= 3 * 104 
>  s[i] 为 '(' 或 ')' 
>  
>  
>  
>  Related Topics 栈 字符串 动态规划 

## 2 解题思路
主要的思路有2点：

- 1 对于每个无法扩长的子串，他们使用自己的长度去竞争最长子串，那么只要找出每个无法扩长的子串中他们最大的长度即可。
- 2 然后计算有效字符串的长度很显然需要用到栈，每当遇到'('则push，遇到')'则pop，这个思路就可以计算有效子串的长度。

如下代码：
```
        int stIdx, edIdx, maxLen;
        maxLen = stIdx = edIdx = 0; 
        vector<int> lStack;
        if(s.length() <= 1) {
            return 0;
        }

        for(edIdx = stIdx; edIdx < s.length(); ++edIdx) {
            if(s[edIdx] == '(') {
                lStack.emplace_back(edIdx);
            }else {
                if (lStack.size() >= 1) {
                    lStack.pop_back();
                    if(lStack.size() == 0) {
                        maxLen = std::max(maxLen, edIdx - stIdx + 1); // 从stIdx到edIdx刚好匹配，故计算搜索区间长度
                    } else {
                        maxLen = std::max(maxLen, edIdx - lStack.back()); // lStack.back()表示从左到右最右边多出来的'('
                    }
                } else {
                    stIdx = edIdx + 1; // 表明没有'('与当前')'对应，所以移动起始搜索点
                }
            }
        }
```

