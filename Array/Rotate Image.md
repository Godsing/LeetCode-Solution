48. Rotate Image



## Problem

You are given an *n* x *n* 2D matrix representing an image.

Rotate the image by 90 degrees (clockwise).

**Note:**

You have to rotate the image [**in-place**](https://en.wikipedia.org/wiki/In-place_algorithm), which means you have to modify the input 2D matrix directly. **DO NOT** allocate another 2D matrix and do the rotation.

**Example 1:**

```
Given input matrix = 
[
  [1,2,3],
  [4,5,6],
  [7,8,9]
],

rotate the input matrix in-place such that it becomes:
[
  [7,4,1],
  [8,5,2],
  [9,6,3]
]
```

**Example 2:**

```
Given input matrix =
[
  [ 5, 1, 9,11],
  [ 2, 4, 8,10],
  [13, 3, 6, 7],
  [15,14,12,16]
], 

rotate the input matrix in-place such that it becomes:
[
  [15,13, 2, 5],
  [14, 3, 4, 1],
  [12, 6, 8, 9],
  [16, 7,10,11]
]
```



## Solution

我的思路：直接逐个元素顺时针旋转，找到旋转的计算规律和循环的边界即可。

```cpp
class Solution {
public:
    void rotate(vector<vector<int>>& matrix) {
        if (matrix.size() <= 1) return ;
        int n = matrix.size();
        int max_i = n / 2 - 1;
        for (int i = 0; i <= max_i; i++) {
            for (int j = i; j <= n-2-i; j++) {
                int a = j, b = n-1-i, tmp = matrix[i][j], tmp2 = 0;
                while(a != i || b != j) {
                    tmp2 = matrix[a][b];
                    matrix[a][b] = tmp;
                    tmp = tmp2;
                    next_ab(a, b, n);
                }
                matrix[i][j] = tmp;
            }
        }
        return ;
    }
private:
    void next_ab(int& a, int& b, const int& n) {
        int tmp = n - 1 - a;
        a = b;
        b = tmp;
    }
};
```



## Debug&Learning

值得好好学习的方法：

```c++
class Solution {
public:
    void rotate(vector<vector<int>>& matrix) {
        reverse(matrix.begin(), matrix.end());
        for(int i = 0; i < matrix.size(); i++)
        {
            for(int j = i; j < matrix[i].size();j++)
            {
                int temp = matrix[i][j];
                matrix[i][j] = matrix[j][i];
                matrix[j][i] = temp;
            }
        }        
    }
};
```



