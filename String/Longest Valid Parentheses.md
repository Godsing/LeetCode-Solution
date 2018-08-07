## Problem

Given a string containing just the characters `'('` and `')'`, find the length of the longest valid (well-formed) parentheses substring.

**Example 1:**

```
Input: "(()"
Output: 2
Explanation: The longest valid parentheses substring is "()"
```

**Example 2:**

```
Input: ")()())"
Output: 4
Explanation: The longest valid parentheses substring is "()()"
```



## Solution

思路：

使用栈，可以做到时间复杂度为 O(n) 。

栈中保存的元素是字符和下标。map 保存的是（右括号的下标、符合格式的最左括号的下标）对。

过程：



对于右括号：

```cpp
class Solution {
public:
    int longestValidParentheses(string s) {
        if (s.empty()) return 0;
        stack<pair<char, int> > st;
        unordered_map<int, int> dict;
        int res = 0;
        for (int i = 0; i < s.size(); i++) {
            //对于左括号，直接压入栈
            if (s[i] == '(') st.push(make_pair('(', i));
            else {
                //如果栈为空，则无法匹配相应的左括号，跳过；
                if (st.empty()) continue;
                //否则，栈顶必然是左括号（因为没法匹配的右括号都跳过了，不会有多余的右括号），这时候取栈顶元素
                auto p = st.top();
                st.pop();
                //当前右括号所匹配的左括号的位置
                int left = p.second;
                //查看左括号的紧邻左侧是否有符合格式的子字符串
                if (dict.count(left-1)) left = dict[left-1];
                dict.insert({i, left});
                res = max(res, i - left + 1);
            }
        }
        return res;
    }
};
//Runtime: 8 ms
```

发现栈中保存字符是没必要的，因此改成栈只保存下标，如下：

```cpp
class Solution {
public:
    int longestValidParentheses(string s) {
        if (s.empty()) return 0;
        stack<int> st;
        unordered_map<int, int> dict;
        int res = 0;
        for (int i = 0; i < s.size(); i++) {
            if (s[i] == '(') st.push(i);
            else {
                if (st.empty()) continue;
                int t = st.top();
                st.pop();
                if (dict.count(t-1)) t = dict[t-1];
                dict.insert({i, t});
                res = max(res, i - t + 1);
            }
        }
        return res;
    }
};
//Runtime: 12 ms
```

运行速度居然更慢了。

---

【其他参考方法】

- 方法一：[My O(n) solution using a stack](https://leetcode.com/problems/longest-valid-parentheses/discuss/14126/My-O(n)-solution-using-a-stack?page=4) 

```cpp
class Solution {
public:
    int longestValidParentheses(string s) {
        int n = s.length(), longest = 0;
        stack<int> st;
        for (int i = 0; i < n; i++) {
            if (s[i] == '(') st.push(i);
            else {
                if (!st.empty()) {
                    if (s[st.top()] == '(') st.pop();
                    else st.push(i);
                }
                else st.push(i);
            }
        }
        if (st.empty()) longest = n;
        else {
            int a = n, b = 0;
            while (!st.empty()) {
                b = st.top(); st.pop();
                longest = max(longest, a-b-1);
                a = b;
            }
            longest = max(longest, a);
        }
        return longest;
    }
};
```

The workflow of the solution is as below.

1. Scan the string from beginning to end.
2. If current character is '(',
   push its index to the stack. If current character is ')' and the
   character at the index of the top of stack is '(', we just find a
   matching pair so pop from the stack. Otherwise, we push the index of
   ')' to the stack.
3. After the scan is done, the stack will only
   contain the indices of characters which cannot be matched. Then
   let's use the opposite side - substring between adjacent indices
   should be valid parentheses.
4. If the stack is empty, the whole input
   string is valid. Otherwise, we can scan the stack to get longest
   valid substring as described in step 3.



- 方法二：上面的方法所在帖子下的评论 [DP solution](https://leetcode.com/problems/longest-valid-parentheses/discuss/14126/My-O(n)-solution-using-a-stack/14473) ，来自 [dennyrong](https://leetcode.com/dennyrong) 。

This is my DP solution, just one pass

V[i] represents number of valid parentheses matches from S[j to i] (j<i)

V[i] = V[i-1] + 2 + previous matches V[i- (V[i-1] + 2) ] if S[i] = ')' and '(' count > 0

```java
public int longestValidParentheses(String s) {
    char[] S = s.toCharArray();
    int[] V = new int[S.length];
    int open = 0;
    int max = 0;
    for (int i=0; i<S.length; i++) {
        if (S[i] == '(') open++;
        if (S[i] == ')' && open > 0) {
            // matches found
            V[i] = 2+ V[i-1];
            // add matches from previous
            if(i-V[i]>0)
                V[i] += V[i-V[i]];
            open--;
        }
        if (V[i] > max) max = V[i];
    }
    return max;
}
```