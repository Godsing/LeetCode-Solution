## 题目

给定一个字符串，验证它是否是回文串，只考虑字母和数字字符，可以忽略字母的大小写。

**说明：**本题中，我们将空字符串定义为有效的回文串。

 

**示例 1:**

```
输入: "A man, a plan, a canal: Panama"
输出: true
解释："amanaplanacanalpanama" 是回文串
```

**示例 2:**

```
输入: "race a car"
输出: false
解释："raceacar" 不是回文串
```

 

**提示：**

- `1 <= s.length <= 2 * 10^5`
- 字符串 `s` 由 ASCII 字符组成



From: https://leetcode-cn.com/problems/XltzEq/



## 题解

```c++
class Solution {
public:
    bool isValidChar(char ch) {
        return (ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z') || (ch >= '0' && ch <= '9');
    }

    char toLower(char ch) {
        if (ch >= 'A' && ch <= 'Z') return ch + ('a' - 'A');
        else return ch;
    }

    bool isPalindrome(string s) {  // 思路：双指针
        int l = 0, r = s.size()-1;
        while (l < r) {
            // find the first valid character from left to right
            while(l < s.size() && !isValidChar(s[l])) l++;  // 注意，需要检查边界
            // find the first valid character from right to left
            while(r >= 0 && !isValidChar(s[r])) r--;  // 注意，需要检查边界
            // check if equal (case insensitive)
            if (l < s.size() && r >= 0 && l < r) {  // 注意，还需要检查边界
                if (toLower(s[l]) == toLower(s[r])) {
                    l++; r--;
                } else return false;
            } // 无需 else，因为若 l < r 不满足，会直接跳出循环
        }
        return true;
    }
};
```

Python版本：

```python
class Solution:
    def isPalindrome(self, s: str) -> bool:
        import re
        s = re.sub(r'[^a-zA-Z0-9]', '', s)
        s = s.lower()
        s2 = s[::-1]
        return s == s2
```

