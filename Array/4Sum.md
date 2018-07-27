## Problem

Given an array `nums` of *n* integers and an integer `target`, are there elements *a*, *b*, *c*, and *d* in `nums` such that *a* + *b* + *c* + *d* = `target`? Find all unique quadruplets in the array which gives the sum of `target`.

**Note:**

The solution set must not contain duplicate quadruplets.

**Example:**

```
Given array nums = [1, 0, -1, 0, -2, 2], and target = 0.

A solution set is:
[
  [-1,  0, 0, 1],
  [-2, -1, 1, 2],
  [-2,  0, 0, 2]
]
```



## Solution

思路：

1. 先排序，从小到大
2. 依次遍历 a 和 b，对于每一种可能的 (a, b) 组合，采用夹逼的方法找到满足条件的 c 和 d。

注意点：因为可能存在重复的元素，所以每次使用完一个数之后，都要挪到后面(对于a, b, c) 或前面(对于d) 不重复的位置上。

分析：时间复杂度 O(n^3)，空间复杂度 O(1)。

```cpp
class Solution {
public:
    vector<vector<int>> fourSum(vector<int>& nums, int target) {
        vector<vector<int> > res;
        if (nums.size() < 4) return res;
        sort(nums.begin(), nums.end());
        auto last = nums.end();  //指向最后一个元素的下一个位置
        for (auto a = nums.begin(); a < prev(last, 3); ) {
            for (auto b = a + 1; b < prev(last, 2); ) {
                auto c = b + 1;
                auto d = last - 1;  //注意这里需要减一
                while (c < d) {
                    if (*a + *b + *c + *d < target) {
                        ++c;
                        while (*c == *(c - 1)) c++;
                    } else if (*a + *b + *c + *d > target) {
                        --d;
                        while (*d == *(d + 1)) d--;
                    } else {
                        res.push_back({*a, *b, *c, *d});
                        ++c;
                        while (*c == *(c - 1)) c++;
                        --d;
                        while (*d == *(d + 1)) d--;
                    }
                }
                b++;
                while (*b == *(b - 1)) b++;
            }
            a++;
            while (*a == *(a - 1)) a++;
        }
        return res;
    }
};
//Runtime: 24 ms
```

