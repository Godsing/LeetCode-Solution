## Problem

442. **Find All Duplicates in an Array**

Given an array of integers, 1 ≤ a[i] ≤ *n* (*n* = size of array), some elements appear **twice** and others appear **once**.

Find all the elements that appear **twice** in this array.

Could you do it without extra space and in O(*n*) runtime?

**Example:**

```
Input:
[4,3,2,7,8,2,3,1]

Output:
[2,3]
```



## Solution

如果要在 O(*n*) 的时间复杂度且不使用额外空间的情况下求解，我没有想到解法。参考了其他人的代码，最后写成如下形式，并加上必要的注释：

```c++
#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    vector<int> findDuplicates(vector<int>& nums) {
        vector<int> result;
        int i = 0;
        for (i = 0; i < nums.size(); ) {
            if (nums[i] != nums[nums[i]-1]) 
// loop until current value equals to corresponded value of position(current value minus 1). That is to say, the position has the right value(position_plus_one) or duplicated value.
              swap(nums[i], nums[nums[i] - 1]);
            else // the position corresponded to current_value_minus_one has been put appropriate value(aka. position_plus_one) 
                i++; 
        } // after the loop, every position has been put the most suitable value.
        for (i = 0; i < nums.size(); i++) {
            if (i != (nums[i] - 1) ) {
                result.emplace_back(nums[i]); // bester than method push_back()
            }
        }
        return result;
    }
};

```

### 我的思考：

第一个循环目的是使所有位置都放置“最恰当的”数字，第二个循环是找出重复数字。

- 以下论证第一个循环为什么是**可行的、完整的**：

第一个循环是核心：并不是每一轮都要 i++ ; 而是在当前位置已经放了最恰当的（不能再好的）数字之后，才处理下一个位置。这里“最恰当的”意思是：该位置已经放置了与位置对应的数字（记为情况①），或者某个重复数字（该数字等于其对应的位置的数字）（记为情况②）；比如，在第一个位置，i=0，那个最终该位置的数字要么是1（与位置对应的数字），要么是某个数比如3且第3个位置(i=2)的值也为3，这两种情况下交换(自身交换或者相同数字交换)已经没有意义。

每次 i 加一后，也就是说对下一个位置的处理时，无论怎么操作，都不会影响到之前已经符合情况①的那些位置(反证法想一下就能明白)。而那些情况②的位置如果受影响，那产生的结果必然是那些位置变成情况①了(因为只有契合那些位置的数字才会被交换到那里去)；所以，对每一个位置的操作过程，都是使全局往最优化方向发展。

这样，最终循环结束后，每个位置都放置了“最恰当的”的数字。

之所以是无遗漏的、**完整的**，是因为，最后每个位置要么是情况①、要么是情况②——如果是情况①，显然无法再优化；如果是情况②，意味着必然是某个重复的数字，既然都重复了(也就是该数字对应的位置已经被占了)，当然也无法继续优化了。言而总之，就是全局最优了。

- 第二个循环，就是找到那些情况②的位置，这些数就是重复数字。

---

### 我的启发：

这道题的这种解法，限制条件很多，可迁移性并不好。限制条件有：

1. 所有元素都是正整数
2. 1 ≤ a[i] ≤ *n* (*n* = size of array) （其实只要 “取值区间的大小=元素个数” 即可）
3. 有些元素出现两次（**不能更多**），其他的出现一次

尽管如此，这道题还是很能锻炼思维：限制越多，意味着情况越特殊。如果充分利用这些特殊性，可能得到一些比较巧妙的、只适用于该问题的解法。

