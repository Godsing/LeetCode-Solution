## 题目

给定一个字符串 `s` 和一个字符串 `t` ，计算在 `s` 的子序列中 `t` 出现的个数。

字符串的一个 **子序列** 是指，通过删除一些（也可以不删除）字符且不干扰剩余字符相对位置所组成的新字符串。（例如，`"ACE"` 是 `"ABCDE"` 的一个子序列，而 `"AEC"` 不是）

题目数据保证答案符合 32 位带符号整数范围。

 

**示例 1：**

```
输入：s = "rabbbit", t = "rabbit"
输出：3
解释：
如下图所示, 有 3 种可以从 s 中得到 "rabbit" 的方案。
rabbbit
rabbbit
rabbbit
```

**示例 2：**

```
输入：s = "babgbag", t = "bag"
输出：5
解释：
如下图所示, 有 5 种可以从 s 中得到 "bag" 的方案。 
babgbag
babgbag
babgbag
babgbag
babgbag
```

 

**提示：**

- `0 <= s.length, t.length <= 1000`
- `s` 和 `t` 由英文字母组成



注意：本题与主站 115 题相同： https://leetcode-cn.com/problems/distinct-subsequences/



## 题解

这道题目很烦人的一点是，保存中间结果的值总是溢出，由于题目说“题目数据保证答案符合 32 位带符号整数范围”，搞得我一度以为自己的代码哪里错了。

但是经过多组数据自测，发现都没有问题。最终灵光一现，想到即便最终结果符合 int 整数范围，但中间值还是可能会溢出啊！

所以，那就调大中间值的取值范围吧，于是我首先尝试调整成 long long 类型，本以为天衣无缝了，结果依然报错o(╥﹏╥)o

最后曲线救国的方法是：使用 `unsigned int` 类型，来避免溢出时报错。毕竟，这些溢出的值迟早也要被忽略掉，那就不管它的值对不对了，反正不报错就行。

```c++
class Solution {
public:
    int numDistinct(string s, string t) {
        if (s.size() < t.size()) return 0;
        vector<unsigned int> prev(s.size()+1, 1);  // 当前的 t 子字符串长度减 1 时，s 中每个位置作为子字符串结尾时对应的解
        vector<unsigned int> curr(s.size()+1, 0);  // 对于当前的 t 子字符串长度，s 中每个位置作为子字符串结尾时对应的解
        for (int i = 1; i <= t.size(); i++) {  // t 的第 i 个字符
            for (int j = 1; j <= s.size(); j++) {  // s 的第 j 个字符
                curr[j] = curr[j-1];
                if (j >= i && s[j-1] == t[i-1]) curr[j] += prev[j-1];
            }
            prev = curr;
        }
        return prev.back();
    }
};
```

