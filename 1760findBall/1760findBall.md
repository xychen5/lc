## 1760findBall

### 1 题目
[https://leetcode-cn.com/problems/walking-robot-simulation/](https://leetcode-cn.com/problems/where-will-the-ball-fall/)

### 2 解题思路

很普通的模拟，
- 1 模拟每个球的反弹就可

```cpp
class Solution {
public:
	struct MovingBall {
		int x = 0;
		int y = 0;
		int heading = 0; // 0->down, 1->left, 2->right
		MovingBall() {};
	};
	// borad 1: \ -1: / {{dx for board: \, dx for board: /, with heading down}, }
	vector<vector<int>> dx = { {0, 0},  {0, 1}, {1, 0} };
	vector<vector<int>> dy = { {1, -1}, {1, 0}, {0, -1} };
	// {{curheading 0 to 2, curheading 1 to 2, nothing}(with board: \),}
	vector<vector<int>> changeHeading = { {2, 2, 0}, {1, 0, 1} };
	vector<int> findBall(vector<vector<int>>& grid) {
		vector<MovingBall> balls(grid[0].size());
		for (int i = 0; i < grid[0].size(); ++i) {
			balls[i].x = 0;
			balls[i].y = i;
			if (grid[0][i] == 1) {
				balls[i].heading = 0;
			}
			else {
				balls[i].heading = 0;
			}
		}

		for (int k = 0; k < 2 * grid.size(); ++k) {
			// move every ball
			for (int i = 0; i < grid[0].size(); ++i) {
				move(balls[i], grid);
			}

		}
		vector<int> res;
		for (int i = 0; i < grid[0].size(); ++i) {
			if (balls[i].x >= grid.size()) {
				res.push_back(balls[i].y);
			}
			else {
				res.push_back(-1);
			}
		}
		return res;

	}

	void move(MovingBall& b, vector<vector<int>>& grid) {
		if (b.x >= grid.size()) { return; }
		int gridType = grid[b.x][b.y];
		if ((0 == b.y && gridType == -1 && b.heading == 0) || \
			(grid[0].size() - 1 == b.y && gridType == 1 && b.heading == 0)) {
			return;
		}
		if (grid[0].size() == 1) return;

		int ifBoard2 = (int)(gridType == -1);
		b.x += dx[b.heading][ifBoard2];
		b.y += dy[b.heading][ifBoard2];
		b.heading = changeHeading[ifBoard2][b.heading];
	}
};
```