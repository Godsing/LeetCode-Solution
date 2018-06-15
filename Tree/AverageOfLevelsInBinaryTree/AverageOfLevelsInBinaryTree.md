## Problem

Given a non-empty binary tree, return the average value of the nodes on each level in the form of an array.

**Example 1:**

```
Input:
    3
   / \
  9  20
    /  \
   15   7
Output: [3, 14.5, 11]
Explanation:
The average value of nodes on level 0 is 3,  on level 1 is 14.5, and on level 2 is 11. Hence return [3, 14.5, 11].
```

**Note:**

1. The range of node's value is in the range of 32-bit signed integer.



## Solution

我的思路：

在每一层的最后面插入一个空指针，通过空指针来判断一层的结束并求平均值。

每遇到一个空指针，弹出后，如果队列不为空，说明还有下一层，而且下一层的结点均已push进入队列，所以直接在队列末尾插入一个空指针，用来标识下一层的结束。

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
    vector<double> averageOfLevels(TreeNode* root) {
        vector<double> res;
        queue<TreeNode*> q;
        TreeNode* tmp;
        double level_sum = 0, level_num = 0;
        q.push(root);
        q.push(nullptr);
        while (!q.empty()) {
            if (!q.front()) {
                res.emplace_back(level_sum / level_num);
                level_sum = 0;
                level_num = 0;
                q.pop();
                // if (q.front()) cout << "True" << endl; 
                // 如果队列 q 为空，q.front()仍然返回 Undefined Behaviour，所以此时 if (q.front()) 居然是 "True"，不能用之代替 if (!q.empty())（被这个坑惨了，找了好久原因）.
                if (!q.empty()) q.push(nullptr);
                continue;
            }
            tmp = q.front();
            level_sum += tmp->val;
            level_num++;
            if (tmp->left) q.push(tmp->left);
            if (tmp->right) q.push(tmp->right);
            q.pop();
        }
        return res;
    }
};
//Runtime: 18 ms, beats 83.42 % of cpp submissions.
```

**[Java BFS Solution](https://leetcode.com/problems/average-of-levels-in-binary-tree/discuss/105107/Java-BFS-Solution)**

在 Discuss 板块看到一个很聪明的办法，不用加空指针。因为从第一层开始，每一层结束的时候，剩下的队列大小就是下一层的结点个数，假设为n。那么接下来就计算着n个结点的平均值就可以了，然后把n更新为下一层的结点个数，如此循环下去。

Classic bfs problem. At each level, compute the average since you already know the size of the level.

```java
public List<Double> averageOfLevels(TreeNode root) {
    List<Double> result = new ArrayList<>();
    Queue<TreeNode> q = new LinkedList<>();
    
    if(root == null) return result;
    q.add(root);
    while(!q.isEmpty()) {
        int n = q.size();
        double sum = 0.0;
        for(int i = 0; i < n; i++) {
            TreeNode node = q.poll();
            sum += node.val;
            if(node.left != null) q.offer(node.left);
            if(node.right != null) q.offer(node.right);
        }
        result.add(sum / n);
    }
    return result;
}
```



## Debug&Learning



