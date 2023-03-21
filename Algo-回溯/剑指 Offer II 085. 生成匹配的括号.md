## 题目

数字 `n` 代表生成括号的对数，请你设计一个函数，用于能够生成所有可能的并且 **有效的** 括号组合。

 

**示例 1：**

```
输入：n = 3
输出：["((()))","(()())","(())()","()(())","()()()"]
```

**示例 2：**

```
输入：n = 1
输出：["()"]
```

 

**提示：**

- `1 <= n <= 8`



注意：本题与主站 22 题相同： https://leetcode-cn.com/problems/generate-parentheses/



## 题解

```c++
class Solution {
public:
    vector<string> generateParenthesis(int n) {
        vector<string> res;
        string path;
        backtracking(0, 0, n, path, res);
        return res;
    }

    void backtracking(int cntl, int cntr, int n, string& path, vector<string>& res) {
        if (cntl == n && cntr == n) res.emplace_back(path);
        if (cntl < n) {  // 左括号还没用完
            path.push_back('(');
            backtracking(cntl+1, cntr, n, path, res);
            path.pop_back();
        }
        if (cntl > cntr) {  // 右括号少于左括号
            path.push_back(')');
            backtracking(cntl, cntr+1, n, path, res);
            path.pop_back();
        }
    }
};
```

