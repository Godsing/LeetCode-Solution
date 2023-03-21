## 题解

给定一个可能有重复数字的整数数组 `candidates` 和一个目标数 `target` ，找出 `candidates` 中所有可以使数字和为 `target` 的组合。

**注意：**解集不能包含重复的组合。 

 

**示例 1:**

```
输入: candidates = [10,1,2,7,6,1,5], target = 8,
输出:
[
[1,1,6],
[1,2,5],
[1,7],
[2,6]
]
```

**示例 2:**

```
输入: candidates = [2,5,2,1,2], target = 5,
输出:
[
[1,2,2],
[5]
]
```

 

**提示:**

- `1 <= candidates.length <= 100`
- `1 <= candidates[i] <= 50`
- `1 <= target <= 30`



## 题解

和上一题的主要区别在于两点：

1. 本题中，候选数组中可能存在重复元素，而**每个元素只能被至多使用一次**，因此重复 m 次的值至多只能被使用 m 次；
2. 为了保证所有解之间不重合，我们需每次“以不同的值开头”并求解这种情况下的所有解；

```c++
class Solution {
public:
    vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
        vector<vector<int>> res;
        vector<int> path;
        sort(candidates.begin(), candidates.end());
        dfs(candidates, target, 0, 0, path, res);
        return res;
    }

    void dfs(vector<int>& candidates, int target, int child_idx_start, int path_sum, vector<int>& path, vector<vector<int>>& res) {
        if (path_sum == target) {res.push_back(path); return ;}
        if (path_sum > target || child_idx_start >= candidates.size()) return ;
        for (int child_idx = child_idx_start; child_idx < candidates.size(); ) {
            path.push_back(candidates[child_idx]);
            dfs(candidates, target, child_idx + 1, path_sum + candidates[child_idx], path, res);  // child_idx + 1 保证了每个元素至多被使用一次（重复 m 次的值至多被使用 m 次）
            path.pop_back();
            // 每次“以不同的值开头”，遍历这棵树以求解这种情况下的所有解
            int next_child_idx = child_idx + 1;
            while (next_child_idx < candidates.size() && candidates[next_child_idx] == candidates[next_child_idx-1]) next_child_idx++;
            child_idx = next_child_idx;
        }
    }
};
```

