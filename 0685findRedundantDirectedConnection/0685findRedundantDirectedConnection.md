# 0685 冗余链接2

## 1 题目描述
[https://leetcode-cn.com/problems/redundant-connection-ii](https://leetcode-cn.com/problems/redundant-connection-ii)

## 2 解题思路
首先，思考有向图冗余链接的集中情况：
- 1 有环路，所有顶点入度为1，这种情况冗余链接1就能解决
- 2 没有环路，有顶点的入度为2，那么我只需要在并查集形成冗余链接的过程中，找到入度为2的顶点的最后加入的边即可
- 3 有环路，有顶点的入度为2，那我们需要删除的边就很确定了，就是位于环路的而且以入度为2的顶点作为终点的边
