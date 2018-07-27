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
//java
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

#### Approach #1 Using Depth First Search [Accepted]

**Algorithm**

One of the methods to solve the given problem is to make use of Depth First Search. In DFS, we try to exhaust each branch of the given tree during the tree traversal before moving onto the next branch.

To make use of DFS to solve the given problem, we make use of two lists countcount and resres. Here, count[i]count[i]refers to the total number of nodes found at the i^{th}ith level(counting from root at level 0) till now, and res[i]res[i]refers to the sum of the nodes at the i^{th}ith level encountered till now during the Depth First Search.

We make use of a function `average(t, i, res, count)`, which is used to fill the resres and countcount array if we start the DFS from the node tt at the i^{th}ith level in the given tree. We start by making the function call `average(root, 0, res, count)`. After this, we do the following at every step:

1. Add the value of the current node to the resres(or sumsum) at the index corresponding to the current level. Also, increment the countcount at the index corresponding to the current level.
2. Call the same function, `average`, with the left and the right child of the current node. Also, update the current level used in making the function call.
3. Repeat the above steps till all the nodes in the given tree have been considered once.
4. Populate the averages in the resultant array to be returned.

The following animation illustrates the process.

【java 版本】

```java
/**
 * Definition for a binary tree node.
 * public class TreeNode {
 *     int val;
 *     TreeNode left;
 *     TreeNode right;
 *     TreeNode(int x) { val = x; }
 * }
 */
public class Solution {
    public List < Double > averageOfLevels(TreeNode root) {
        List < Integer > count = new ArrayList < > ();
        List < Double > res = new ArrayList < > ();
        average(root, 0, res, count);
        for (int i = 0; i < res.size(); i++)
            res.set(i, res.get(i) / count.get(i));
        return res;
    }
    public void average(TreeNode t, int i, List < Double > sum, List < Integer > count) {
        if (t == null)
            return;
        if (i < sum.size()) {
            sum.set(i, sum.get(i) + t.val);
            count.set(i, count.get(i) + 1);
        } else {
            sum.add(1.0 * t.val);
            count.add(1);
        }
        average(t.left, i + 1, sum, count);
        average(t.right, i + 1, sum, count);
    }
}
```

**Complexity Analysis**

- Time complexity : O(n)O(n). The whole tree is traversed once only. Here, nn refers to the total number of nodes in the given binary tree.
- Space complexity : O(h)O(h). resres and countcount array of size hh are used. Here, hh refers to the height(maximum number of levels) of the given binary tree. Further, the depth of the recursive tree could go upto hh only.

#### Approach #2 Breadth First Search [Accepted]

**Algorithm**

Another method to solve the given problem is to make use of a Breadth First Search. In BFS, we start by pushing the root node into a queuequeue. Then, we remove an element(node) from the front of the queuequeue. For every node removed from the queuequeue, we add all its children to the back of the same queuequeue. We keep on continuing this process till the queuequeue becomes empty. In this way, we can traverse the given tree on a level-by-level basis.

But, in the current implementation, we need to do a slight modification, since we need to separate the nodes on one level from that of the other.

The steps to be performed are listed below:

1. Put the root node into the queuequeue.
2. Initialize sumsum and countcount as 0 and temptemp as an empty queue.
3. Pop a node from the front of the queuequeue. Add this node's value to the sumsum corresponding to the current level. Also, update the countcount corresponding to the current level.
4. Put the children nodes of the node last popped into the a temptemp queue(instead of queuequeue).
5. Continue steps 3 and 4 till queuequeue becomes empty. (An empty queuequeue indicates that one level of the tree has been considered).
6. Reinitialize queuequeue with its value as temptemp.
7. Populate the resres array with the average corresponding to the current level.
8. Repeat steps 2 to 7 till the queuequeue and temptemp become empty.

At the end, resres is the required result.

The following animation illustrates the process.

【java 版本】

```java

/**
 * Definition for a binary tree node.
 * public class TreeNode {
 *     int val;
 *     TreeNode left;
 *     TreeNode right;
 *     TreeNode(int x) { val = x; }
 * }
 */
public class Solution {
    public List < Double > averageOfLevels(TreeNode root) {
        List < Double > res = new ArrayList < > ();
        Queue < TreeNode > queue = new LinkedList < > ();
        queue.add(root);
        while (!queue.isEmpty()) {
            long sum = 0, count = 0;
            Queue < TreeNode > temp = new LinkedList < > ();
            while (!queue.isEmpty()) {
                TreeNode n = queue.remove();
                sum += n.val;
                count++;
                if (n.left != null)
                    temp.add(n.left);
                if (n.right != null)
                    temp.add(n.right);
            }
            queue = temp;
            res.add(sum * 1.0 / count);
        }
        return res;
    }
}
```

**Complexity Analysis**

- Time complexity : O(n)O(n). The whole tree is traversed atmost once. Here, nn refers to the number of nodes in the given binary tree.
- Space complexity : O(m)O(m). The size of queuequeue or temptemp can grow upto atmost the maximum number of nodes at any level in the given binary tree. Here, mm refers to the maximum mumber of nodes at any level in the input tree.

------

Analysis written by: [@vinod23](https://leetcode.com/vinod23) 