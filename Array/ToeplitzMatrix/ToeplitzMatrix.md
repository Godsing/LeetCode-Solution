

## Problem

766. **Toeplitz Matrix**

A matrix is *Toeplitz* if every diagonal from top-left to bottom-right has the same element.

Now given an `M x N` matrix, return `True` if and only if the matrix is *Toeplitz*.

**Example 1:**

```
Input: matrix = [[1,2,3,4],[5,1,2,3],[9,5,1,2]]
Output: True
Explanation:
1234
5123
9512

In the above grid, the diagonals are "[9]", "[5, 5]", "[1, 1, 1]", "[2, 2, 2]", "[3, 3]", "[4]", and in each diagonal all elements are the same, so the answer is True.
```

**Example 2:**

```
Input: matrix = [[1,2],[2,2]]
Output: False
Explanation:
The diagonal "[1, 2]" has different elements.
```

**Note:**

1. `matrix` will be a 2D array of integers.
2. `matrix` will have a number of rows and columns in range `[1, 20]`.
3. `matrix[i][j]` will be integers in range `[0, 99]`.

---

## Solution

- 一开始的思路是这样的：

遍历每一个对角线，只要遍历过程中出现不相等的立即退出。

这样做的时间复杂度也算正常，是 $O(n^2)$ 但是代码就难实现很多，因为要考虑很多边界。

- 后来得到启发：

只需要每个判断每个元素是否和它左上角(如果存在)的元素相等即可，使用常规的遍历。

时间复杂度一样，但是代码容易实现。



## 总结

考虑问题不仅要考虑效率，还要考虑实现难度。有时候换个角度思考问题，就可以得到另一中解决问题的方式。

