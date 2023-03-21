## 题目

给你一个字符串数组，请你将 **字母异位词** 组合在一起。可以按任意顺序返回结果列表。

**字母异位词** 是由重新排列源单词的字母得到的一个新单词，所有源单词中的字母通常恰好只用一次。

 

**示例 1:**

```
输入: strs = ["eat", "tea", "tan", "ate", "nat", "bat"]
输出: [["bat"],["nat","tan"],["ate","eat","tea"]]
```

**示例 2:**

```
输入: strs = [""]
输出: [[""]]
```

**示例 3:**

```
输入: strs = ["a"]
输出: [["a"]]
```

 

**提示：**

- `1 <= strs.length <= 10^4`
- `0 <= strs[i].length <= 100`
- `strs[i]` 仅包含小写字母



## 题解

为了快速地对比不同字符串是否为变位词，同时也是为了将同组变位词存储在同一个地方（进而想到如果用哈希表来存储，那么需要一个 key），所以决定采用排序的结果来作为同组变位词的唯一标识（这样既方便了变位词的判定，也方便作为 key 来使用），而不是通过哈希表的统计结果来判断。

即便是排序，在这里也有两种比较不错的算法可以采用：快速排序、桶排序。由于字符串全部由小写字母组成，只有 26 个可能的字符，通过桶排序可以实现 O(n) 的时间复杂度。但是由于这里字符串的长度较小（不超过100）、且平均意义上可以假定字符串长度约 50，因此桶排序在这里没有足够的优势，快速排序足以应付。

```c++
class Solution {
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        unordered_map<string, vector<string>> m;
        for (string s: strs) {
            string sortedWord = s;  // 复制一个，避免修改原来的字符串
            sort(sortedWord.begin(), sortedWord.end());  // 用排序结果来作为每组变位词的唯一标识
            m[sortedWord].push_back(s);
        }
        vector<vector<string>> res;
        for (auto it = m.begin(); it != m.end(); ++it) {
            res.push_back(it->second);
        }
        return res;
    }
};
```

