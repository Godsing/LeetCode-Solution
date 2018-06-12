## Problem

Given an integer array with no duplicates. A maximum tree building on this array is defined as follow:

1. The root is the maximum number in the array.
2. The left subtree is the maximum tree constructed from left part subarray divided by the maximum number.
3. The right subtree is the maximum tree constructed from right part subarray divided by the maximum number.

Construct the maximum tree by the given array and output the root node of this tree.

**Example 1:**

```
Input: [3,2,1,6,0,5]
Output: return the tree root node representing the following tree:

      6
    /   \
   3     5
    \    / 
     2  0   
       \
        1
```

**Note:**

1. The size of the given array will be in the range [1,1000].



## Solution

```c++
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
    TreeNode* constructMaximumBinaryTree(vector<int>& nums) {
        return constructor(0, nums.size(), nums);
    }
    TreeNode* constructor(int l, int r, const vector<int>& nums) {
        if (l == r) return nullptr;
        int max_index = FindMax(l, r, nums);
        TreeNode* node = new TreeNode(nums[max_index]);
        node->left = constructor(l, max_index, nums);
        node->right = constructor(max_index+1, r, nums);
        return node;
    }
    int FindMax(int l, int r, const vector<int>& nums) {
        int max_index = l, max_value = nums[l];
        for (int i = l+1; i < r; i++) {
            if (nums[i] > max_value) {
                max_index = i;
                max_value = nums[i];
            }
        }
        return max_index;
    }
};
//Runtime: 63 ms, beats 89.18 % of cpp submissions.
```





## Debug&Learning



