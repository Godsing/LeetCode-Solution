## 题目

给定一个非空字符串 `s`，**最多**删除一个字符。判断是否能成为回文字符串。

 

**示例 1:**

```
输入: s = "aba"
输出: true
```

**示例 2:**

```
输入: s = "abca"
输出: true
解释: 你可以删除c字符。
```

**示例 3:**

```
输入: s = "abc"
输出: false
```

 

**提示:**

- `1 <= s.length <= 10^5`
- `s` 由小写英文字母组成



注意：本题与主站 680 题相同： https://leetcode-cn.com/problems/valid-palindrome-ii/

From: https://leetcode-cn.com/problems/RQku0D/



## 题解

因为至多删除一个字符，那么当从两侧向中间逼近的过程中，如果遇到两个不相同的字符，那么必定需要删除其中之一（否则… 反证法可以证明）。因此，这也是一种贪心策略。为此，我们分两次使用双指针即可。

```c++
class Solution {
public:
    bool isPlaindrome(string s, int l, int r) {
        while (l < r) {
            if (s[l] != s[r]) return false;
            else {l++; r--;}
        }
        return true;
    }

    bool validPalindrome(string s) {
        int l = 0, r = s.size() - 1;
        while (l < r) {
            if (s[l] != s[r]) break;
            else {l++; r--;}
        }
        return l >= r || isPlaindrome(s, l+1, r) || isPlaindrome(s, l, r-1);
    }
};
```

