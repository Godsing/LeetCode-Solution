## Problem

Given a sorted array *nums*, remove the duplicates [**in-place**](https://en.wikipedia.org/wiki/In-place_algorithm) such that each element appear only *once* and return the new length.

Do not allocate extra space for another array, you must do this by **modifying the input array in-place** with O(1) extra memory.

**Example 1:**

```
Given nums = [1,1,2],

Your function should return length = 2, with the first two elements of nums being 1 and 2 respectively.

It doesn't matter what you leave beyond the returned length.
```

**Example 2:**

```
Given nums = [0,0,1,1,1,2,2,3,3,4],

Your function should return length = 5, with the first five elements of nums being modified to 0, 1, 2, 3, and 4 respectively.

It doesn't matter what values are set beyond the returned length.
```

**Clarification:**

Confused why the returned value is an integer but your answer is an array?

Note that the input array is passed in by **reference**, which means modification to the input array will be known to the caller as well.

Internally you can think of this:

```
// nums is passed in by reference. (i.e., without making a copy)
int len = removeDuplicates(nums);

// any modification to nums in your function would be known by the caller.
// using the length returned by your function, it prints the first len elements.
for (int i = 0; i < len; i++) {
    print(nums[i]);
}
```



## Solution

```cpp
class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        if (nums.empty()) return 0;
        
        int index = 0;
        for (int i = 1; i < nums.size(); i++) {
            if (nums[i] != nums[i-1])  //这里的判断条件可以是 nums[i] != nums[index]
                nums[++index] = nums[i];
        }
        return index + 1;
    }
};
//Runtime: 16ms, beats 99.79 % of cpp submissions.
```

另一种解法，使用 STL 库。

```cpp
// 时间复杂度 O(n), 空间复杂度 O(1)
class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        return distance(nums.begin(), unique(nums.begin(), nums.end()));
    }
};
```

unique: 在STL中unique函数是一个去重函数， unique的功能是去除相邻的重复元素(只保留一个)，其实它并不真正把重复的元素删除，是把重复的元素移到后面去了，然后依然保存到了原数组中，然后**返回一个迭代器**（去重后最后一个元素的地址）。因为unique去除的是相邻的重复元素，所以一般用之前都会要排一下序。

distance: 头文件<iterator>。返回开头和结尾（包含结尾）之间的元素个数。



## Debug&Learning



