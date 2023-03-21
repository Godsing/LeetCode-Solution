## 题目

字典 `wordList` 中从单词 `beginWord` 和 `endWord` 的 **转换序列** 是一个按下述规格形成的序列 `beginWord -> s1 -> s2 -> ... -> sk`：

- 每一对相邻的单词只差一个字母。
-  对于 `1 <= i <= k` 时，每个 `si` 都在 `wordList` 中。注意， `beginWord` 不需要在 `wordList` 中。
- `sk == endWord`

给你两个单词 `beginWord` 和 `endWord` 和一个字典 `wordList` ，返回 *从 `beginWord` 到 `endWord` 的 **最短转换序列** 中的 **单词数目*** 。如果不存在这样的转换序列，返回 `0` 。

 

**示例 1：**

```
输入：beginWord = "hit", endWord = "cog", wordList = ["hot","dot","dog","lot","log","cog"]
输出：5
解释：一个最短转换序列是 "hit" -> "hot" -> "dot" -> "dog" -> "cog", 返回它的长度 5。
```

**示例 2：**

```
输入：beginWord = "hit", endWord = "cog", wordList = ["hot","dot","dog","lot","log"]
输出：0
解释：endWord "cog" 不在字典中，所以无法进行转换。
```

 

**提示：**

- `1 <= beginWord.length <= 10`
- `endWord.length == beginWord.length`
- `1 <= wordList.length <= 5000`
- `wordList[i].length == beginWord.length`
- `beginWord`、`endWord` 和 `wordList[i]` 由小写英文字母组成
- `beginWord != endWord`
- `wordList` 中的所有字符串 **互不相同**



注意：本题与主站 127 题相同： https://leetcode-cn.com/problems/word-ladder/



## 题解

```c++
class Solution {
public:
    int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
        unordered_set<string> remain(wordList.begin(), wordList.end()), begin_set({beginWord}), end_set({endWord});
        if (remain.find(endWord) == remain.end()) return 0;
        else remain.erase(endWord);
        int ladder = 2;
        while (!begin_set.empty() && !end_set.empty()) {
            if (begin_set.size() > end_set.size()) begin_set.swap(end_set);
            unordered_set<string> next_level;
            for (string w : begin_set) {
                for (int i = 0; i < w.size(); i++) {
                    char c = w[i];
                    for (int j = 0; j < 26; j++) {
                        w[i] = 'a' + j;
                        if (end_set.find(w) != end_set.end()) return ladder;
                        if (remain.find(w) != remain.end()) {
                            next_level.insert(w);
                            remain.erase(w);
                        }
                    }
                    w[i] = c;
                }
            }
            begin_set.swap(next_level);
            ladder++;
        }
        return 0;
    }
};
```

