## 题目

给定一个可包含重复数字的序列 `nums` ，***按任意顺序*** 返回所有不重复的全排列。

 

**示例 1：**

```
输入：nums = [1,1,2]
输出：
[[1,1,2],
 [1,2,1],
 [2,1,1]]
```

**示例 2：**

```
输入：nums = [1,2,3]
输出：[[1,2,3],[1,3,2],[2,1,3],[2,3,1],[3,1,2],[3,2,1]]
```

 

**提示：**

- `1 <= nums.length <= 8`
- `-10 <= nums[i] <= 10`



注意：本题与主站 47 题相同： https://leetcode-cn.com/problems/permutations-ii/



## 题解

相较于上一题，有几处改动：

1. 添加 while 循环用于跳过值相同的元素；
2. 注释掉复位 swap 操作，以保证剩余数组在 for 循环中每次 swap 后依然有序(e.g. [1,1,2,2,3,3,4]->[2,1,1,2,3,3,4]->[3,1,1,2,2,3,4]);
3. 需要提前排好序；
4. permuteRecursive 的第一个参数 num 不能再是传引用。

```c++
class Solution {
public:
    vector<vector<int>> permuteUnique(vector<int>& nums) {
        vector<vector<int>> result;
        sort(nums.begin(), nums.end());  // 改动 3
        permuteRecursive(nums, 0, result);
        return result;
    }
    
    void permuteRecursive(vector<int> num, int begin, vector<vector<int> > &result) {  // 改动 4
        if (begin >= num.size()) {
            result.push_back(num);
            return;
        }
        for (int i = begin; i < num.size(); i++) {
            swap(num[begin], num[i]);
            permuteRecursive(num, begin + 1, result);
            while (i+1 < num.size() && num[i+1] == num[begin]) i++;  // 改动 1
            // swap(num[begin], num[i]);  // 改动 2
        }
    }
};
```

