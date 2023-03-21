## 题目

完全二叉树是每一层（除最后一层外）都是完全填充（即，节点数达到最大）的，并且所有的节点都尽可能地集中在左侧。

设计一个用完全二叉树初始化的数据结构 `CBTInserter`，它支持以下几种操作：

- `CBTInserter(TreeNode root)` 使用头节点为 `root` 的给定树初始化该数据结构；
- `CBTInserter.insert(int v)` 向树中插入一个新节点，节点类型为 `TreeNode`，值为 `v` 。使树保持完全二叉树的状态，**并返回插入的新节点的父节点的值**；
- `CBTInserter.get_root()` 将返回树的头节点。

 



**示例 1：**

```
输入：inputs = ["CBTInserter","insert","get_root"], inputs = [[[1]],[2],[]]
输出：[null,1,[1,2]]
```

**示例 2：**

```
输入：inputs = ["CBTInserter","insert","insert","get_root"], inputs = [[[1,2,3,4,5,6]],[7],[8],[]]
输出：[null,3,4,[1,2,3,4,5,6,7,8]]
```

 

**提示：**

1. 最初给定的树是完全二叉树，且包含 `1` 到 `1000` 个节点。
2. 每个测试用例最多调用 `CBTInserter.insert` 操作 `10000` 次。
3. 给定节点或插入节点的每个值都在 `0` 到 `5000` 之间。



注意：本题与主站 919 题相同： https://leetcode-cn.com/problems/complete-binary-tree-inserter/



来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/NaqhDT
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。



## 题解

这里有一个比较巧妙的想法：想要实现 `insert` 的时候，返回父节点的值，只需要将那些叶子节点（以及只有一个`left`孩子的节点(如果存在)）用一个队列保存起来。然后在插入的时候，取队列第一个节点作为父节点，插入孩子，然后同时也将该孩子添加到此队列的末尾。父节点如果两个孩子都满了，就从此队列中弹出。最后返回该父节点的值即可。

为了得到上述的队列，需要用另一个队列来进行广度优先遍历。

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
class CBTInserter {
private:
    TreeNode* tree_root;
    deque<TreeNode*> q;  // 用来保存最后两层的叶子节点（先倒数第二层(如果有)，再最后一层）

public:
    CBTInserter(TreeNode* root) {
        tree_root = root;
        deque<TreeNode*> row;
        row.push_back(root);
        while (!row.empty()) {
            TreeNode* node = row.front();
            row.pop_front();
            if (node->left) row.push_back(node->left);
            if (node->right) row.push_back(node->right);
            else q.push_back(node);
        }
    }

    int insert(int v) {
        TreeNode* new_node = new TreeNode(v);
        TreeNode* node = q.front();
        if (node->left) {
            node->right = new_node;
            q.push_back(new_node);
            q.pop_front();
        } else {
            node->left = new_node;
            q.push_back(new_node);
        }
      return node->val;
    }

    TreeNode* get_root() {
        return tree_root;
    }
};

/**
 * Your CBTInserter object will be instantiated and called as such:
 * CBTInserter* obj = new CBTInserter(root);
 * int param_1 = obj->insert(v);
 * TreeNode* param_2 = obj->get_root();
 */
```



学习一下官方解法：总体思路一样，只是在用广度优先遍历得到所需队列 `que` 的时候，并没有借助另一个辅助队列(我代码中的`row`)，而是直接用`que`，只需要稍微修改一下 while 循环的判断条件就可以了。但与此同时，insert 函数中插入左孩子的代码需要挪动一下位置。

```c++
class CBTInserter {
private:
    queue<TreeNode*> que;
    TreeNode* root;
public:
    CBTInserter(TreeNode* root) {
        this->root = root;  // 成员变量与形参同名时的写法
        que.push(root);
        while (que.front()->left != nullptr && que.front()->right != nullptr) {
            que.push(que.front()->left);
            que.push(que.front()->right);
            que.pop();
        }  // 注意，循环结束后，只有一个 left 孩子的节点(如果存在)会在队列 que 的开头，而 left 孩子节点不在队列中
    }
    
    int insert(int v) {
        TreeNode* node = new TreeNode(v);
        TreeNode* fa = que.front();
        if (fa->left == nullptr) {
            fa->left = node;
        }
        else {
            fa->right = node;
            que.push(fa->left);  // 保证了 left 孩子节点在队列中
            que.push(fa->right);
            que.pop();
        }
        return fa->val;
    }
    
    TreeNode* get_root() {
        return this->root;
    }
};

```

作者：master_xue
链接：https://leetcode-cn.com/problems/NaqhDT/solution/jian-zhi-offer-2-mian-shi-ti-43-shu-zhon-hy4v/
来源：力扣（LeetCode）

