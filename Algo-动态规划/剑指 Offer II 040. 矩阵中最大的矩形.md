## 题目

给定一个仅包含 `0` 和 `1` 、大小为 `rows x cols` 的二维二进制矩阵，找出只包含 `1` 的最大矩形，并返回其面积。

 

**示例 1：**

![img](https://mdpicbed.oss-cn-hongkong.aliyuncs.com/imgs/maximal.jpg)

```
输入：matrix = [["1","0","1","0","0"],["1","0","1","1","1"],["1","1","1","1","1"],["1","0","0","1","0"]]
输出：6
解释：最大矩形如上图所示。
```

**示例 2：**

```
输入：matrix = []
输出：0
```

**示例 3：**

```
输入：matrix = [["0"]]
输出：0
```

**示例 4：**

```
输入：matrix = [["1"]]
输出：1
```

**示例 5：**

```
输入：matrix = [["0","0"]]
输出：0
```

 

**提示：**

- `rows == matrix.length`
- `cols == matrix[0].length`
- `1 <= row, cols <= 200`
- `matrix[i][j]` 为 `'0'` 或 `'1'`



注意：本题与主站 85 题相同（输入参数格式不同）： https://leetcode-cn.com/problems/maximal-rectangle/



来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/PLYXKQ
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。



## 题解

动态规划解法：

```c++
class Solution {
public:
    int maximalRectangle(vector<string>& matrix) {
        if (matrix.empty()) return 0;
        int m = matrix.size(), n = matrix[0].size();
        // 用以下三个变量来保存遍历某一行时，当前位置的 1 向上延伸的最大高度，以及由此高度继续向左、右分别延伸所能到达的最远距离
        vector<int> heights(n, 0);
        vector<int> left_bound(n, 0);
        vector<int> right_bound(n, n-1);
        int res = 0;
        for (int i = 0; i < m; i++) {
            int row_left = 0, row_right = n-1;  // 当前行的 1 向左、右分别所能延伸到的最远位置
            for (int j = 0; j < n; j++) {
                if (matrix[i][j] == '1') {
                    heights[j]++;
                    left_bound[j] = max(left_bound[j], row_left);
                } else {
                    heights[j] = 0;
                    row_left = j+1;
                    left_bound[j] = 0;
                }
            }
            for (int j = n-1; j >= 0; j--) {
                if (matrix[i][j] == '1') {
                    right_bound[j] = min(right_bound[j], row_right);
                    res = max(res, heights[j] * (right_bound[j] - left_bound[j] + 1));
                } else {
                    row_right = j-1;
                    right_bound[j] = n-1;
                }
            }
        }
        return res;
    }
};
```



另一种思路，转化为，以每一行为底边，上方所有的 1 构成直方图，求直方图的最大矩形面积（用单调栈实现）。

