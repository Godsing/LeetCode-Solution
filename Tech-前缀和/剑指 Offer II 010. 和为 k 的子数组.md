## 题目

给你一个整数数组 `nums` 和一个整数 `k` ，请你统计并返回该数组中和为 `k` 的连续子数组的个数。

 **示例 1：**

```
输入：nums = [1,1,1], k = 2
输出：2
```

**示例 2：**

```
输入：nums = [1,2,3], k = 3
输出：2
```

**提示：**

- $1 <= nums.length <= 2 * 10^4$
- $-1000 <= nums[i] <= 1000$
- $-10^7 <= k <= 10^7$



注意：本题与主站 560 题相同： https://leetcode-cn.com/problems/subarray-sum-equals-k/



## 题解

```c++
class Solution {
public:
    int subarraySum(vector<int>& nums, int k) {
        unordered_map<int, int> prefixsum_cnt{{0, 1}};
        int prefixsum = 0, res = 0;
        for (int num : nums) {
            prefixsum = prefixsum + num;
            res += prefixsum_cnt[prefixsum - k];
            prefixsum_cnt[prefixsum]++;
        }
        return res;
    }
};
```

