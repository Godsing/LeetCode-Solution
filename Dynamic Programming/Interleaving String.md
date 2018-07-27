## Problem

Given *s1*, *s2*, *s3*, find whether *s3* is formed by the interleaving of *s1* and *s2*.

**Example 1:**

```
Input: s1 = "aabcc", s2 = "dbbca", s3 = "aadbbcbcac"
Output: true
```

**Example 2:**

```
Input: s1 = "aabcc", s2 = "dbbca", s3 = "aadbbbaccc"
Output: false
```



## Solution

二维动态规划。

设状态 f[i+1]\[j+1] = true，表示 s1[0:i] 和 s2[[0:j] 交叉之后可以得到 s3[0: i+j+1]。

```cpp
class Solution {
public:
    bool isInterleave(string s1, string s2, string s3) {
        if(s3.length() != s1.length() + s2.length()) return false;
        
        const int n1 = s1.size();
        const int n2 = s2.size();
        bool f[n1+1][n2+1];
        f[0][0] = true;
        for (int i = 0; i < n2; i++) {
            f[0][i+1] = (s2[i] == s3[i] && f[0][i]);
        }
        for (int i = 0; i < n1; i++) {
            f[i+1][0] = (s1[i] == s3[i] && f[i][0]);
        }
        for (int i = 0; i < n1; i++) {
            for (int j = 0; j < n2; j++) {
                f[i+1][j+1] = (s1[i] == s3[i+j+1] && f[i][j+1]) || (s2[j] == s3[i+j+1] && f[i+1][j]);  //状态转移方程
            }
        }
        return f[n1][n2];
    }
};
```



## Debug&Learning



