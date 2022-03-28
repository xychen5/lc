## 0335isSelfCrossing 相交路径

### 1 题目
[https://leetcode-cn.com/problems/self-crossing/](https://leetcode-cn.com/problems/self-crossing/)

### 2 解题思路
- 1 解题思路： 意识到，所有碰撞之和近6次以及以内的步骤有关，然后讨论即可

```cpp
class Solution {
public:

/*               i-2
    case 1 : i-1┌─┐
                └─┼─>i
                 i-3
                 
                    i-2
    case 2 : i-1 ┌────┐
                 └─══>┘i-3
                 i  i-4      (i overlapped i-4)

    case 3 :    i-4
               ┌──┐ 
               │i<┼─┐
            i-3│ i-5│i-1
               └────┘
                i-2

*/

    bool isSelfCrossing(vector<int>& distance) {
        int n = distance.size();
        if(n <= 3) {
            return false;
        }

        int i = 0;
        for(int i = 3; i < n; ++i) {
            // case 1
            if(distance[i] >= distance[i-2] && distance[i-3] >= distance[i-1]) {
                return true;
            }

            // case 2
            if(i >= 4 && distance[i-3] == distance[i-1] && distance[i] + distance[i-4] >= distance[i-2]) {
                return true;
            }

            // case 3
            if(i >= 5 && distance[i-1] + distance[i-5] >= distance[i-3] && distance[i-1] < distance[i-3] && distance[i-2] > distance[i-4] && distance[i] + distance[i-4] >= distance[i-2]) {
                return true;
            }
        }

        return false;

    }
};
```