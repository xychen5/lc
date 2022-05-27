## 0854kSimilaritySwap 相似度为k的字符串

### 1 题目
[https://leetcode.cn/problems/k-similar-strings/](https://leetcode.cn/problems/k-similar-strings/)

### 2 解题思路
- 1 解题思路：
  - 1.1 bfs，每一层，考虑交换i j
  - 1.2 肯定是要剪枝：
    - 1.2.1 剪枝1：首先我们考虑交换ij能够一次性做完两个字符串的位置
    - 1.2.1 剪枝2：对于没有“一次性做完两个字符串”的情况，我们找到第一个不相等的位置i，然后剩下所有位置j从i到n-1，考虑：curSrc[i] == tar[j] || curSrc[j] == tar[i]，也就是至少能够做完一个字符串位置，我们才加入到bfs队列中，然后直接进行下一层的bfs，那么为什么可以找到第一个不相等的i，就不用管后面的i呢？因为很明显的一个道理，一次交换之只能一个字符串，那么后面的i肯定会在更深层次的bfs完成

```cpp
class Solution {
public:

    int kSimilarity(string s1, string s2) {
        if(s1 == s2) {
            return 0;
        }   

        int depth = 1;
        string src = std::move(s1);
        string tar = std::move(s2);
        queue<string> curLevel;
        unordered_map<string, int> vis;
        curLevel.push(src);
        vis[src] = 0;

        int n = src.size();

        int i, j, curDep;
        while(!curLevel.empty()) {
            auto curSrc = curLevel.front();
            curDep = vis[curSrc];
            curLevel.pop();

            // exactly two pos swap
            bool swapTwo = false;
            for( i = 0; i < n; ++i) {
                if(curSrc[i] == tar[i]) {
                    continue;
                }
                for(j = i+1; j < n; ++j) {
                    if(curSrc[i] == tar[j] && curSrc[j] == tar[i]) {
                        swap(curSrc[i], curSrc[j]);
                        if(curSrc == tar) {
                            return curDep + 1;
                        }
                        if(vis.end() == vis.find(curSrc)) {
                            curLevel.push(curSrc);
                            vis.insert({curSrc, curDep + 1});
                            // vis[curSrc] = curDep + 1;
                        }
                        swapTwo = true;
                        swap(curSrc[j], curSrc[i]);
                    }
                }
            }
            if(swapTwo) {
                continue;
            }
            i = 0;
            for(i = 0; i < n; ++i) {
                if(curSrc[i] == tar[i]) {
                    continue;
                }
                for(j = i + 1; j < n; ++j) {
                    if(curSrc[i] == tar[j] || curSrc[j] == tar[i]) {

                        swap(curSrc[i], curSrc[j]);
                        if(curSrc == tar) {
                            return curDep + 1;
                        }
                        if(vis.end() == vis.find(curSrc)) {
                            curLevel.push(curSrc);
                            vis.insert({curSrc, curDep + 1});

                            // vis[curSrc] = curDep + 1;
                        }
                        swap(curSrc[j], curSrc[i]);
                    }
                }
                break;
            }
        }
        return -1;
    }

};

```