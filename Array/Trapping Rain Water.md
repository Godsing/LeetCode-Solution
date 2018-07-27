## Problem

Given *n* non-negative integers representing an elevation map where the width of each bar is 1, compute how much water it is able to trap after raining.

![img](http://p1nwamyah.bkt.clouddn.com/18-7-23/33676370.jpg)
The above elevation map is represented by array [0,1,0,2,1,0,1,3,2,1,2,1]. In this case, 6 units of rain water (blue section) are being trapped. **Thanks Marcos** for contributing this image!

**Example:**

```
Input: [0,1,0,2,1,0,1,3,2,1,2,1]
Output: 6
```



## Solution

思路：根据“木桶原理”，对于每一个位置，找到它对应的“短板”，“短板”值和当前值的差就是当前位置在垂直方向上的最大蓄水量。

具体操作：（均在第2个到倒数第2个上进行，因为头、尾两个位置肯定无法蓄水）

1. 从左到右，为每个位置记录一个值，这个值等于它左边元素中的最大值与当前值之差；
2. 从右到左，为每个位置记录一个值，这个值等于它右边元素中的最大值与当前值之差；
3. 这时候，每个位置记录了两个值，这两个值中较小的那个就表示了当前位置的最大垂直蓄水量。因此，遍历一遍，将每个位置记录的较小值累加，就是总蓄水量。

```cpp
class Solution {
public:
    int trap(vector<int>& height) {
        int n = height.size(), res = 0;
        if (n < 3) return res;
        int left_gap[n], right_gap[n];
        int left_max = height[0], right_max = height[n-1];
        for (int i = 1; i < n; i++) {
            if (height[i] > left_max) {
                left_max = height[i];
                left_gap[i] = 0;
            } else
                left_gap[i] = left_max - height[i];
        }
        for (int i = n - 2; i > 0; i--) {
            if (height[i] > right_max) {
                right_max = height[i];
                right_gap[i] = 0;
            } else 
                right_gap[i] = right_max - height[i];
        }
        for (int i = 1; i < n - 1; i++) {
            // cout << left_gap[i] << ' ' << right_gap[i] << endl;
            res += min(left_gap[i], right_gap[i]);
        }
        return res;
    }
};
```

