## 题目

给定一个二进制数组 `nums` , 找到含有相同数量的 `0` 和 `1` 的最长连续子数组，并返回该子数组的长度。

 

**示例 1:**

```
输入: nums = [0,1]
输出: 2
说明: [0, 1] 是具有相同数量 0 和 1 的最长连续子数组。
```

**示例 2:**

```
输入: nums = [0,1,0]
输出: 2
说明: [0, 1] (或 [1, 0]) 是具有相同数量0和1的最长连续子数组。
```

 

**提示：**

- `1 <= nums.length <= 10^5`
- `nums[i]` 不是 `0` 就是 `1`



注意：本题与主站 525 题相同： https://leetcode-cn.com/problems/contiguous-array/



## 题解

这道题可以视为“前缀和”技巧的引申。

```c++
class Solution {
public:
    int findMaxLength(vector<int>& nums) {
        unordered_map<int, int> diff_min_index{{0, -1}};
        int diff = 0, maxlen = 0;
        for (int i = 0; i < nums.size(); i++) {
            if (nums[i] == 1) diff++;  // diff 为截止当前，1 比 0 多出来的个数
            else diff--;
            if (!diff_min_index.count(diff)) diff_min_index[diff] = i;
            else maxlen = max(maxlen, i - diff_min_index[diff]);  // 当前所在位置，减去当前 diff 第一次出现的位置，就是这一段满足条件的连续子数组的长度
        }
        return maxlen;
    }
};
```

