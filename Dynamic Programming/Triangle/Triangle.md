## Problem

Given a triangle, find the minimum path sum from top to bottom. Each step you may move to adjacent numbers on the row below.

For example, given the following triangle

```
[
     [2],
    [3,4],
   [6,5,7],
  [4,1,8,3]
]
```

The minimum path sum from top to bottom is `11` (i.e., **2** + **3** + **5** + **1** = 11).

**Note:**

Bonus point if you are able to do this using only *O*(*n*) extra space, where *n* is the total number of rows in the triangle.



## Solution

从前往后（自底向上），非递归：

```cpp
class Solution {
public:
    int minimumTotal(vector<vector<int>>& triangle) {
        if (triangle.empty() || triangle[0].empty()) return 0;
        int n = triangle.size();
        vector<int> dp(n);
        dp[0] = triangle[0][0];
        int res, new_dp, tmp_dp;  //使用两个中间变量，以节省dp所需的空间。
        for (int i = 1; i < n; i++) {
            new_dp = dp[0] + triangle[i][0];
            for (int j = 1; j < i; j++) {
                tmp_dp = dp[j-1] < dp[j] ? dp[j-1] + triangle[i][j] : dp[j] + triangle[i][j];
                dp[j-1] = new_dp;
                new_dp = tmp_dp;
            }
            tmp_dp = dp[i-1] + triangle[i][i];
            dp[i-1] = new_dp;
            dp[i] = tmp_dp;
        }
        res = dp[0];
        for (int i = 1; i < n; i++) {
            res = dp[i] < res ? dp[i] : res;
        }
        return res;
    }
};
//Runtime: 4 ms, beats 99.97 % of cpp submissions.
```

另一种解法，从后往前（自顶向下），递归：

```cpp
class Solution {
public:
    int minimumTotal(vector<vector<int>>& triangle) {
        for (int i = triangle.size() - 2; i >= 0; i--) {
            for (int j = 0; j < i + 1; j++) {
                triangle[i][j] += min(triangle[i+1][j], triangle[i+1][j+1]);
            }
        }
        return triangle[0][0];
    }
};
```



## Debug&Learning



