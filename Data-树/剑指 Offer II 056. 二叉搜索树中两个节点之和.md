## 题目

给定一个二叉搜索树 `root` 和一个目标结果 `k`，如果 BST 中存在两个元素且它们的和等于给定的目标结果，则返回 `true`。

 

**示例 1：**

![img](https://mdpicbed.oss-cn-hongkong.aliyuncs.com/imgs/sum_tree_1.jpg)

```
输入: root = [5,3,6,2,4,null,7], k = 9
输出: true
```

**示例 2：**

![img](https://mdpicbed.oss-cn-hongkong.aliyuncs.com/imgs/sum_tree_2.jpg)

```
输入: root = [5,3,6,2,4,null,7], k = 28
输出: false
```

 

**提示:**

- 二叉树的节点个数的范围是 `[1, 10^4]`.
- `-10^4 <= Node.val <= 10^4`
- `root` 为二叉搜索树
- `-10^5 <= k <= 10^5`



注意：本题与主站 653 题相同： https://leetcode-cn.com/problems/two-sum-iv-input-is-a-bst/



## 题解

假如将这道题中的二叉搜索树替换成排序树组，我们知道，只需要进行简单的夹逼，就能找到解。

然而，对于本题的二叉搜索树，虽然它的结构本身蕴含了顺序，但是我们想进行夹逼，似乎也没那么容易。幸好，我们刚刚做过了另一题《剑指 Offer II 055. 二叉搜索树迭代器》——对二叉搜索树构造一个迭代器。受此启发，如果我们能有一个从小到大遍历二叉搜索树的迭代器，还有一个从大到小的迭代器，不就能进行夹逼了吗？

照着这个思路实现，代码如下：

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
class BSTIterator {
private:
    TreeNode *l, *r;
    stack<TreeNode*> lst, rst;
public:
    BSTIterator(TreeNode* root) {
        l = root;
        r = root;
    }
    
    int bigger_next() {  // 从左向右
        while (l) {
            lst.push(l);
            l = l->left;
        }
        l = lst.top();
        lst.pop();
        int val = l->val;
        l = l->right;
        return val;
    }

    int smaller_next() {  // 从右向左
        while (r) {
            rst.push(r);
            r = r->right;
        }
        r = rst.top();
        rst.pop();
        int val = r->val;
        r = r->left;
        return val;
    }
};
class Solution {
public:
    bool findTarget(TreeNode* root, int k) {
        BSTIterator* it = new BSTIterator(root);
        int left = it->bigger_next(), right = it->smaller_next();
        while (left < right) {  // 双指针夹逼
            if (left + right == k) return true;
            else if (left + right < k) left = it->bigger_next();
            else right = it->smaller_next();
        }
        return false;
    }
};
```

> 就这种代码实现难度，这道题的难度标签居然是“简单”，我只能表示自己真的菜…

