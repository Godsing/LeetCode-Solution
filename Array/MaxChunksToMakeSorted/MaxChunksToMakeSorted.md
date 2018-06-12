## Problem

Given an array `arr` that is a permutation of `[0, 1, ..., arr.length - 1]`, we split the array into some number of "chunks" (partitions), and individually sort each chunk.  After concatenating them, the result equals the sorted array.

What is the most number of chunks we could have made?

**Example 1:**

```
Input: arr = [4,3,2,1,0]
Output: 1
Explanation:
Splitting into two or more chunks will not return the required result.
For example, splitting into [4, 3], [2, 1, 0] will result in [3, 4, 0, 1, 2], which isn't sorted.
```

**Example 2:**

```
Input: arr = [1,0,2,3,4]
Output: 4
Explanation:
We can split into two chunks, such as [1, 0], [2, 3, 4].
However, splitting into [1, 0], [2], [3], [4] is the highest number of chunks possible.
```

**Note:**

- `arr` will have length in range `[1, 10]`.
- `arr[i]` will be a permutation of `[0, 1, ..., arr.length - 1]`.



## Solution

我的思路：

从位置 i (0 <= i <= arr.length -1) 开始，到位置 j (i <= j <= arr.length - 1) 为止，如果序列 [arr[i], ..., arr[j] ] 是序列 [i, ..., j] 的一个排列，则可以作为一个 chunk。同时，如果我们遵循一个原则：每次遇到符合该条件的序列，就计一个 chunk，这样就可以保证最后会得到最多的 chunk。

那么如何判断符合条件的序列呢？ 因为数组元素不会重复，而且都是在区间 [0, arr.length -1] 内的正整数。所以，从第 0 个元素开始，假设遇到的最大元素值是 max，且 arr[max] 之前的元素都不比 max 大，则意味着这是一个 [0, ..., max] 的排列，记一个 chunk；同理，每一个排列之后，下一个元素必然比 max 大，所以从下一个元素开始，也记录临时的最大值 max，直到遇到 arr[max] 之前的元素都不比 max 大，又可以算一个 chunk；这样一直遍历，就可以找到所有的 chunk。时间复杂度为 O(n) 。

```cpp
class Solution {
public:
    int maxChunksToSorted(vector<int>& arr) {
        int tempmax = arr[0];
        int tempstart = 0;
        int count = 0;
        int i = 0;
        while (1) {
            for (i = tempstart; i <= tempmax; i++) {  // i == tempmax 时退出循环，记一个chunk
                if (arr[i] > tempmax) tempmax = arr[i];
            }
            count++;
            if (i < arr.size()) {  // 到头了，就退出大循环
                tempstart = i;
                tempmax = arr[i];            
            }else break;
        }
        return count;
    }
};
```

Discuss 模块里，作者 votrubac 提供的答案比我更简洁，他把 i == tempmax 和 i < arr.size() 这两个判断条件对调了一下，使代码更容易理解。如下：

```cpp
class Solution {
public:
    int maxChunksToSorted(vector<int>& arr) {
        for (auto i = 0, max_i = 0, ch = 0; i <= arr.size(); ++i) {
            if (i == arr.size()) return ch;
            max_i = max(max_i, arr[i]);
            if (max_i == i) ++ch;
        }
    }
};
```

不过，把判断 i == arr.size() 挪到外面似乎更好一点，因为本身在循环里已经判断了 i <= arr.size() 。所以，liuchuo 的答案更好一些：

```cpp
class Solution {
public:
	int maxChunksToSorted(vector<int>& arr) {
        int ans = 0;
        for (int i = 0, maxn = 0; i < arr.size(); i++) {
            maxn = max(arr[i], maxn);
            if (maxn == i) ans++;
        }
        return ans;
    }
};
```

