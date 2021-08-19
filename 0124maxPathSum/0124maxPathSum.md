## 0123买卖股票最佳时机

### 1 题目：
[https://leetcode-cn.com/problems/best-time-to-buy-and-sell-stock-iii/](https://leetcode-cn.com/problems/best-time-to-buy-and-sell-stock-iii/)

### 2 解题思路：


### 2.1 我能想到的思路，复杂度O(N^2)
主要想法就是：
- 1 从每个叶子节点出发进行dfs，对每一个路径采用O(N)算法来获取最大子序和。
```cpp
for(every leafNode of the binary tree):
    start dfs from curleafNode:
        using bellowing func to store each "dfs search path"(which mean from the curleafNode
	to another dfs leaf node):
	{
		void findMaxPathSum(std::priority_queue<int>& res, int maxSum, int lastSum, TreeNode* curNode) {
		// when lastSum + curNode->val > curNode->val, we shall always accept the new coming in value 
		lastSum = std::max(lastSum + curNode->val, curNode->val);
		// maxSum will record the path's history max Sum
		maxSum = std::max(maxSum, lastSum);    
		if( !curNode->left && !curNode->right) {
		res.push(maxSum);
		return;    
		}
		return;
		}
	}
```

