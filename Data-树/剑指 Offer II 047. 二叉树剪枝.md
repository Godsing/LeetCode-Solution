## 题目

给你二叉树的根结点 `root` ，此外树的每个结点的值要么是 `0` ，要么是 `1` 。

返回移除了所有不包含 `1` 的子树的原二叉树。

节点 `node` 的子树为 `node` 本身加上所有 `node` 的后代。

 

**示例 1：**

![img](https://mdpicbed.oss-cn-hongkong.aliyuncs.com/imgs/1028_1.png)

```
输入：root = [1,null,0,0,1]
输出：[1,null,0,null,1]
解释：
只有红色节点满足条件“所有不包含 1 的子树”。 右图为返回的答案。
```

**示例 2：**

![img](https://mdpicbed.oss-cn-hongkong.aliyuncs.com/imgs/1028_2.png)

```
输入：root = [1,0,1,0,0,0,1]
输出：[1,null,1,null,1]
```

**示例 3：**

![img](https://mdpicbed.oss-cn-hongkong.aliyuncs.com/imgs/1028.png)

```
输入：root = [1,1,0,1,1,0,1,0]
输出：[1,1,0,1,1,null,1]
```

 

**提示：**

- 树中节点的数目在范围 `[1, 200]` 内
- `Node.val` 为 `0` 或 `1`



注意：本题与主站 814 题相同：https://leetcode-cn.com/problems/binary-tree-pruning/



## 题解

后序遍历即可。在遍历过程中，将没有孩子的值为 `0` 的节点都去掉，由于是深度优先遍历，所以可以保证“所有值均为`0`”的子树能被完全地移除。

```c++
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    TreeNode* pruneTree(TreeNode* root) {
        if (!root) return nullptr;
        root->left = pruneTree(root->left);
        root->right = pruneTree(root->right);
        if (!root->left && !root->right && root->val == 0) return nullptr;
        else return root;
    }
};
```

