## Problem

Given two words *word1* and *word2*, find the minimum number of operations required to convert *word1* to *word2*.

You have the following 3 operations permitted on a word:

1. Insert a character
2. Delete a character
3. Replace a character

**Example 1:**

```
Input: word1 = "horse", word2 = "ros"
Output: 3
Explanation: 
horse -> rorse (replace 'h' with 'r')
rorse -> rose (remove 'r')
rose -> ros (remove 'e')
```

**Example 2:**

```
Input: word1 = "intention", word2 = "execution"
Output: 5
Explanation: 
intention -> inention (remove 't')
inention -> enention (replace 'i' with 'e')
enention -> exention (replace 'n' with 'x')
exention -> exection (replace 'n' with 'c')
exection -> execution (insert 'u')
```



## Solution

二维动态规划。

设状态 f[i]\[j] 表示 word1[0:i-1] 和 word2[0:j-1] 之间所需的最小编辑距离。该距离只能从之前的子问题、以 4 种可能的“编辑方式”中的一种得来。该四种情况分别如下：

1. 已有  word1[0:i-2] 和 word2[0:j-2] 且word1[i-1] == word2[j-1]，那么：

   `f[i][j] = f[i-1][j-1]`

2. 否则，可能从“增加、删除、替换”三种方式得来，找编辑距离最小的一种：

   `f[i][j] = min(f[i-1][j-1], min(f[i-1][j], f[i][j-1])) + 1`

已得到状态转移方程。实现代码如下：

```cpp
//时间复杂度 O(n*m)，空间复杂度 O(n*m)
class Solution {
public:
    int minDistance(string word1, string word2) {
        const int n = word1.size();
        const int m = word2.size();
        int f[n+1][m+1];
        for (int i = 0; i <= n; i++)
            f[i][0] = i;  //need to delete i character
        for (int i = 0; i <= m; i++) 
            f[0][i] = i;  //need to add i character
        
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                if (word1[i-1] == word2[j-1])
                    f[i][j] = f[i-1][j-1];
                else {
                    f[i][j] = min(f[i-1][j-1], min(f[i-1][j], f[i][j-1])) + 1;
                }
            }
        }
        
        return f[n][m];
    }
};
//Runtime: 8 ms
```

也可以二维动态规划 + 滚动数组，此时时间复杂度 `O(n*m)`，空间复杂度 `O(n)`。

没有自己实现，leetcode上的示例代码如下：

```cpp
//sample 4 ms submission
class Solution {
public:
    int minDistance(string word1, string word2) {
        size_t len1 = word1.size();
        size_t len2 = word2.size();
        vector<int> dp(len1+1, 0);
        int pre, tmp;
        if (len1 == 0)
            return len2;
        for (int i = 1; i <= len1; i++)
            dp[i] = i;
        for (int j = 1; j <= len2; j++) {
            pre = dp[0];
            dp[0] = j;
            for (int i = 1; i <= len1; i++) {
                tmp = dp[i];
                if (word1[i-1] == word2[j-1]) {
                    dp[i] = pre;
                }
                else
                    dp[i] = min(dp[i-1] + 1, min(dp[i] + 1, pre + 1));
                pre = tmp;
            }
        }
        return dp[len1];
    }
};
```



## Debug&Learning



