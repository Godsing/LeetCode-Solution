## 题目

给定两个字符串 s 和 p，找到 s 中所有 p 的 变位词 的子串，返回这些子串的起始索引。不考虑答案输出的顺序。

变位词 指字母相同，但排列不同的字符串。

 

示例 1:

```
输入: s = "cbaebabacd", p = "abc"
输出: [0,6]
解释:
起始索引等于 0 的子串是 "cba", 它是 "abc" 的变位词。
起始索引等于 6 的子串是 "bac", 它是 "abc" 的变位词。
```

示例 2:

```
输入: s = "abab", p = "ab"
输出: [0,1,2]
解释:
起始索引等于 0 的子串是 "ab", 它是 "ab" 的变位词。
起始索引等于 1 的子串是 "ba", 它是 "ab" 的变位词。
起始索引等于 2 的子串是 "ab", 它是 "ab" 的变位词。
```

**提示:**

- `1 <= s.length, p.length <= 3 * 10^4`
- `s` 和 `p` 仅包含小写字母



注意：本题与主站 438 题相同： https://leetcode-cn.com/problems/find-all-anagrams-in-a-string/



## 题解

```c++
class Solution {
public:
    vector<int> findAnagrams(string s, string p) {
        // result
        vector<int> res;
        // current status
        unordered_map<char, int> req;
        for (char ch: p) req[ch]++;
        int cnt = 0;
        // target status
        int target = req.size();
        // points
        int l = 0, r = 0;
        // sliding window
        while (r < s.size()) {
            // move r
            char chr = s[r++];
            // update current status
            req[chr]--;
            if (req[chr] == 0) cnt++;
            // judge if find an solution
            if (cnt == target) res.push_back(l);
            while (r - l >= p.size()) {
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

