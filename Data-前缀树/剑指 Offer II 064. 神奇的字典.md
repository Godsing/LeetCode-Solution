## 题目

设计一个使用单词列表进行初始化的数据结构，单词列表中的单词 **互不相同** 。 如果给出一个单词，请判定能否只将这个单词中**一个**字母换成另一个字母，使得所形成的新单词存在于你构建的字典中。

实现 `MagicDictionary` 类：

- `MagicDictionary()` 初始化对象
- `void buildDict(String[] dictionary)` 使用字符串数组 `dictionary` 设定该数据结构，`dictionary` 中的字符串互不相同
- `bool search(String searchWord)` 给定一个字符串 `searchWord` ，判定能否只将字符串中 **一个** 字母换成另一个字母，使得所形成的新字符串能够与字典中的任一字符串匹配。如果可以，返回 `true` ；否则，返回 `false` 。

 

**示例：**

```
输入
["MagicDictionary", "buildDict", "search", "search", "search", "search"]
[[], [["hello", "leetcode"]], ["hello"], ["hhllo"], ["hell"], ["leetcoded"]]
输出
[null, null, false, true, false, false]

解释
MagicDictionary magicDictionary = new MagicDictionary();
magicDictionary.buildDict(["hello", "leetcode"]);
magicDictionary.search("hello"); // 返回 False
magicDictionary.search("hhllo"); // 将第二个 'h' 替换为 'e' 可以匹配 "hello" ，所以返回 True
magicDictionary.search("hell"); // 返回 False
magicDictionary.search("leetcoded"); // 返回 False
```

 

**提示：**

- `1 <= dictionary.length <= 100`
- `1 <= dictionary[i].length <= 100`
- `dictionary[i]` 仅由小写英文字母组成
- `dictionary` 中的所有字符串 **互不相同**
- `1 <= searchWord.length <= 100`
- `searchWord` 仅由小写英文字母组成
- `buildDict` 仅在 `search` 之前调用一次
- 最多调用 `100` 次 `search`



注意：本题与主站 676 题相同： https://leetcode-cn.com/problems/implement-magic-dictionary/



来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/US1pGT

## 题解

方法一：使用前缀树

```c++
class Trie {
public:
    unordered_map<char, Trie*> children;  //本题由于字符区间比较小(仅限于小写英文字母)，所以其实可以用数组代替哈希表
    bool is_leaf;
    /** Initialize your data structure here. */
    Trie() : is_leaf(false) {}

    /** Inserts a word into the trie. */
    void insert(string word) {
        Trie* node = this;
        for (char ch : word) {
            if (node->children[ch] == nullptr)
                node->children[ch] = new Trie();
            node = node->children[ch];
        }
        node->is_leaf = true;
    }

    bool is_end() {
        return this->is_leaf;
    }
};

class MagicDictionary {
private:
    Trie* trie;
public:
    /** Initialize your data structure here. */
    MagicDictionary() {
        trie = new Trie();
    }

    void buildDict(vector<string> dictionary) {
        for (string s : dictionary) trie->insert(s);
    }

    bool dfs(Trie* node, const string& s, int i, int cnt) {
        if (i == s.size()) return (cnt == 1) && node->is_end();
        if (node->children.count(s[i])) {
            // node = node->children[s[i]];  // 注意不能这么写
            if (dfs(node->children[s[i]], s, i+1, cnt)) {
            return true;}
        }
        if (cnt > 0) return false;
        for (auto it = node->children.begin(); it != node->children.end(); it++) {
            if (it->first == s[i]) continue;
            if (dfs(it->second, s, i+1, cnt+1)) return true;
        }
        return false;
    }

    bool search(string searchWord) {
        return dfs(trie, searchWord, 0, 0);
    }
};

/**
 * Your MagicDictionary object will be instantiated and called as such:
 * MagicDictionary* obj = new MagicDictionary();
 * obj->buildDict(dictionary);
 * bool param_2 = obj->search(searchWord);
 */
```

另一种方法：使用集合就行了，参考[这里](https://leetcode-cn.com/problems/US1pGT/solution/offerii064shen-qi-de-zi-dian-by-logilong-4hmn/)。这个题解里，对广义邻居进行了计数，实际上是没必要的，只需要判断输入的词是否在词典中即可排除原文重复的情况。

