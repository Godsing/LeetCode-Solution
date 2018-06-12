## Problem

Given two integers n and k, you need to construct a list which contains n different positive integers ranging from 1 to n and obeys the following requirement: 
Suppose this list is $[a_1, a_2, a_3, ... , a_n]$ , then the list $ [|a_1 - a_2|, |a_2 - a_3|, |a_3 - a_4|, ... , |a_n-1 - a_n|]$ has exactly k distinct integers.

If there are multiple answers, print **any** of them. (此处any是“任意”，不是“任何”)。

**Example 1:**

```
Input: n = 3, k = 1
Output: [1, 2, 3]
Explanation: The [1, 2, 3] has three different positive integers ranging from 1 to 3, and the [1, 1] has exactly 1 distinct integer: 1.

```

**Example 2:**

```
Input: n = 3, k = 2
Output: [1, 3, 2]
Explanation: The [1, 3, 2] has three different positive integers ranging from 1 to 3, and the [2, 1] has exactly 2 distinct integers: 1 and 2.

```

**Note:**

1. The `n` and `k` are in the range 1 <= k < n <= 104.





## Solution

if you have `n` number, the maximum `k` can be `n - 1`;
if `n` is 9, max `k` is 8.
This case can be done by picking numbers interleavingly from head and tail, like this:

```
// start from i = 1, j = n;
// i++, j--, i++, j--, i++, j--

1   2   3   4   5
  9   8   7   6
out: 1 9 2 8 3 7 6 4 5
dif:  8 7 6 5 4 3 2 1
```

Above is a case where `k` is exactly `n - 1`
When k is less than that, simply lay out the rest `(i, j)` in incremental
order(all diff is 1). Say if k is 5:

```
     i++ j-- i++ j--  i++ i++ i++ ...
out: 1   9   2   8    3   4   5   6   7
dif:   8   7   6   5    1   1   1   1 
```

cited from: https://discuss.leetcode.com/topic/101113/c-java-clean-code-4-liner

---

我的进一步分析：

我们可以把所要输出的结果序列从中间劈开，分成左右两部分：左边有 `k-1` 个交叉排列的数，右边是一个递增（其实也可以是递减，只要和前面的交叉排列互补即可）序列——这样便符合了题目的要求。

在右边子序列是递增的情况下，该子序列的第一个数是子序列中最小的，那么（参考下面代码 i = 1, j = n，每次得到一个数就 i++ 或 j--），这就意味着左边子序列的倒数第一个（即第 k-1 个）必须是 (多次)j-- 之后某个 j（不能是i，因为如果是i，就和右边那个数的间隔也为1，所有不同的间隔数就变成(k-2) + 1=(k-1)了）。

所以，交叉往左递推，如果 k-1 是奇数（即k是偶数），则左边子序列第一个数从 j 开始；否则从 i 开始。故得到：第一个数 `= k % 2 ? i : j;` ，然后利用该式不断往下循环即可。

```c++
class Solution {
    public:
    vector<int> constructArray(int n, int k) {
        vector<int> res;
        for (int i = 1, j = n; i <= j; ) {
            if (k > 1) {
                 res.push_back(k-- % 2 ? i++ : j--); //k可被2整除时，取j，否则取i 
            }
            else {
                 res.push_back(i++); //得到右边子序列 
            }
        }
        return res;
    }
};
```

