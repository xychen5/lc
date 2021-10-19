#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <limits.h>
#include <numeric>
#include <list>
#include <queue>
#include <unordered_set>
#include <unordered_map>
#include <map>

using namespace std;
class Solution {
public:
    vector<int> findRedundantDirectedConnection(vector<vector<int>>& edges) {
        tree.resize(edges.size() * 2 + 1, -1);
        fathers.resize(edges.size() * 2 + 1, -1);
        subTreeSize.resize(edges.size() * 2 + 1, 1);
        unordered_map<int, int> inDegree; // nodeIdx -> its in degree
        unordered_map<int, int> outDegree; // nodeIdx -> its out degree

        bool notOnlyCycle  = false;                                                                                                  
        int tarNode = -1;
        for(auto& c : edges) {
            fathers[c[0]] = c[1];
            if(inDegree.find(c[1]) == inDegree.end()) {
                inDegree[c[1]] = 1;
            } else {
                inDegree[c[1]] += 1;
                notOnlyCycle = true;
                tarNode = c[1];
            }
        }
        vector<vector<int>> addedTree = vector(0, vector<int>(2, 0));
        
        vector<int> res = edges[0];
        for(auto& c : edges) {
            addedTree.emplace_back(c);
            if(!unionMerge(c[0], c[1], tree)) {
                if(notOnlyCycle) {
                    // merge fail so we get a cycle
                    int cur = c[1];
                    int ed = c[0];
                    if(inDegree[cur] == 2) {
                        res = {ed, cur};
                        return res;
                    }

                    int resNoCyc = 0;
                    int resCyc = 0;
                    bool hasCyc = false;
                    int n = edges.size() * 2 + 1;
                    int tmpCur = cur;
                    while(--n >= 0) {
                        int fa = fathers[tmpCur];
                        if (fa < 0) {
                            break;
                        }
                        if (fa == ed) {
                            hasCyc = true;
                            break;
                        }
                        tmpCur = fa;
                    }

                    
                    if(hasCyc) {
                        // 2出度 有环
                        while(1) {
                            int fa = fathers[cur];
                            if(fa != ed) {
                                if(inDegree[fa] == 2) {
                                    res = {cur, fa};
                                    return res;
                                }
                            } else {
                                
                                res = {cur, fa};
                                return res;
                            }
                            cur = fa;
                        }
                    } else {
                        // 2出度 无环
                        int lastIdx = 0;
                        for(int i = 0; i < addedTree.size(); ++i) {
                            if(inDegree[addedTree[i][1]] == 2 && find(c[0], tree) != -1) {
                                lastIdx = i;
                            }
                        }
                        return addedTree[lastIdx];
                    }
                    
                }
                
                res = c;
                return res;
            }
        }
        return res;
    }
    
    int find(int tar, vector<int>& tree) {
        int curFather = tree[tar];
        if (curFather < 0) { // tar has no father, so he is the root
            tree[tar] = tar;
            return tar;
        }
        if(tar != curFather) {
            // tree[tar] = find(curFather, tree); // compress the data path
            return find(curFather, tree); // compress the data path
        }
        return tree[tar];
    }

    int findFather(int tar, vector<int>& tree) {
        return tree[tar];
    }
    
    
    bool unionMerge(int x, int y, vector<int>& tree) {
        int fx = find(x, tree);
        int fy = find(y, tree);
        if(fx == fy) {
            return false; // x, y are in the same tree, need no merge
        }
        if(subTreeSize[fx] > subTreeSize[fy]){ // merge by rank of the sub Tree
            tree[fy] = fx;
            subTreeSize[fx] += subTreeSize[fy];
        } else {
            tree[fx] = fy;
            subTreeSize[fy] += subTreeSize[fx];
        }
        return true;
    }
    
    vector<int> subTreeSize;
    vector<int> tree;
    vector<int> fathers;
};

int main() {
    // vector<int> nums = {1, 15, 5, 11};
    // vector<int> nums = {1, 3};
    // vector<int> nums = {1, 3};
    // vector<int> nums = {1, 2, 5, 7};
    vector<int> nums = {2, 2, 3, 4};

    vector<vector<int>> nums2d1 = {
        {0, 1, 1, 0}, 
        {0, 0, 0, 0}
    };

    vector<vector<int>> nums2d2 = {
        {1,2},
        {1,3},
        {2,3}
    };

    std::string str = "()(()())()(";

    Solution sl;
    std::cout << sl.findRedundantDirectedConnection(nums2d2) << std::endl;
    
    // std::cout << ios::left << std::setw(20) << "Hello, World!" << std::setw(5) << "a s " << 1 << std::endl;
    return 0;
}