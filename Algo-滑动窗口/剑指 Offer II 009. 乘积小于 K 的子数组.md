## 题目

给定一个正整数数组 `nums`和整数 `k` 。

请找出该数组内乘积小于 `k` 的连续的子数组的个数。

 

**示例 1:**

```
输入: nums = [10,5,2,6], k = 100
输出: 8
解释: 8个乘积小于100的子数组分别为: [10], [5], [2], [6], [10,5], [5,2], [2,6], [5,2,6]。
需要注意的是 [10,5,2] 并不是乘积小于100的子数组。
```

**示例 2:**

```
输入: nums = [1,2,3], k = 0
输出: 0
```

 

**提示:** 

- `1 <= nums.length <= 3 * 10^4`
- `1 <= nums[i] <= 1000`
- `0 <= k <= 10^6`



注意：本题与主站 713 题相同：https://leetcode-cn.com/problems/subarray-product-less-than-k/ 



来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/ZVAVXX



## 题解

```c++
class Solution {
public:
    int numSubarrayProductLessThanK(vector<int>& nums, int k) {
        if (k == 0) return 0;
        int tmp = nums[0], left = 0, right = 0, res = 0;
        while (right < nums.size()) {
            if (tmp < k || right < left) {  // 找到一个满足条件的子数组 or 当前right所指元素≥k
                if (tmp < k) res += (right - left + 1);  // 以 right 结尾的满足条件的连续子数组的个数
                right++;
                if (right < nums.size()) {
                    tmp *= nums[right];
                }
            } else {
                tmp /= nums[left];
                left++;
            }
        }
        return res;
    }
};
```

