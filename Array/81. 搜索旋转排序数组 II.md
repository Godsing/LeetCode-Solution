## Problem

Suppose an array sorted in ascending order is rotated at some pivot unknown to you beforehand.

(i.e., `[0,0,1,2,2,5,6]` might become `[2,5,6,0,0,1,2]`).

You are given a target value to search. If found in the array return `true`, otherwise return `false`.

**Example 1:**

```
Input: nums = [2,5,6,0,0,1,2], target = 0
Output: true
```

**Example 2:**

```
Input: nums = [2,5,6,0,0,1,2], target = 3
Output: false
```

**Follow up:**

- This is a follow up problem to [Search in Rotated Sorted Array](https://leetcode.com/problems/search-in-rotated-sorted-array/description/), where `nums` may contain duplicates.
- Would this affect the run-time complexity? How and why?



## Solution

```cpp
class Solution {
public:
    bool search(vector<int>& nums, int target) {
        int left = 0, right = nums.size() -1, mid;
        
        while (left <= right) {
            mid = (left + right) >> 1;
            if (nums[mid] == target) return true;
            //只要保证两边和中间不都相等即可。两边同时收缩，速度更快。
            if (nums[left] == nums[mid] && nums[mid] == nums[right]) {left++; right--;}
            else if (nums[left] <= nums[mid]) {  //仔细思考，此时左半部分一定是非严格递增的
                if (nums[left] <= target && target < nums[mid]) right = mid - 1;
                else left = mid + 1;
            } else {
                if (nums[mid] < target && target <= nums[right]) left = mid + 1;
                else right = mid - 1;
            }
        }
        
        return false;
    }
};
//Runtime: 4 ms, beats 99.90 % of cpp submissions.
```

另一种方法，保证序列某一侧和中间值不相等即可，也就是说让 nums[mid] == nums[hi] （或者 nums[lo] == nums[mid]）不成立即可。

```cpp
class Solution {
public:
    bool search(vector<int>& nums, int target) {
        if(nums.empty()) return false;
        int lo =0, hi = nums.size() -1;
        while(lo<hi){
              int mid=(lo+hi)/2;
              if(nums[mid]==target) return true;
              if(nums[mid]>nums[hi]){
                  if(nums[mid]>target && nums[lo] <= target) hi = mid;
                  else lo = mid + 1;
              }else if(nums[mid] < nums[hi]){
                  if(nums[mid]<target && nums[hi] >= target) lo = mid + 1;
                  else hi = mid;
              }else{
                  hi--;
              }
        }
        return nums[lo] == target ? true : false;
    }
};
```

```cpp
class Solution {
public:
    bool search(const vector<int>& nums, int target) {
        int first = 0, last = nums.size();
        while (first != last) {
            const int mid = first + (last - first) / 2;
            if (nums[mid] == target)
                return true;
            if (nums[first] < nums[mid]) {
                if (nums[first] <= target && target < nums[mid])
                    last = mid;
                else
                    first = mid + 1;
            } else if (nums[first] > nums[mid]) {
                if (nums[mid] < target && target <= nums[last-1])
                    first = mid + 1;
                else
                    last = mid;
            } else
                //skip duplicate one
                first++;
        }
        return false;
    }
};
//Runtime: 4 ms
```



## Debug&Learning



