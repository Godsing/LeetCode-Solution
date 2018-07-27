## Problem

Suppose an array sorted in ascending order is rotated at some pivot unknown to you beforehand.

(i.e., `[0,1,2,4,5,6,7]` might become `[4,5,6,7,0,1,2]`).

You are given a target value to search. If found in the array return its index, otherwise return `-1`.

You may assume no duplicate exists in the array.

Your algorithm's runtime complexity must be in the order of *O*(log *n*).

**Example 1:**

```
Input: nums = [4,5,6,7,0,1,2], target = 0
Output: 4
```

**Example 2:**

```
Input: nums = [4,5,6,7,0,1,2], target = 3
Output: -1
```



## Solution

```cpp
class Solution {
public:
    int search(vector<int>& nums, int target) {
        int first = 0, last = nums.size();
        while (first != last) {
            const int mid = first + (last - first) / 2;
            if (nums[mid] == target)
                return mid;
            if (nums[mid] > nums[first]) {  //左半个序列递增
                if (nums[first] <= target && target < nums[mid])
                    last = mid;
                else 
                    first = mid + 1;
            } else {  //右半个序列递增
                if (nums[mid] < target && target <= nums[last-1])
                    first = mid + 1;
                else
                    last = mid;
            }
        }
        
        return -1;
    }
};
//Runtime: 4 ms, beats 99.85 % of cpp submissions.
```



## Debug&Learning



