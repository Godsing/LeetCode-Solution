## Problem

Suppose an array sorted in ascending order is rotated at some pivot unknown to you beforehand.

(i.e., `[0,1,2,4,5,6,7]` might become `[4,5,6,7,0,1,2]`).

You are given a target value to search. If found in the array return its index, otherwise return `-1`.

You may assume no duplicate exists in the array

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

与上面"先判断左/右半个序列是否递增"不同，下面这种方法先判断大小，在判断是否递增：2019年04月01日

```cpp
class Solution {
public:
    int search(vector<int>& nums, int target) {
        int l = 0, r = nums.size() - 1;
        while (l <= r) {
            int mid = l + (r - l) / 2;
            if (nums[mid] == target) return mid;
            if (nums[mid] > target) {
                //左半序列递增，且target在范围内
                if (nums[l] <= target) r = mid - 1;
                //左半序列递增，而target不在范围内，所以只可能在右半序列
                //因为可能出现 l == mid 的情况（比如输入[3, 1]），所以这里要用 "<=" 号
                else if (nums[l] <= nums[mid]) l = mid + 1;
                //右半序列一定递增，且都大于target，所以只可能在左半序列
                else r = mid - 1;
            } else {
                if (nums[r] >= target) l = mid + 1;
                else if (nums[r] > nums[mid]) r = mid - 1;
                else l = mid + 1;
            }
        }
        return -1;
    }
};
```



## Debug&Learning



