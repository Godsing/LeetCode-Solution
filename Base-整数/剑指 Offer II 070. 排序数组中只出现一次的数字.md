## 题目

给你一个仅由整数组成的有序数组，其中每个元素都会出现两次，唯有一个数只会出现一次。

请你找出并返回只出现一次的那个数。

你设计的解决方案必须满足 `O(log n)` 时间复杂度和 `O(1)` 空间复杂度。

 

**示例 1:**

```
输入: nums = [1,1,2,3,3,4,4,8,8]
输出: 2
```

**示例 2:**

```
输入: nums =  [3,3,7,7,10,11,11]
输出: 10
```

 



**提示:**

- `1 <= nums.length <= 10^5`
- `0 <= nums[i] <= 10^5`



**进阶:** 采用的方案可以在 `O(log n)` 时间复杂度和 `O(1)` 空间复杂度中运行吗？



注意：本题与主站 540 题相同：https://leetcode-cn.com/problems/single-element-in-a-sorted-array/



来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/skFtm2



## 题解

此题核心在于判断当前 mid 是否满足目标，还是在目标值的左侧还是右侧。注意细节！

```c++
class Solution {
public:
    int singleNonDuplicate(vector<int>& nums) {
        // 用异或可解，但时间复杂度 O(n)。二分搜索更快
        int left = 0, right = nums.size() - 1, mid = 0;
        while (left <= right) {
            mid = left + (right - left) / 2;
            if ((mid == 0 || nums[mid-1] != nums[mid]) && (mid == nums.size()-1 || nums[mid+1] != nums[mid])) return nums[mid];
            if (((mid&1) == 0 && mid < nums.size()-1 && nums[mid] == nums[mid+1]) || (mid&1) && nums[mid] == nums[mid-1]) left = mid + 1;
            else right = mid - 1;
        }
        return -1;
    }
};
```

