## 0952 最大因数联通分量大小

### 1 题目
[https://leetcode-cn.com/problems/largest-component-size-by-common-factor](https://leetcode-cn.com/problems/largest-component-size-by-common-factor)

### 2 解题思路
个人体悟： 当需要判断两个节点是否位于同一个连通子图时，首选并查集

- 1 普通思路：
  - 1.1 很简单，暴力的去检测两两节点之间的连接性，然后构建并查集，求解最大的分量值即可；
- 2 优化思路：
  - 1 中需要o(n^2)的复杂度去计算结点之间的链接性，我们不去计算节点的连接性，改为计算他们质数因子的连接性
  - 2 对于每个数字提取出质因子列表，然后因为这个数的存在，可以将这些质因子联系起来，将所有数字的质因子计作L
  - 3 而后我们统计每个数字，他对应的属于哪个质因子的联通分量，然后对该联通分量的root计数加1即可，最后找出所有的质因子联通分量最大的计数即可。

```cpp
class Solution {
public:
    class DSU{
    public:
        vector<int> parent;
        vector<int> subTreeSize;
    
        DSU(int n) {
            parent.resize(n);
            subTreeSize.resize(n);
            for(int i = 0; i < n; ++i) {
                parent[i] = i;
                subTreeSize[i] = 1;
            }
        }
    
        int find(int x) {
            while(x != parent[x]) {
                parent[x] = parent[parent[x]];
                x = parent[x];
            }
            return x;
        }
    
        bool unionMerge(int x, int y) {
            int findX = find(x);
            int findY = find(y);
            if(findX != findY) {
                parent[findX] = findY;
                subTreeSize[findY] += subTreeSize[findX];
                return true;
            }
            return false;
        }

        int maxComponentSize() {
            return *max(subTreeSize.begin(), subTreeSize.end());
        }
    };

    int getGreatestCommonDivisor(int x, int y) {
        int res = 0;
        int mod = 0;
        do {
            mod = x % y;
            x = y;
            y = mod;

        } while(mod != 0);
        // cout << y << endl;
        return x;
    }

    int largestComponentSize(vector<int>& nums) {
        int n = nums.size();
        int maxComponentSize = INT_MIN;

        // DSU* dsu = new DSU(n);
        // travel all pairs and construct the dsu, o(n ** 2), too slow
        // for(int i = 0; i < n; ++i) {
        //     for(int j = i; j < n; ++j) {
        //         if(getGreatestCommonDivisor(nums[i], nums[j]) != 1) {
        //             dsu->unionMerge(i, j);
        //         }
        //     }
        // }
        // 
        // return *max_element(dsu->subTreeSize.begin(), dsu->subTreeSize.end());

        // we shall understand the fact that:
        // union: union by edeg, but edge denote two set

        // find a number's prime factors:
        map<int, vector<int>> numberToPrimes;
        for(auto num : nums) {
            vector<int> primes;
            int x = num;
            
            int d = 2;
            while(d * d <= num) {
                if(num % d == 0) {
                    // cull out all d
                    while(num % d == 0) {
                        num = num / d;
                    }
                    primes.emplace_back(d);
                }
                ++d;
            }
            if(num > 1 || primes.empty()) {
                primes.emplace_back(num);
            }
            numberToPrimes[x] = primes;
        }

        // form all the factors and numbers into nodes
        unordered_set<int> factors;
        for(auto& p : numberToPrimes) {
            for(auto& fac : p.second) {
                factors.insert(fac);
            }
        }

        unordered_map<int, int> facToNode;
        int i = 0;
        for(auto fac : factors) {
            facToNode[fac] = i++;
        }

        DSU* dsu = new DSU(factors.size());
        // union those numbers by factors
        for(auto p : numberToPrimes) {
            vector<int> primes = p.second;
            // union a number's all factors, we need union action: primes.size() times
            for(auto prime : primes) {
                // cout << p.first << "->" << prime << endl;
                dsu->unionMerge(facToNode[primes[0]], facToNode[prime]);
            }

        }

        // for each number, find the union root of this number
        // all numbers who are connected will share the same root
        vector<int> cnt(factors.size());
        for(auto p : numberToPrimes) {
            cnt[dsu->find(facToNode[p.second[0]])]++;
        }
        
        return *max_element(cnt.begin(), cnt.end());
        // return *max_element(dsu->subTreeSize.begin(), dsu->subTreeSize.end());
        // return dsu->maxComponentSize();
    }
};
```
