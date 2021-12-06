## 1808 好因子的最大数目

### 1 题目
[https://leetcode-cn.com/problems/maximize-number-of-nice-divisors/](https://leetcode-cn.com/problems/maximize-number-of-nice-divisors/)

### 2 解题思路
- 1 普通思路：
  - 1.1 需要做的是把这个题目解读好，注意使用数学语言，无普通思路
- 2 优化思路：
  - 2.1 题目意思理解： 首先有primeFactors = n个因子，找出最大的好因子个数，那么先用这些个质因数把数字表示出来：(记有m个质因子)
  - 2.2 数字 = f1^k1 * f2^k2 * f3^k3 * f4^k4 ... * ... fm^km ，所以，sum(k1,k2,..,km) <= n，然后要求好因子（需要被f1 * f2 * f3 ... * fm所有质因数的连乘所整除） 个数最多，很显然好因子个数为：k1 * k2 * k3 * ... * km，然而sum(k1,k2,..,km) <= n，所以要想k1 * ... * km最大，必须有sum(k1, ... , km) = n

然后就是证明，怎么拆这个n，才能使乘最大，尽力拆成3，多余的拆成2，但是2的个数不能超过3，因为 2 * 2 * 2 < 3 * 3，然后对于大于4的k，(x-2) * 2 > x，所以任何大于4的都可以拆成更小的

### 快速幂乘
考虑： a3a2a1 ^ b3b2b1的乘法过程

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
