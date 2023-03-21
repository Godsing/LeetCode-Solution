## 题目

单词数组 `words` 的 **有效编码** 由任意助记字符串 `s` 和下标数组 `indices` 组成，且满足：

- `words.length == indices.length`
- 助记字符串 `s` 以 `'#'` 字符结尾
- 对于每个下标 `indices[i]` ，`s` 的一个从 `indices[i]` 开始、到下一个 `'#'` 字符结束（但不包括 `'#'`）的 **子字符串** 恰好与 `words[i]` 相等

给你一个单词数组 `words` ，返回成功对 `words` 进行编码的最小助记字符串 `s` 的长度 。

 

**示例 1：**

```
输入：words = ["time", "me", "bell"]
输出：10
解释：一组有效编码为 s = "time#bell#" 和 indices = [0, 2, 5] 。
words[0] = "time" ，s 开始于 indices[0] = 0 到下一个 '#' 结束的子字符串，如加粗部分所示 "time#bell#"
words[1] = "me" ，s 开始于 indices[1] = 2 到下一个 '#' 结束的子字符串，如加粗部分所示 "time#bell#"
words[2] = "bell" ，s 开始于 indices[2] = 5 到下一个 '#' 结束的子字符串，如加粗部分所示 "time#bell#"
```

**示例 2：**

```
输入：words = ["t"]
输出：2
解释：一组有效编码为 s = "t#" 和 indices = [0] 。
```

 

**提示：**

- `1 <= words.length <= 2000`
- `1 <= words[i].length <= 7`
- `words[i]` 仅由小写字母组成



注意：本题与主站 820 题相同： https://leetcode-cn.com/problems/short-encoding-of-words/



## 题解

```c++
class Trie {
private:
    unordered_map<char, Trie*> children;
    // bool is_leaf;

public:
    Trie() {}

    void insert_inv(string word) {
        Trie* node = this;
        for (int i = word.size() - 1; i >= 0; i--) {
            char ch = word[i];
            if (!node->children[ch]) node->children[ch] = new Trie();
            node = node->children[ch];
        }
        // node->is_leaf = true;
    }

    int encoding_length() {
        int res = 0;
        dfs(this, 0, res);
        return res;
    }

    void dfs(Trie* node, int depth, int& res) {
        if (node->children.empty()) {
            res += (depth + 1);
            return ;
        }
        for (auto it = node->children.begin(); it != node->children.end(); it++) {
            dfs(it->second, depth+1, res);
        }
    }
};
class Solution {
public:
    int minimumLengthEncoding(vector<string>& words) {
        Trie* trie = new Trie();
        for (string word : words) trie->insert_inv(word);
        return trie->encoding_length();
    }
};
```

