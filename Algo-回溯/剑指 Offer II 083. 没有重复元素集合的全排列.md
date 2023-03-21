## 题目

给定一个不含重复数字的数组 `nums` ，返回其 *所有可能的全排列* 。你可以 **按任意顺序** 返回答案。

 

**示例 1：**

```
输入：nums = [1,2,3]
输出：[[1,2,3],[1,3,2],[2,1,3],[2,3,1],[3,1,2],[3,2,1]]
```

**示例 2：**

```
输入：nums = [0,1]
输出：[[0,1],[1,0]]
```

**示例 3：**

```
输入：nums = [1]
输出：[[1]]
```

 

**提示：**

- `1 <= nums.length <= 6`
- `-10 <= nums[i] <= 10`
- `nums` 中的所有整数 **互不相同**



注意：本题与主站 46 题相同：https://leetcode-cn.com/problems/permutations/ 



## 题解

- 方法一：回溯法

```c++
class Solution {
public:
    vector<vector<int>> permute(vector<int>& nums) {
        vector<vector<int>> res;
        vector<int> perm;
        vector<bool> visited(nums.size(), false);
        backtrace(nums, visited, perm, res);
        return res;
    }
    void backtrace(vector<int>& nums, vector<bool>& visited, vector<int>& perm, vector<vector<int>>& res) {
        if (perm.size() == nums.size()) {res.push_back(perm); return ;}
        for (int i = 0; i < nums.size(); i++) {
            if (visited[i]) continue;
            perm.push_back(nums[i]);
            visited[i] = true;
            backtrace(nums, visited, perm, res);
            visited[i] = false;
            perm.pop_back();
        }
    }
};
// 4 ms. 此方法效率不高，因为每个排列中的每个元素，其获取过程都需要遍历整个 visited 列表
```

用 swap 操作代替 visited 标记，可以极大地提升效率：

```c++
class Solution {
public:
    vector<vector<int> > permute(vector<int> &num) {
        vector<vector<int> > result;

        permuteRecursive(num, 0, result);
        return result;
    }
    
    // permute num[begin..end]
    // invariant: num[0..begin-1] have been fixed/permuted
    void permuteRecursive(vector<int> &num, int begin, vector<vector<int> > &result) {
        if (begin >= num.size()) {
            // one permutation instance
            result.push_back(num);
            return;
        }
        //把num[begin:end]的每个元素分别放在 begin 的位置
        for (int i = begin; i < num.size(); i++) {
            swap(num[begin], num[i]);
            permuteRecursive(num, begin + 1, result);
            // reset
            swap(num[begin], num[i]);
        }
    }
};
// 0 ms
```

- 方法二：康托编码

```c++
class Solution {
public:
    vector<vector<int>> permute(vector<int>& nums) {
        vector<vector<int> > res;
        std::sort(nums.begin(), nums.end());
        //当下一个排列比当前排列的字典序大时，next_permutation返回true
        do res.emplace_back(nums);
        while (std::next_permutation(nums.begin(), nums.end()));
        return res;
    }
};
```

