## 题目

在英语中，我们有一个叫做 `词根`(root) 的概念，可以词根**后面**添加其他一些词组成另一个较长的单词——我们称这个词为 `继承词`(successor)。例如，词根`an`，跟随着单词 `other`(其他)，可以形成新的单词 `another`(另一个)。

现在，给定一个由许多**词根**组成的词典 `dictionary` 和一个用空格分隔单词形成的句子 `sentence`。你需要将句子中的所有**继承词**用**词根**替换掉。如果**继承词**有许多可以形成它的**词根**，则用**最短**的词根替换它。

你需要输出替换之后的句子。

 

**示例 1：**

```
输入：dictionary = ["cat","bat","rat"], sentence = "the cattle was rattled by the battery"
输出："the cat was rat by the bat"
```

**示例 2：**

```
输入：dictionary = ["a","b","c"], sentence = "aadsfasf absbs bbab cadsfafs"
输出："a a b c"
```

 

**提示：**

- `1 <= dictionary.length <= 1000`
- `1 <= dictionary[i].length <= 100`
- `dictionary[i]` 仅由小写字母组成。
- `1 <= sentence.length <= 10^6`
- `sentence` 仅由小写字母和空格组成。
- `sentence` 中单词的总量在范围 `[1, 1000]` 内。
- `sentence` 中每个单词的长度在范围 `[1, 1000]` 内。
- `sentence` 中单词之间由一个空格隔开。
- `sentence` 没有前导或尾随空格。

 

## 题解

此题需要自行实现一个 Trie 树，并实现相应的匹配算法。

```c++
class Trie {
private:
    vector<Trie*> children;
    bool is_leaf;
public:
    Trie() : children(26), is_leaf(false) {}

    void insert(string word) {
        Trie* node = this;
        for (char ch : word) {
            int i = ch - 'a';
            if (!node->children[i]) node->children[i] = new Trie();
            node = node->children[i];
            if (node->is_leaf) return ;  // 由于本题只需要返回最短的词根，所以更长的词根也没意义
        }
        node->is_leaf = true;
    }

    string match_root(string word) {
        Trie* node = this;
        for (int i = 0; i < word.size(); i++) {
            int k = word[i] - 'a';
            if (node->children[k]) node = node->children[k];
            else break;
            if (node->is_leaf) return word.substr(0, i+1);
        }
        return "";
    }
};

class Solution {
public:
    string replaceWords(vector<string>& dictionary, string sentence) {
        Trie* trie = new Trie();
        for (string root : dictionary) trie->insert(root);

        string res = "";
        string word = "";
        for (int i = 0; i < sentence.size() + 1; i++) {
            if (i == sentence.size() || sentence[i] == ' ') {
                string root = trie->match_root(word);
                if (root.empty()) root = word;

                if (!res.empty()) res += ' ';
                res += root;

                word = "";
            } else word += sentence[i];
        }
        return res;
    }
};
```

