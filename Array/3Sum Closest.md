## Problem

Given an array `nums` of *n* integers and an integer `target`, find three integers in `nums` such that the sum is closest to `target`. Return the sum of the three integers. You may assume that each input would have exactly one solution.

**Example:**

```
Given array nums = [-1, 2, 1, -4], and target = 1.

The sum that is closest to the target is 2. (-1 + 2 + 1 = 2).
```



## Solution

```cpp
class Solution {
public:
    int threeSumClosest(vector<int>& nums, int target) {
        int gap = INT_MAX, res = 0;  //gap的初始化值很重要，一开始初始化为target，无法通过
        sort(nums.begin(), nums.end());
        for (int i = 0; i < nums.size() - 2; i++) {
            int j = i + 1, k = nums.size() - 1;
            while (j < k) {
                int tmp = nums[i] + nums[j] + nums[k];
                if (abs(tmp - target) < gap) {
                    gap = abs(tmp - target);
                    res = tmp;
                }
                if (tmp < target) {
                    j++;
                    while (nums[j] == nums[j-1]) j++;
                } else {
                    k--;
                    while (nums[k] == nums[k+1]) k--;                    
                }
            }
        }
        return res;
    }
};
```

