## Problem

Given an array `nums` of *n* integers, are there elements *a*, *b*, *c* in `nums` such that *a* + *b* + *c* = 0? Find all unique triplets in the array which gives the sum of zero.

**Note:**

The solution set must not contain duplicate triplets.

**Example:**

```
Given array nums = [-1, 0, 1, 2, -1, -4],

A solution set is:
[
  [-1, 0, 1],
  [-1, -1, 2]
]
```

 

## Solution

先排序，后夹逼。需要注意跳过重复的数！

时间复杂度 O(n^2) ，空间复杂度 O(1)。

```cpp
class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        vector<vector<int> > res;
        if (nums.size() < 3) return res;
        sort(nums.begin(), nums.end());
        int n = nums.size();
        for (int i = 0; i < n - 2; i++) {
            if (i > 0 && nums[i] == nums[i-1]) continue;
            int target = 0 - nums[i];
            int j = i+1, k = n - 1;
            while (j < k) {
                if (nums[j] + nums[k] < target) j++;
                else if (nums[j] + nums[k] > target) k--;
                else {
                    res.push_back({nums[i], nums[j], nums[k]});  //这里不能用emplace_back()，为什么？
                    j++;
                    k--;
                    while (nums[j] == nums[j-1] && nums[k] == nums[k+1] && j < k) j++;
                }
            }
        }
        return res;
    }
};
```



## Debug&Learning



