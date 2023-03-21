## 题目

序列化是将一个数据结构或者对象转换为连续的比特位的操作，进而可以将转换后的数据存储在一个文件或者内存中，同时也可以通过网络传输到另一个计算机环境，采取相反方式重构得到原数据。

请设计一个算法来实现二叉树的序列化与反序列化。这里不限定你的序列 / 反序列化算法执行逻辑，你只需要保证一个二叉树可以被序列化为一个字符串并且将这个字符串反序列化为原始的树结构。

**提示:** 输入输出格式与 LeetCode 目前使用的方式一致，详情请参阅 [LeetCode 序列化二叉树的格式](vscode-webview://034d5984-a812-4e2e-972a-7a53c888085b/faq/#binary-tree)。你并非必须采取这种方式，你也可以采用其他的方法解决这个问题。

 

**示例 1：**

![img](https://mdpicbed.oss-cn-hongkong.aliyuncs.com/imgs/serdeser.jpg)

```
输入：root = [1,2,3,null,null,4,5]
输出：[1,2,3,null,null,4,5]
```

**示例 2：**

```
输入：root = []
输出：[]
```

**示例 3：**

```
输入：root = [1]
输出：[1]
```

**示例 4：**

```
输入：root = [1,2]
输出：[1,2]
```

 

**提示：**

- 树中结点数在范围 `[0, 104]` 内
- `-1000 <= Node.val <= 1000`



注意：本题与主站 297 题相同：https://leetcode-cn.com/problems/serialize-and-deserialize-binary-tree/ 



来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/h54YBf



## 题解

先序遍历，并且对每个缺少孩子的节点，都用空节点补足（使其有两个孩子）。这些空节点，在反序列化时十分重要，它们提示了何时该返回。

```c++
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Codec {
public:
    void serialzie_core(TreeNode* root, string& str) {
        if (!root) {
            str += ',';
            return;
        }
        str += to_string(root->val) + ',';
        serialzie_core(root->left, str);
        serialzie_core(root->right, str);
    }

    // Encodes a tree to a single string.
    string serialize(TreeNode* root) {
        string res;
        serialzie_core(root, res);
        return res;
    }

    TreeNode* deserialize_core(queue<string>& vals) {
        if (vals.front() == "None") {
            vals.pop();
            return nullptr;
        }
        auto node = new TreeNode(stoi(vals.front()));
        vals.pop();
        node->left = deserialize_core(vals);
        node->right = deserialize_core(vals);
        return node;
    }

    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data) {
        queue<string> vals;
        string val;
        for (char ch : data) {
            if (ch == ',') {
                if (!val.empty()) vals.push(val);
                else vals.push("None");
                val.clear();
            } else {
                val.push_back(ch);
            }
        }
        return deserialize_core(vals);
    }
};

// Your Codec object will be instantiated and called as such:
// Codec ser, deser;
// TreeNode* ans = deser.deserialize(ser.serialize(root));
```

