## Problem

Given an array of non-negative integers, you are initially positioned at the first index of the array.

Each element in the array represents your maximum jump length at that position.

Your goal is to reach the last index in the minimum number of jumps.

**Example:**

```
Input: [2,3,1,1,4]
Output: 2
Explanation: The minimum number of jumps to reach the last index is 2.
    Jump 1 step from index 0 to 1, then 3 steps to the last index.
```

**Note:**

You can assume that you can always reach the last index.



## Solution

思路：在当前可跳的最远距离内，找到下一跳可达的最远距离，跳数加一。

```cpp
class Solution {
public:
    int jump(vector<int>& nums) {
        if (nums.size() == 1) return 0;
        int reach_now = nums[0], reach_next = nums[0], steps = 1, i = 0;
        while (reach_now < nums.size()-1) {
            while (i <= reach_now) {  //在当前可跳的最远距离内，找到下一跳可达的最远距离
                reach_next = max(reach_next, i+nums[i]);
                i++;
            }
            steps++;
            reach_now = reach_next;
        }
        return steps;
    }
};
//Runtime: 8 ms, beats 97.83 % of cpp submissions.
```

2019-05-30：用了一种错误的做法，导致超时。回顾之前的AC解法，重写如下：

```c++
class Solution {
public:
    int jump(vector<int>& nums) {
        int n = nums.size(), now = 0, next = 0, i = 0, steps = 0;
        while (now < n - 1) {
            while (i <= now) {
                next = max(next, i + nums[i]);
                i++;
            }
            steps++;
            now = next;
        }
        return steps;
    }
};
```



## Debug&Learning



