## 题解

给你一个整数数组 `nums` ，数组中的元素 **互不相同** 。返回该数组所有可能的子集（幂集）。

解集 **不能** 包含重复的子集。你可以按 **任意顺序** 返回解集。

 

**示例 1：**

```
输入：nums = [1,2,3]
输出：[[],[1],[2],[1,2],[3],[1,3],[2,3],[1,2,3]]
```

**示例 2：**

```
输入：nums = [0]
输出：[[],[0]]
```

 

**提示：**

- `1 <= nums.length <= 10`
- `-10 <= nums[i] <= 10`
- `nums` 中的所有元素 **互不相同**



注意：本题与主站 78 题相同： https://leetcode-cn.com/problems/subsets/



## 题解

```c++
class Solution {
public:
    vector<vector<int>> subsets(vector<int>& nums) {
        vector<vector<int>> res;
        vector<int> path;
        dfs(nums, 0, path, res);
        return res;
    }

    void dfs(vector<int>& nums, int i, vector<int>& path, vector<vector<int>>& res) {
        if (i == nums.size()) {res.push_back(path); return ;}
        dfs(nums, i+1, path, res);
        path.push_back(nums[i]);
        dfs(nums, i+1, path, res);
        path.pop_back();
    }
};
```

