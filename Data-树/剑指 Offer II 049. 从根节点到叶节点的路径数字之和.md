## 题目

给你一个二叉树的根节点 `root` ，树中每个节点都存放有一个 `0` 到 `9` 之间的数字。

每条从根节点到叶节点的路径都代表一个数字：

- 例如，从根节点到叶节点的路径 `1 -> 2 -> 3` 表示数字 `123` 。

计算从根节点到叶节点生成的 **所有数字之和** 。

**叶节点** 是指没有子节点的节点。

 

**示例 1：**

![img](https://mdpicbed.oss-cn-hongkong.aliyuncs.com/imgs/num2tree.jpg)

```
输入：root = [1,2,3]
输出：25
解释：
从根到叶子节点路径 1->2 代表数字 12
从根到叶子节点路径 1->3 代表数字 13
因此，数字总和 = 12 + 13 = 25
```

**示例 2：**

![img](https://mdpicbed.oss-cn-hongkong.aliyuncs.com/imgs/num1tree.jpg)

```
输入：root = [4,9,0,5,1]
输出：1026
解释：
从根到叶子节点路径 4->9->5 代表数字 495
从根到叶子节点路径 4->9->1 代表数字 491
从根到叶子节点路径 4->0 代表数字 40
因此，数字总和 = 495 + 491 + 40 = 1026
```

 

**提示：**

- 树中节点的数目在范围 `[1, 1000]` 内
- `0 <= Node.val <= 9`
- 树的深度不超过 `10`



注意：本题与主站 129 题相同： https://leetcode-cn.com/problems/sum-root-to-leaf-numbers/



## 题解

回溯法。或者说，类似于先序遍历+后序遍历，因为需要在遍历左右孩子之前，将当前节点的值更新到路径里，且在从当前节点返回时，将当前节点的值从路径中再次剔除。

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
    int sumNumbers(TreeNode* root) {
        int res = 0;
        int tmp = 0;  //保存某个路径的值
        dfs(root, tmp, res);
        return res;
    }
    void dfs(TreeNode* root, int& tmp, int& res) {
        if (!root->left && !root->right) {
            res += tmp*10 + root->val;  // 在每个叶子节点，将当前路径的值累加起来
            return ;
        }
        tmp = tmp*10 + root->val;
        if (root->left) dfs(root->left, tmp, res);
        if (root->right) dfs(root->right, tmp, res);
        tmp /= 10;
    }
};
```

