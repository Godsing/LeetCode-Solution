## Problem

Given a binary search tree, write a function `kthSmallest` to find the **k**th smallest element in it.

**Note:** 
You may assume k is always valid, 1 ≤ k ≤ BST's total elements.

**Example 1:**

```
Input: root = [3,1,4,null,2], k = 1
   3
  / \
 1   4
  \
   2
Output: 1
```

**Example 2:**

```
Input: root = [5,3,6,2,4,null,null,1], k = 3
       5
      / \
     3   6
    / \
   2   4
  /
 1
Output: 3
```

**Follow up:**
What if the BST is modified (insert/delete operations) often and you need to find the kth smallest frequently? How would you optimize the kthSmallest routine?



## Solution

因为是二叉搜索树，所以先序遍历的过程，就是结点值从小到大的过程。通过非递归进行遍历，访问到第 k 个结点时，直接返回其值。

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
    int kthSmallest(TreeNode* root, int k) {
        int cnt = 0;
        stack<TreeNode*> st;
        TreeNode* p = root;
        //先序遍历的非递归实现
        while (!st.empty() || p != NULL) {
            if (p != NULL) {
                st.push(p);
                p = p->left;
            } else {
                TreeNode* node = st.top();
                cnt++;
                if (cnt == k) return node->val;
                st.pop();
                p = node->right;
            }
        }
    }
};
//Runtime: 15 ms, beats 97.97 % of cpp submissions.
```



## Debug&Learning



