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
    vector<int> findRedundantConnection(vector<vector<int>>& edges) {
        tree.resize(edges.size() * 2 + 1, -1);
        subTreeSize.resize(edges.size() * 2 + 1, 1);
        
        vector<int> res;
        for(auto& c : edges) {
            if(!unionMerge(c[0], c[1], tree)) {
                res = c;
                break;
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
            tree[tar] = find(curFather, tree); // compress the data path
        }
        return tree[tar];
    }
    
    
    bool unionMerge(int x, int y, vector<int>& tree) {
        int fx = find(x, tree);
        int fy = find(y, tree);
        if(fx == fy) {
            return false; // x, y are in the same tree, need no merge
        }
        if(subTreeSize[fx] >= subTreeSize[fy]){ // merge by rank of the sub Tree
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

    std::string str = "()(()())()(";

    Solution sl;
    std::cout << sl.triangleNumber(nums) << std::endl;
    
    // std::cout << ios::left << std::setw(20) << "Hello, World!" << std::setw(5) << "a s " << 1 << std::endl;
    return 0;
}