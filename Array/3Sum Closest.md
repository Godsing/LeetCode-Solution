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
                    //若不是题目中说了"You may assume that each input would have exactly one solution."(意味着输入数据不会出现多个数都相等的情况)，下面这种写法可能会出现最后 j 越界的情况
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

2019-05-29：

```c++
class Solution {
public:
    int threeSumClosest(vector<int>& nums, int target) {
        int gap = INT_MAX, res = 0, n = nums.size();
        sort(nums.begin(), nums.end());
        for (int i=0; i < n - 2; i++) {
            int j = i + 1, k = n - 1;
            while (j < k) {
                int tmp = nums[i] + nums[j] + nums[k];
                if (abs(tmp - target) < gap) {
                    gap = abs(tmp - target);
                    res = tmp;
                }
                if (tmp < target) {
                    j++;
                    //为了保证稳定，还是加上 j < k 为好
                    while (j < k && nums[j] == nums[j-1]) j++;
                } else {
                    k--;
                    while (j < k && nums[k] == nums[k+1]) k--;
                }
            }
        }
        return res;
    }
};
```

