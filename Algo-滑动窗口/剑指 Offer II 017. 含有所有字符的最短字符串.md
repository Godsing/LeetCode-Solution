## 题目

给你一个字符串 `s` 、一个字符串 `t` 。返回 `s` 中涵盖 `t` 所有字符的最小子串。如果 `s` 中不存在涵盖 `t` 所有字符的子串，则返回空字符串 `""` 。

 

**注意：**

- 对于 `t` 中重复字符，我们寻找的子字符串中该字符数量必须不少于 `t` 中该字符数量。
- 如果 `s` 中存在这样的子串，我们保证它是唯一的答案。

 

**示例 1：**

```
输入：s = "ADOBECODEBANC", t = "ABC"
输出："BANC"
```

**示例 2：**

```
输入：s = "a", t = "a"
输出："a"
```

**示例 3:**

```
输入: s = "a", t = "aa"
输出: ""
解释: t 中两个字符 'a' 均应包含在 s 的子串中，
因此没有符合条件的子字符串，返回空字符串。
```

 

**提示：**

- `1 <= s.length, t.length <= 10^5`
- `s` 和 `t` 由英文字母组成



注意：本题与主站 76 题相似（本题答案不唯一）：https://leetcode-cn.com/problems/minimum-window-substring/

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/M1oyTv
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。



## 题解

```c++
class Solution {
public:
    string minWindow(string s, string t) {  // 思路：滑动窗口
        // result
        string res;
        // current status
        unordered_map<char, int> req;
        for (char ch : t) req[ch]++;
        int cnt = 0;
        // target status
        int target = req.size();
        // points
        int l = 0, r = 0;
        while (r < s.size()) {
            // move r
            char chr = s[r++];
            // update current status
            req[chr]--;
            if (req[chr] == 0) cnt++;
            // while it is a possible solution
            while (cnt == target) {
                // update solution
                if (res.empty() || r-l < res.size()) res = s.substr(l, r-l);
                // move l
                char chl = s[l++];
                // update current status
                if (req[chl] == 0) cnt--;
                req[chl]++;
            }
        }
        return res;
    }
};
```

