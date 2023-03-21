## 题目

给你一个 **只包含正整数** 的 **非空** 数组 `nums` 。请你判断是否可以将这个数组分割成两个子集，使得两个子集的元素和相等。

 

**示例 1：**

```
输入：nums = [1,5,11,5]
输出：true
解释：数组可以分割成 [1, 5, 5] 和 [11] 。
```

**示例 2：**

```
输入：nums = [1,2,3,5]
输出：false
解释：数组不能分割成两个元素和相等的子集。
```

 

**提示：**

- `1 <= nums.length <= 200`
- `1 <= nums[i] <= 100`



注意：本题与主站 416 题相同： https://leetcode-cn.com/problems/partition-equal-subset-sum/



来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/NUPfPr



## 题解

```c++
class Solution {
public:
    bool canPartition(vector<int>& nums) {
        int sum = 0;
        for (auto& n : nums) sum += n;
        if ((sum & 1) != 0) return false;
        // 问题转化为背包问题：能否将 N 个物品中的若干个装入容量为 target 的背包，且刚好装满
        int target = sum >> 1;
        vector<bool> dp(target + 1, false);
        dp[0] = true;
        for (int i = 0; i < nums.size(); ++i) {  // 考虑第 i 个物品，放/不放入背包
            for (int j = target; j >= nums[i]; --j) {  // 考虑背包容量为 j
                // 若放入第 i 个物品，则要求还没放入前、容量为 j - nums[i] 的背包能被刚好装满
                // 若不放入第 i 个物品，则要求容量为 i 的背包已经能被刚好装满
                dp[j] = dp[j] || dp[j - nums[i]];  // 满足以上两种情况之一即可
            }
        }
        return dp[target];
    }
};
```

