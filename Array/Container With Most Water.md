## Problem

Given *n* non-negative integers *a1*, *a2*, ..., *an* , where each represents a point at coordinate (*i*, *ai*). *n* vertical lines are drawn such that the two endpoints of line *i* is at (*i*, *ai*) and (*i*, 0). Find two lines, which together with x-axis forms a container, such that the container contains the most water.

**Note:** You may not slant the container and *n* is at least 2.

 

![img](https://s3-lc-upload.s3.amazonaws.com/uploads/2018/07/17/question_11.jpg)

The above vertical lines are represented by array [1,8,6,2,5,4,8,3,7]. In this case, the max area of water (blue section) the container can contain is 49.

 

**Example:**

```
Input: [1,8,6,2,5,4,8,3,7]
Output: 49
```

 

## Solution

暴力解法：

1. 对于每一个数值，从它的右侧找到和它搭配时面积最大的那个，记录下面积大小；
2. 对于记录下来的 n-1 个面积，找到最大值即可。

时间复杂度 O(n^2)，空间复杂度 O(n)。

```cpp
class Solution {
public:
    int maxArea(vector<int>& height) {
        vector<int> maxs(height.size() - 1);
        int tmp;
        for (int i = 0; i < height.size() - 1; i++) {
            for (int j = i + 1; j < height.size(); j++) {
                tmp = (j - i) * min(height[i], height[j]);
                if (tmp > maxs[i]) maxs[i] = tmp;
            }
        }
        return *max_element(maxs.begin(), maxs.end());
    }
};
```

夹逼解法：

从两边向中间夹逼，遇到更高的点时，计算新的容积是否更大。夹逼应该是短的一侧往中间夹，但是我自己实现时代码十分冗余。以下参考：[Simple and fast C++/C with explanation](https://leetcode.com/problems/container-with-most-water/discuss/6090/Simple-and-fast-C++C-with-explanation)

Start by evaluating the widest container, using the first and the last line. All other possible containers are less wide, so to hold more water, they need to be higher. Thus, after evaluating that widest container, skip lines at both ends that don't support a higher height. Then evaluate that new container we arrived at. Repeat until there are no more possible containers left.

```cpp
int maxArea(vector<int>& height) {
    int water = 0;
    int i = 0, j = height.size() - 1;
    while (i < j) {
        int h = min(height[i], height[j]);
        water = max(water, (j - i) * h);
        while (height[i] <= h && i < j) i++;  //应为用 <= 号进行判断，每次这两个while只有一个（两侧中短的那侧）会进行循环，往中间夹逼
        while (height[j] <= h && i < j) j--;  //循环的时候要小心，记得加上 i < j 这个条件
    }
    return water;
}
```

