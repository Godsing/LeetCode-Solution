## 题目

给你两个字符串 `s1` 和 `s2` ，写一个函数来判断 `s2` 是否包含 `s1` 的排列。如果是，返回 `true` ；否则，返回 `false` 。

换句话说，`s1` 的排列之一是 `s2` 的 **子串** 。

 

**示例 1：**

```
输入：s1 = "ab" s2 = "eidbaooo"
输出：true
解释：s2 包含 s1 的排列之一 ("ba").
```

**示例 2：**

```
输入：s1= "ab" s2 = "eidboaoo"
输出：false
```

 

**提示：**

- `1 <= s1.length, s2.length <= 10^4`
- `s1` 和 `s2` 仅包含小写字母



注意：本题与主站 567 题相同： https://leetcode-cn.com/problems/permutation-in-string/



## 题解

参照《套路.md》，实现代码如下：

```c++
class Solution {
public:
    bool checkInclusion(string s1, string s2) {
        unordered_map<char, int> required;
        for (char ch : s1) required[ch]++;
        // 如果挪动指针时，直接在 required 上修改，那么需要一个 target 变量；如果是另起一个 unordered_map 变量 window，则可以不需要 target 变量
        int satisfied = 0, target = required.size(), left = 0, right = 0;
        while (right < s2.size()) {  // 挪动右指针
            char ch = s2[right];
            right++;
            // 窗口内添加数据时的处理，主要是 required, satisfied 等
            required[ch]--;
            if (required[ch] == 0) {  // 挪动右指针后，要判断满足条件的字母个数是否有变多
                satisfied++;  // 满足条件的字母个数
                if (satisfied == target) return true;  // 因为不是求最值，只需找到一个就可返回
            }
            while (right - left >= s1.size()) {  // 另一种挪动左指针的条件：长度超了
                char d = s2[left];
                left++;
                // 对称代码：窗口内删除数据时的处理
                if (required[d] == 0) satisfied--;  // 挪动左指针前，要判断满足条件的字母个数是否会变少
                required[d]++;
            }
        }
        return false;
    }
};
```

