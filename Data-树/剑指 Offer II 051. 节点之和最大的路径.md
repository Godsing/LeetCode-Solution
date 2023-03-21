## 题目

**路径** 被定义为一条从树中任意节点出发，沿父节点-子节点连接，达到任意节点的序列。同一个节点在一条路径序列中 **至多出现一次** 。该路径 **至少包含一个** 节点，且不一定经过根节点。

**路径和** 是路径中各节点值的总和。

给你一个二叉树的根节点 `root` ，返回其 **最大路径和** 。

 

**示例 1：**

![img](https://mdpicbed.oss-cn-hongkong.aliyuncs.com/imgs/exx1.jpg)

```
输入：root = [1,2,3]
输出：6
解释：最优路径是 2 -> 1 -> 3 ，路径和为 2 + 1 + 3 = 6
```

**示例 2：**

![img](https://mdpicbed.oss-cn-hongkong.aliyuncs.com/imgs/exx2.jpg)

```
输入：root = [-10,9,20,null,null,15,7]
输出：42
解释：最优路径是 15 -> 20 -> 7 ，路径和为 15 + 20 + 7 = 42
```

 

**提示：**

- 树中节点数目范围是 `[1, 3 * 104]`
- `-1000 <= Node.val <= 1000`



注意：本题与主站 124 题相同： https://leetcode-cn.com/problems/binary-tree-maximum-path-sum/



来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/jC7MId

## 题解

为了得到整棵树的最大路径和，只需要遍历每一个节点，计算当它作为节点之一时所能达到的最大路径和。

而对于某个节点，要计算当它作为节点之一时的最大路径和，需要知道该节点的左孩子节点的单侧最大路径和。所谓某节点的单侧最大路径和，指的是以该节点作为根节点，向叶子节点单向延伸的所有可能路径中的最大路径和。因此，我们可以定义一个递归函数，它既计算当前节点作为节点之一时所能达到的最大路径和（以更新最终解），也返回当前节点的单侧最大路径和（供上层函数使用）。

总体思路算是一种后序遍历。

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
    int maxPathSum(TreeNode* root) {
        int res = INT_MIN;
        int tmp = dfs(root, res);
        return res;
    }

    int dfs(TreeNode* node, int& res) {
        if (!node) return 0;
        int left_max = max(dfs(node->left, res), 0);
        int right_max = max(dfs(node->right, res), 0);
        res = max(res, left_max + node->val + right_max);
        return max(left_max, right_max) + node->val;
    }
};
```

