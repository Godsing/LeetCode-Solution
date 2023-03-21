## 题目

给定整数数组 `nums` 和整数 `k`，请返回数组中第 `**k**` 个最大的元素。

请注意，你需要找的是数组排序后的第 `k` 个最大的元素，而不是第 `k` 个不同的元素。

 

**示例 1:**

```
输入: [3,2,1,5,6,4] 和 k = 2
输出: 5
```

**示例 2:**

```
输入: [3,2,3,1,2,4,5,5,6] 和 k = 4
输出: 4
```

 

**提示：**

- `1 <= k <= nums.length <= 10^4`
- `-104 <= nums[i] <= 10^4`



注意：本题与主站 215 题相同： https://leetcode-cn.com/problems/kth-largest-element-in-an-array/



来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/xx4gT2



## 题解

- 递归写法

```c++
class Solution {
public:
    int findKthLargest(vector<int>& nums, int k) {
        return find(nums, 0, nums.size()-1, nums.size()-k);
    }

    int find(vector<int>& nums, int l, int r, int k) {
        int i = l;
        for (int j = i; j <= r; j++) if (nums[j] < nums[l]) swap(nums[j], nums[++i]);
        swap(nums[l], nums[i]);
        if (i == k) return nums[i];
        else if (i < k) return find(nums, i+1, r, k);
        else return find(nums, l, i-1, k);
    }
};
```

- 循环写法（虽然是二叉树先序遍历，但由于我们能**一路剪枝**直到目标叶子节点，所以其实不需要像 DFS 那样用递归）

```c++
class Solution {
public:
    int findKthLargest(vector<int>& nums, int k) {
        int left = 0, right = nums.size()-1, target = nums.size()-k;
        int p = partition(nums, left, right);
        while (p != target) {
            if (p < target) left = p + 1;
            else right = p - 1;
            p = partition(nums, left, right);
        }
        return nums[p];
    }

    int partition(vector<int>& nums, int l, int r) {
        int i = l;
        for (int j = i; j <= r; j++) if (nums[j] < nums[l]) swap(nums[j], nums[++i]);
        swap(nums[l], nums[i]);
        return i;
    }
};
```

以上两种写法差不多，遇到极端情况（原始数组有序），都是直接拉跨，所以最好是随机选择中枢节点：

- 方法一优化版：

```c++
class Solution {
public:
    int findKthLargest(vector<int>& nums, int k) {
        return find(nums, 0, nums.size()-1, nums.size()-k);
    }

    int find(vector<int>& nums, int l, int r, int k) {
        int rand_pos = rand() % (r - l + 1) + l;
        swap(nums[l], nums[rand_pos]);  // 将随机一个元素作为中枢节点
        int i = l;  //用 i 记录最后一个小于等于中枢节点 nums[l] 的元素的索引
        for (int j = i; j <= r; j++) if (nums[j] < nums[l]) swap(nums[j], nums[++i]);
        swap(nums[l], nums[i]);  // 将中枢节点挪到 i 的位置
        if (i == k) return nums[i];
        else if (i < k) return find(nums, i+1, r, k);
        else return find(nums, l, i-1, k);
    }
};
```



- 方法二优化版：

```c++
class Solution {
public:
    int findKthLargest(vector<int>& nums, int k) {
        int left = 0, right = nums.size()-1, target = nums.size()-k;
        int p = random_partition(nums, left, right);
        while (p != target) {
            if (p < target) left = p + 1;
            else right = p - 1;
            p = random_partition(nums, left, right);
        }
        return nums[p];
    }

    inline int random_partition(vector<int> &nums, int left, int right) {
        int rand_pos = rand() % (right - left + 1) + left;  // 随机选择中枢节点
        swap(nums[rand_pos], nums[left]);
        return partition(nums, left, right);
    }

    inline int partition(vector<int>& nums, int l, int r) {
        int i = l;
        for (int j = i; j <= r; j++) if (nums[j] < nums[l]) swap(nums[j], nums[++i]);
        swap(nums[l], nums[i]);
        return i;
    }
};
```

