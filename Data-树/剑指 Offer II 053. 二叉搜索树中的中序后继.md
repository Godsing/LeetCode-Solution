## 题目

给定一棵二叉搜索树和其中的一个节点 p ，找到该节点在树中的中序后继。如果节点没有中序后继，请返回 null 。

节点 p 的后继是值比 p.val 大的节点中键值最小的节点，即按中序遍历的顺序节点 p 的下一个节点。

 

**示例 1：**

![img](https://mdpicbed.oss-cn-hongkong.aliyuncs.com/imgs/285_example_1.PNG)

```
输入：root = [2,1,3], p = 1
输出：2
解释：这里 1 的中序后继是 2。请注意 p 和返回值都应是 TreeNode 类型。
```

**示例 2：**

![img](https://mdpicbed.oss-cn-hongkong.aliyuncs.com/imgs/285_example_2.PNG)

```
输入：root = [5,3,6,2,4,null,null,1], p = 6
输出：null
解释：因为给出的节点没有中序后继，所以答案就返回 null 了。
```



**提示：**

- 树中节点的数目在范围 [1, $10^4$] 内。
- $-10^5$ <= Node.val <= $10^5$
- 树中各节点的值均保证唯一。



注意：本题与主站 285 题（会员题）相同： https://leetcode-cn.com/problems/inorder-successor-in-bst/

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/P5rCT8



## 题解

这一题，有略微的技巧性，需要充分利用二叉搜索树的结构。具体来说，思路如下：

- 从根节点开始遍历；
- 如果当前节点的值大于节点 p 的值，那么当前节点可能恰好是中序后继（更新一下结果），也可能中序后继比当前节点的值小，所以，只需要试着往左子树继续搜索；（如果真正的中继后续在左子树里，那么一定会被找到）
- 如果当前节点的值小于等于节点 p 的值，那么中序后继肯定在右边，所以，只需要试着往右子树继续搜索；

当遍历结束时，我们也就找到了中序后继。时间复杂度是 $O(depth(BST))$ ，即二叉搜索树的最大深度。

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
    TreeNode* inorderSuccessor(TreeNode* root, TreeNode* p) {
        TreeNode* node = root;
        TreeNode* res = nullptr;
        while (node) {
            if (node->val > p->val) {
                res = node;
                node = node->left;
            } else {
                node = node->right;
            }
        }
        return res;
    }
};
```

