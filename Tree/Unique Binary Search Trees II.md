## Problem

Given an integer *n*, generate all structurally unique **BST's** (binary search trees) that store values 1 ... *n*.

**Example:**

```
Input: 3
Output:
[
  [1,null,3,2],
  [3,2,null,1],
  [3,1,null,null,2],
  [2,1,3],
  [1,null,2,null,3]
]
Explanation:
The above output corresponds to the 5 unique BST's shown below:

   1         3     3      2      1
    \       /     /      / \      \
     3     2     1      1   3      2
    /     /       \                 \
   2     1         2                 3
```



## Solution

递归，思路来自：https://leetcode.com/problems/unique-binary-search-trees-ii/discuss/31494/A-simple-recursive-solution

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
class Solution {
public:
    vector<TreeNode*> generateTrees(int n) {
        auto res = genTrees(1, n);
        if (n == 0) res.clear();
        return res;
    }
    
private:
    vector<TreeNode*> genTrees(int start, int end) {
        vector<TreeNode*> list;
        if (start > end) {
            list.emplace_back(nullptr);
            return list;
        }
        if (start == end) {
            list.emplace_back(new TreeNode(start));
            return list;
        }
        vector<TreeNode*> left_subtrees, right_subtrees;
        for (int i = start; i <= end; i++) {  //每个点作为根节点时，生成所有可能的左右子树
            left_subtrees = genTrees(start, i-1);
            right_subtrees = genTrees(i+1, end);
            //为所有（左、右子树）可能的组合，生成一棵树，并添加到list里
            for (auto left_subtree : left_subtrees){
                for (auto right_subtree : right_subtrees) {
                    TreeNode* root = new TreeNode(i);
                    root->left = left_subtree;
                    root->right = right_subtree;
                    list.emplace_back(root);
                }
            }
        }
        return list;
    }
};
//Runtime: 12 ms, beats 14.31 % of cpp submissions. 速度偏慢
```



## Debug&Learning



