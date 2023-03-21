## 题目

给你一棵二叉搜索树的 `root` ，请你 **按中序遍历** 将其重新排列为一棵递增顺序搜索树，使树中最左边的节点成为树的根节点，并且每个节点没有左子节点，只有一个右子节点。

 

**示例 1：**

![img](https://mdpicbed.oss-cn-hongkong.aliyuncs.com/imgs/ex2.jpg)

```
输入：root = [5,3,6,2,4,null,8,1,null,null,null,7,9]
输出：[1,null,2,null,3,null,4,null,5,null,6,null,7,null,8,null,9]
```

**示例 2：**

![img](https://mdpicbed.oss-cn-hongkong.aliyuncs.com/imgs/ex1.jpg)

```
输入：root = [5,1,7]
输出：[1,null,5,null,7]
```

 

**提示：**

- 树中节点数的取值范围是 `[1, 100]`
- `0 <= Node.val <= 1000`



## 题解

方法一：先中序遍历将所有节点保存到 vector 中，再重新组织成递增顺序搜索树。

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
    void inorder(TreeNode* node, vector<TreeNode*>& nodes) {
        if (!node) return ;
        inorder(node->left, nodes);
        nodes.push_back(node);
        inorder(node->right, nodes);
    }
    TreeNode* increasingBST(TreeNode* root) {
        vector<TreeNode*> nodes;
        inorder(root, nodes);
        TreeNode* head = nodes.front();
        for (int i = 0; i < nodes.size() - 1; i++) {
            nodes[i]->left = nullptr;
            nodes[i]->right = nodes[i+1];
        }
        nodes.back()->left = nullptr;
        nodes.back()->right = nullptr;
        return head;
    }
};
```

方法二：直接原地修改。可以不需要借助 dummy 节点，代码如下：

```c++
class Solution {
private:
    TreeNode* head = nullptr;
public:
    TreeNode* increasingBST(TreeNode* root) {
        TreeNode* prev = nullptr;
        inorder(root, prev);
        return head;
    }

    void inorder(TreeNode* node, TreeNode* &prev) {  // 注意，prev 指针需要引用
        if (!node) return ;
        inorder(node->left, prev);
        if (!prev) head = node;  // 没有前一节点，说明当前是第一个节点
        else prev->right = node;  // 需要注意的是："prev->left = nullptr;" 这一行不能放在 else 里
        prev = node;
        prev->left = nullptr;  // 放在这里，才能保证每一个节点的左孩子都置为 nullptr
        inorder(node->right, prev);
    }
};
// 这道题难度标签虽然是“简单”，但如果要用这种方式实现代码，细节上还是有一定难度的，需要特别细心才行
```

