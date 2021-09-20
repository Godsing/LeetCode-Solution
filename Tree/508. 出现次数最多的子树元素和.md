## Problem

Given the root of a tree, you are asked to find the most frequent subtree sum. The subtree sum of a node is defined as the sum of all the node values formed by the subtree rooted at that node (including the node itself). So what is the most frequent subtree sum value? If there is a tie, return all the values with the highest frequency in any order.

**Examples 1**
Input:

```
  5
 /  \
2   -3
```

return [2, -3, 4], since all the values happen only once, return all of them in any order.

**Examples 2**
Input:

```
  5
 /  \
2   -5
```

return [2], since 2 happens twice, however -5 only occur once.

**Note:** You may assume the sum of values in any subtree is in the range of 32-bit signed integer.



## Solution

思路：先用一个 map 保存下来所有 Subtree Sum 的频率，最后再把频率最高的那个/那些 Sum 输出。

```cpp
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
#include <unordered_map>

class Solution {
public:
    int dfs(TreeNode* root, unordered_map<int, int>& mp) {
        if(!root) return 0;
        int lsum = dfs(root->left, mp);
        int rsum = dfs(root->right, mp);
        int sum = root->val + lsum + rsum;
        mp[sum]++;
        return sum;
    }
    vector<int> findFrequentTreeSum(TreeNode* root) {
        vector<int> res;
        if(!root) return res;
        unordered_map<int, int> mp;
        dfs(root, mp);
        int max_cnt = 0;
        for (auto kv : mp) {
            if (kv.second == max_cnt) {
                res.emplace_back(kv.first);
            }
            if (kv.second > max_cnt) {
                max_cnt = kv.second;
                res.clear();
                res.emplace_back(kv.first);
            }
        }
        return res;
    }
};
//Runtime: 8 ms, beats 99.94 % of cpp submissions.
```



## Debug&Learning



