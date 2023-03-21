## 题目

设计一个 map ，满足以下几点:

- 字符串表示键，整数表示值
- 返回具有前缀等于给定字符串的键的值的总和

实现一个 `MapSum` 类：

- `MapSum()` 初始化 `MapSum` 对象
- `void insert(String key, int val)` 插入 `key-val` 键值对，字符串表示键 `key` ，整数表示值 `val` 。如果键 `key` 已经存在，那么原来的键值对 `key-value` 将被替代成新的键值对。
- `int sum(string prefix)` 返回所有以该前缀 `prefix` 开头的键 `key` 的值的总和。

 

**示例 1：**

```
输入：
["MapSum", "insert", "sum", "insert", "sum"]
[[], ["apple", 3], ["ap"], ["app", 2], ["ap"]]
输出：
[null, null, 3, null, 5]

解释：
MapSum mapSum = new MapSum();
mapSum.insert("apple", 3);  
mapSum.sum("ap");           // 返回 3 (apple = 3)
mapSum.insert("app", 2);    
mapSum.sum("ap");           // 返回 5 (apple + app = 3 + 2 = 5)
```

 

**提示：**

- `1 <= key.length, prefix.length <= 50`
- `key` 和 `prefix` 仅由小写英文字母组成
- `1 <= val <= 1000`
- 最多调用 `50` 次 `insert` 和 `sum`



注意：本题与主站 677 题相同： https://leetcode-cn.com/problems/map-sum-pairs/



## 题目

```c++
class Trie {
public:
    unordered_map<char, Trie*> children;  //本题由于字符区间比较小(仅限于小写英文字母)，所以其实可以用数组代替哈希表
    bool is_leaf = false;

    /** Initialize your data structure here. */
    Trie() {

    }
    
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
};

class MapSum {
private:
    Trie* trie;
    unordered_map<string, int> m;
public:
    /** Initialize your data structure here. */
    MapSum() {
        trie = new Trie();
    }
    
    void insert(string key, int val) {
        trie->insert(key);
        m[key] = val;
    }
    
    int sum(string prefix) {
        Trie* node = find_last_node(prefix);
        if (!node) return 0;
        int res = 0;
        sum_of_node(node, prefix, res);
        return res;
    }

    Trie* find_last_node(string prefix) {
        Trie* node = trie;
        for (char ch : prefix) {
            // if (node->children[ch]) node = node->children[ch];
            if (node->children.count(ch)) node = node->children[ch];
            else return nullptr;
        }
        return node;
    }

    void sum_of_node(Trie* node, string& word, int& res) {
        if (node->is_leaf) res += m[word];
        for (auto it = node->children.begin(); it != node->children.end(); it++) {
            word.push_back(it->first);
            sum_of_node(it->second, word, res);
            word.pop_back();
        }
    }
};

/**
 * Your MapSum object will be instantiated and called as such:
 * MapSum* obj = new MapSum();
 * obj->insert(key,val);
 * int param_2 = obj->sum(prefix);
 */
```

