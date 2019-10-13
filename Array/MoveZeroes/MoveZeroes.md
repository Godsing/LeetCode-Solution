
## Problem

Given an array nums, write a function to move all 0's to the end of it while maintaining the relative order of the non-zero elements.

For example, given nums = [0, 1, 0, 3, 12], after calling your function, nums should be [1, 3, 12, 0, 0].

Note:
You must do this in-place without making a copy of the array.
Minimize the total number of operations.
Credits:
Special thanks to [@jianchao.li.fighter](https://leetcode.com/discuss/user/jianchao.li.fighter) for adding this problem and creating all test cases.



## Solution

我的思路：

维护两个变量，分别指向数组中的第一个0，以及第一个0后面的第一个非零的数。这样，只需要不断交换这两个数，直到第二个变量遍历至末尾。

```c++
class Solution {
public:
    void moveZeroes(vector<int>& nums) {
        int zr = 0, nz = 0;
        for (int i = 0; i < nums.size(); i++) { //find the first 0 if exist.
            nz = i + 1;
            if (nums[i] == 0) {
                zr = i;
                break;
            }
        }
        while (nz < nums.size()) { //swap the first 0 with the first non-0 after that 0.
            if (nums[nz] == 0) 
                nz++;
            else
                swap(nums[zr++], nums[nz++]);
        }
    }
};
```

看了几个人的代码，我目前所能想到的运行时间最短的版本：把判断第一个零的过程融入在了一次循环之中

```c++
class Solution {
public:
    void moveZeroes(vector<int>& nums) {
        int size = nums.size();
        if(size < 2) return;
        for (int i = 0, j = 0; i < size; i++) {
            if (nums[i]) {
                if (i != j) { //after reach at the first 0, i > j will always meet.
                //    nums[j++] = nums[i]; //Be carefully not reversed.
                    nums[j] = nums[i];
                    nums[i] = 0;
                }// else { //aka, i = j and nums[i] != 0. j will increase simultaneously with i if fisrt 0 never appear.
                j++;   
                //}
            }
        }
    }
};
```



