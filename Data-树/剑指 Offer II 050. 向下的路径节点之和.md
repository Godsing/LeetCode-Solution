## 题目

给定一个二叉树的根节点 `root` ，和一个整数 `targetSum` ，求该二叉树里节点值之和等于 `targetSum` 的 **路径** 的数目。

**路径** 不需要从根节点开始，也不需要在叶子节点结束，但是路径方向必须是向下的（只能从父节点到子节点）。

 

**示例 1：**

![img](https://mdpicbed.oss-cn-hongkong.aliyuncs.com/imgs/pathsum3-1-tree.jpg)

```
输入：root = [10,5,-3,3,2,null,11,3,-2,null,1], targetSum = 8
输出：3
解释：和等于 8 的路径有 3 条，如图所示。
```

**示例 2：**

```
输入：root = [5,4,8,11,null,13,4,7,2,null,null,5,1], targetSum = 22
输出：3
```

 

**提示:**

- 二叉树的节点个数的范围是 `[0,1000]`
- `-109 <= Node.val <= 109` 
- `-1000 <= targetSum <= 1000` 



注意：本题与主站 437 题相同：https://leetcode-cn.com/problems/path-sum-iii/



## 题解

显然，对于每条从根节点到叶子节点的路径，我们需要知道其中和为 `targetSum` 的子区间的个数。而要快速计算任意区间的和，很容易想到数组的“前缀和”技巧。但在这里，我们不需要确切知道和为 `targetSum` 的子区间在路径中的起点和终点，而是要知道有多少这样的区间，因此，我们不用数组来保存前缀和，而是用一个哈希映射来对“前缀和”进行计数。

进而，只需要在深度遍历的过程中，遇到每个节点，就能马上知道前面有多少个符合条件的节点可以作为起点。

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
    int pathSum(TreeNode* root, int targetSum) {
        unordered_map<int, int> prefix_sum_cnt;
        prefix_sum_cnt[0] = 1;
        int res = 0;
        dfs(root, targetSum, 0, prefix_sum_cnt, res);
        return res;
    }

    void dfs(TreeNode* root, int t, int path_sum, unordered_map<int, int>& sum_cnt, int& res) {
        if (!root) return ;
        path_sum += root->val;
        res += sum_cnt[path_sum - t];
        sum_cnt[path_sum]++;
        dfs(root->left, t, path_sum, sum_cnt, res);
        dfs(root->right, t, path_sum, sum_cnt, res);
        sum_cnt[path_sum]--;
        path_sum -= root->val;
    }
};
```

