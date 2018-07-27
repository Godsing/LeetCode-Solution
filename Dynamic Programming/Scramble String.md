## Problem

Given a string *s1*, we may represent it as a binary tree by partitioning it to two non-empty substrings recursively.

Below is one possible representation of *s1* = `"great"`:

```
    great
   /    \
  gr    eat
 / \    /  \
g   r  e   at
           / \
          a   t
```

To scramble the string, we may choose any non-leaf node and swap its two children.

For example, if we choose the node `"gr"` and swap its two children, it produces a scrambled string `"rgeat"`.

```
    rgeat
   /    \
  rg    eat
 / \    /  \
r   g  e   at
           / \
          a   t
```

We say that `"rgeat"` is a scrambled string of `"great"`.

Similarly, if we continue to swap the children of nodes `"eat"` and `"at"`, it produces a scrambled string `"rgtae"`.

```
    rgtae
   /    \
  rg    tae
 / \    /  \
r   g  ta  e
       / \
      t   a
```

We say that `"rgtae"` is a scrambled string of `"great"`.

Given two strings *s1* and *s2* of the same length, determine if *s2* is a scrambled string of *s1*.

**Example 1:**

```
Input: s1 = "great", s2 = "rgeat"
Output: true
```

**Example 2:**

```
Input: s1 = "abcde", s2 = "caebd"
Output: false
```



## Solution

首先想到的是递归（即深搜），对两个string进行分割，然后比较四对字符串。代码虽然简单，但是复杂度比较高。有两种加速策略，一种是剪枝，提前返回；一种是加缓存，缓存中间结果，即memoization（翻译为记忆化搜索）。

剪枝可以五花八门，要充分观察，充分利用信息，找到能让节点提前返回的条件。例如，判断两个字符串是否互为scamble，至少要求每个字符在两个字符串中出现的次数要相等，如果不相等则返回false。

加缓存，可以用数组或HashMap。本题维数较高，用HashMap，map和unordered_map均可。

既然可以用记忆化搜索，这题也一定可以用动规。设状态为`f[n][i][j]`，表示长度为$n$，起点为 s1[i] 和起点为s2[j] 两个字符串是否互为 scramble，则状态转移方程为

```
f[n][i][j]} =  (f[k][i][j] && f[n-k][i+k][j+k]) 
            || (f[k][i][j+n-k] && f[n-k][i+k][j])
```

三维动态规划：

```cpp
class Solution {
public:
    bool isScramble(string s1, string s2) {
        if (s1.length() != s2.length()) return false;
        
        const int N = s1.length();
        //f[n][i][j] 表示长度为n，起点为 s1[i] 和 s2[j] 的两个字符串是否互为 scramble
        bool f[N+1][N][N];
        fill_n(&f[0][0][0], (N+1) * N * N, false);
        
        for (int i = 0; i < N; i++)
            for (int j = 0; j < N; j++)
                f[1][i][j] = s1[i] == s2[j];
        
        for (int n = 2; n <= N; ++n) {
            for (int i = 0; i+n <=N; i++) {
                for (int j = 0; j+n <= N; j++) {
                    for (int k = 1; k < n; k++) {
                        if ((f[k][i][j] && f[n-k][i+k][j+k]) || (f[k][i][j+n-k] && f[n-k][i+k][j])) {
                            f[n][i][j] = true;
                            break;
                        }
                    }
                }
            }
        }
        return f[N][0][0];
    }
};  
```

soulmachine/[leetcode](https://github.com/soulmachine/leetcode) 上提供了另外几种解法（递归+剪枝，备忘录法）。



## Debug&Learning



