## Problem

Given a binary tree, return the *postorder* traversal of its nodes' values.

**Example:**

```
Input: [1,null,2,3]
   1
    \
     2
    /
   3

Output: [3,2,1]
```

**Follow up:** Recursive solution is trivial, could you do it iteratively?



## Solution

由于 vector 在第一个位置 insert 会导致所有元素重新分配内存，效率极低，因此采用逆向的办法：先以类似于先序遍历的办法访问所有节点，再反转得到后序遍历。

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
    vector<int> postorderTraversal(TreeNode* root) {
        vector<int> res;
        if (!root) return res;
        
        stack<TreeNode*> s;
        TreeNode* p = root;
        // 类似于先序遍历，只是先当前结点，再访问右子树，后访问左子树
        while (!s.empty() || p != NULL) {
            if (p != NULL) {
                s.push(p);
                res.emplace_back(p->val);
                p = p->right;
            } else {
                TreeNode* tmp = s.top();
                p = tmp->left;
                s.pop();
            }
        }
        vector<int> new_res(res.rbegin(), res.rend());  // 反转，得到后序遍历
        return new_res;
    }
};
```



## Debug&Learning

[Preorder, Inorder, and Postorder Iteratively Summarization](https://leetcode.com/problems/binary-tree-postorder-traversal/discuss/45551/Preorder-Inorder-and-Postorder-Iteratively-Summarization) 

Here I summarize the iterative implementation for preorder, inorder, and postorder traverse.

### Pre Order Traverse

------

```java
public List<Integer> preorderTraversal(TreeNode root) {
    List<Integer> result = new ArrayList<>();
    Deque<TreeNode> stack = new ArrayDeque<>();
    TreeNode p = root;
    while(!stack.isEmpty() || p != null) {
        if(p != null) {
            stack.push(p);
            result.add(p.val);  // Add before going to children
            p = p.left;
        } else {
            TreeNode node = stack.pop();
            p = node.right;   
        }
    }
    return result;
}
```



### In Order Traverse

------

```java
public List<Integer> inorderTraversal(TreeNode root) {
    List<Integer> result = new ArrayList<>();
    Deque<TreeNode> stack = new ArrayDeque<>();
    TreeNode p = root;
    while(!stack.isEmpty() || p != null) {
        if(p != null) {
            stack.push(p);
            p = p.left;
        } else {
            TreeNode node = stack.pop();
            result.add(node.val);  // Add after all left children
            p = node.right;   
        }
    }
    return result;
}
```



### Post Order Traverse

------

```java
public List<Integer> postorderTraversal(TreeNode root) {
    LinkedList<Integer> result = new LinkedList<>();
    Deque<TreeNode> stack = new ArrayDeque<>();
    TreeNode p = root;
    while(!stack.isEmpty() || p != null) {
        if(p != null) {
            stack.push(p);
            result.addFirst(p.val);  // Reverse the process of preorder
            p = p.right;             // Reverse the process of preorder
        } else {
            TreeNode node = stack.pop();
            p = node.left;           // Reverse the process of preorder
        }
    }
    return result;
}
```