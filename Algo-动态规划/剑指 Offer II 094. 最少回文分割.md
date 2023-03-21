## 题目

给你一个字符串 `s`，请你将 `s` 分割成一些子串，使每个子串都是回文。

返回符合要求的 **最少分割次数** 。

 

**示例 1：**

```
输入：s = "aab"
输出：1
解释：只需一次分割就可将 s 分割成 ["aa","b"] 这样两个回文子串。
```

**示例 2：**

```
输入：s = "a"
输出：0
```

**示例 3：**

```
输入：s = "ab"
输出：1
```

 

**提示：**

- `1 <= s.length <= 2000`
- `s` 仅由小写英文字母组成



注意：本题与主站 132 题相同： https://leetcode-cn.com/problems/palindrome-partitioning-ii/



来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/omKAoA



## 题解

### 解法一：先记录回文子串，再 DP 递推求解

- 实现方法一：

  ```c++
  class Solution {
  public:
      int minCut(string s) {
          vector<vector<bool>> mem(s.size(), vector<bool>(s.size(), false));
          // 记录回文子串
          int cenL = 0, cenR = 0;
          while (cenR < s.size()) {
              // 从种子子串开始向两边扩展开，直到不能再扩展(不再是回文子串)，这样便可求得以当前种子子串作为中点的所有回文子串
              int left = cenL, right = cenR;
              while (left >= 0 && right < s.size() && s[left] == s[right]) mem[left--][right++] = true;
              cenR > cenL ? cenL++ : cenR++;  // 向右并步走：先迈右脚，并入左脚，再迈右脚... 这样可以遍历所有的长度为 1 和 2 的子串，作为种子
          }
  
          vector<int> dp(s.size(), 0);  // 以索引 i 结尾的 s 的子字符串需要的最少分割次数
          for (int i = 0; i < s.size(); ++i) {
              if (mem[0][i]) continue;
              dp[i] = i;  // dp[i] 初始化为 s[0] ~ s[i] 的最大切割次数，因为有 i+1 个数，所以需要切 i 次
              for (int j = 1; j <= i; j++) {
                  if (mem[j][i]) {
                      dp[i] = min(dp[i], dp[j - 1] + 1);
                  }
              }
          }
  
          return dp.back();
      }
  };
  ```

- 实现方法二：主要区别在于，方法二求解回文子串不是用“中心扩展法”，而是用“长度递增法”，这种方法性能上也较差，因为做了很多不必要的遍历。

  ```c++
  class Solution {
  public:
      int minCut(string s) {
          vector<vector<bool>> mem(s.size(), vector<bool>(s.size(), false));
          for (int len = 1; len <= s.size(); len++) {
              for (int i = 0; i < s.size() - len + 1; i++) {
                  mem[i][i+len-1] = bool(s[i] == s[i+len-1] && (len < 3 || mem[i+1][i+len-2]));
              }
          }
  
          vector<int> dp(s.size(), 0);  // 以索引 i 结尾的 s 的子字符串需要的最少分割次数
          for (int i = 0; i < s.size(); ++i) {
              if (mem[0][i]) continue;
              dp[i] = i;  // dp[i] 初始化为 s[0] ~ s[i] 的最大切割次数，因为有 i+1 个数，所以需要切 i 次
              for (int j = 1; j <= i; j++) {
                  if (mem[j][i]) {
                      dp[i] = min(dp[i], dp[j - 1] + 1);
                  }
              }
          }
  
          return dp.back();
      }
  };
  ```

  

### 解法二：回文子串判断和 DP 递推同时进行

参考《[132. 分割回文串 II](./132. 分割回文串 II.md)》

