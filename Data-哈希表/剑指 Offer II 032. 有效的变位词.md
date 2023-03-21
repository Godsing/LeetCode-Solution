## 题目

给定两个字符串 `*s*` 和 `*t*` ，编写一个函数来判断 `*t*` 是否是 `*s*` 的字母异位词。

**注意：**若 `*s*` 和 `*t*` 中每个字符出现的次数都相同，则称 `*s*` 和 `*t*` 互为字母异位词。

 

**示例 1:**

```
输入: s = "anagram", t = "nagaram"
输出: true
```

**示例 2:**

```
输入: s = "rat", t = "car"
输出: false
```

 

**提示:**

- `1 <= s.length, t.length <= 5 * 104`
- `s` 和 `t` 仅包含小写字母

 

**进阶:** 如果输入字符串包含 unicode 字符怎么办？你能否调整你的解法来应对这种情况？



注意：本题与主站 242 题相似（字母异位词定义不同）：https://leetcode-cn.com/problems/valid-anagram/

From: https://leetcode-cn.com/problems/dKk3P7/



## 题解

V1:

```c++
class Solution {
public:
    bool isAnagram(string s, string t) {
        if (s == t || s.size() != t.size()) return false;
        unordered_map<char, int> cnt;
        for (char ch : s) cnt[ch]++;
        for (char ch : t) {
            cnt[ch]--;
            if (cnt[ch] == 0) cnt.erase(ch);
        }
        return cnt.empty();
    }
};
```

V2:

```c++
class Solution {
public:
    bool isAnagram(string s, string t) {
        if (s == t || s.size() != t.size()) return false;
        unordered_map<char, int> cnt;
        for (char ch : s) cnt[ch]++;
        for (char ch : t) {
            if (cnt[ch] == 0) return false;
            cnt[ch]--;
        }
        return true;
    }
};
```

除了用哈希表，还可以用 vector 来充当哈希表。另外，先对字符串中的字符进行排序，然后再比较两个字符串，也是一种方法。