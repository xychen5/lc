## 0699fallingSquares 掉落的方块

### 1 题目：
[https://leetcode-cn.com/problems/falling-squares/](https://leetcode-cn.com/problems/falling-squares/)

### 2 解题思路：
- 1 普通思路：使用一维数组模拟每个位置方块高度，复杂度为o(N^2)，由于N很大，所以会超时
- 2 优化：使用坐标压缩，将所有方块的边界存储在2000以内（因为一共就1000个方块），然后更新高度就按照2000以内去更新即可
```cpp
class Solution {
public:
    vector<int> fallingSquares(vector<vector<int>>& positions) {
        // coordinate compression
        set<int, std::less<int>> coords;
        for(vector<int>& coord : positions) {
            coords.insert(coord[0]);
            coords.insert(coord[0] + coord[1] - 1);
        }

        unordered_map<int, int> borderToIdx;
        int t = 0;
        for(auto& i : coords) {
            borderToIdx[i] = t++;
        }

        // cal heights
        vector<int> heights(t);
        vector<int> res;
        int curHeightest = INT_MIN;
        for(vector<int>& square : positions) {
            int l = borderToIdx[square[0]];
            int r = borderToIdx[square[0] + square[1] - 1];
            int h = square[1];
            int updatedHeight = update(l, r, h, heights);
            curHeightest = max(curHeightest, updatedHeight);
            res.emplace_back(curHeightest);
        }
        return res;
    }

    // update and return updated height of [l, r]
    int update(int l, int r, int h, vector<int>& heights) {
        int oldHeight = INT_MIN;
        for(int i = l; i <= r; ++i) {
            oldHeight = max(oldHeight, heights[i]);
        }
        int newHeight = INT_MIN;
        for(int i = l; i <= r; ++i) {
            heights[i] = oldHeight + h;
        }
        return oldHeight + h;
    } 
};
```