## 题目

给定两个整数 `n` 和 `k`，返回范围 `[1, n]` 中所有可能的 `k` 个数的组合。

你可以按 **任何顺序** 返回答案。

 

**示例 1：**

```
输入：n = 4, k = 2
输出：
[
  [2,4],
  [3,4],
  [2,3],
  [1,2],
  [1,3],
  [1,4],
]
```

**示例 2：**

```
输入：n = 1, k = 1
输出：[[1]]
```

 

**提示：**

- `1 <= n <= 20`
- `1 <= k <= n`



注意：本题与主站 77 题相同： https://leetcode-cn.com/problems/combinations/



## 题解

```c++
class Solution {
public:
    vector<vector<int>> combine(int n, int k) {
        vector<vector<int>> res;
        vector<int> path;
        dfs(n, 1, path, res, k);
        return res;
    }

    void dfs(const int& max_num, int num, vector<int>& path, vector<vector<int>>& res, const int& target_len) {
        if (path.size() == target_len) {res.push_back(path); return ;}  // 找到一个解，剪枝
        if (num > max_num || target_len - path.size() > max_num - num + 1) return ;  // 此路径无解，剪枝
        path.push_back(num);
        dfs(max_num, num+1, path, res, target_len);
        path.pop_back();
        dfs(max_num, num+1, path, res, target_len);
    }
};
```

