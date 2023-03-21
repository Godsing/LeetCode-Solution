## 题目

给你一个字符串 `s`，请你将 `s` 分割成一些子串，使每个子串都是 **回文串** 。返回 `s` 所有可能的分割方案。

**回文串** 是正着读和反着读都一样的字符串。

 

**示例 1：**

```
输入：s = "aab"
输出：[["a","a","b"],["aa","b"]]
```

**示例 2：**

```
输入：s = "a"
输出：[["a"]]
```

 

**提示：**

- `1 <= s.length <= 16`
- `s` 仅由小写英文字母组成



注意：本题与主站 131 题相同： https://leetcode-cn.com/problems/palindrome-partitioning/



## 题解

```c++
class Solution {
private:
    vector<vector<bool>> mem;
public:
    vector<vector<string>> partition(string s) {
        mem.resize(s.size(), vector<bool>(s.size(), false));  // 记住这种用法，参考《剑指 Offer II 013. 二维子矩阵的和》
        for (int len = 1; len <= s.size(); len++) {
            for (int i = 0; i < s.size() - len + 1; i++) {
                mem[i][i+len-1] = bool(s[i] == s[i+len-1] && (len < 3 || mem[i+1][i+len-2]));
            }
        }
        vector<string> path;
        vector<vector<string>> res;
        backtracking(s, 0, path, res);
        return res;
    }

    void backtracking(const string& s, int start, vector<string>& path, vector<vector<string>>& res) {
        if (start == s.size()) res.push_back(path);
        for (int end = start; end < s.size(); end++) {
            if (mem[start][end]) {  // 闭区间
                path.push_back(s.substr(start, end-start+1));
                backtracking(s, end+1, path, res);
                path.pop_back();
            }
        }
    }
};
```

