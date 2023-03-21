## 题目

给你一个字符串 `s` ，请你统计并返回这个字符串中 **回文子串** 的数目。

**回文字符串** 是正着读和倒过来读一样的字符串。

**子字符串** 是字符串中的由连续字符组成的一个序列。

具有不同开始位置或结束位置的子串，即使是由相同的字符组成，也会被视作不同的子串。

 

**示例 1：**

```
输入：s = "abc"
输出：3
解释：三个回文子串: "a", "b", "c"
```

**示例 2：**

```
输入：s = "aaa"
输出：6
解释：6个回文子串: "a", "a", "a", "aa", "aa", "aaa"
```

 

**提示：**

- `1 <= s.length <= 1000`
- `s` 由小写英文字母组成



注意：本题与主站 647 题相同：https://leetcode-cn.com/problems/palindromic-substrings/ 

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/a7VOhD
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。



## 题解

本应用一个矩阵，来保存任意两个索引位置之间的子字符串是否为回文串。但我们可以进行简化，并用“求余”的方式来实现循环。

具体地，用三个数组，分别用来保存每个索引位置作为起点的 “长度减2”、“长度减1”以及“当前长度”的子字符串是否为回文串。

```c++
class Solution {
public:
    int countSubstrings(string s) {
        int res = s.size();
        vector<vector<bool>> dp(3, vector<bool>(s.size(), true));
        for (int len = 2; len <= s.size(); len++) {  //注意：<= 别写成了 <
            for (int l = 0; l <= s.size() - len; l++) {
                int r = l + len - 1;
                if (s[l] == s[r] && dp[(len-2)%3][l+1]) {
                    res++;
                    dp[len%3][l] = true;
                } else dp[len%3][l] = false;
            }
        }
        return res;
    }
};
```

