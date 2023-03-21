## 题目

请你设计并实现一个满足 [LRU (最近最少使用) 缓存](https://baike.baidu.com/item/LRU) 约束的数据结构。

实现 `LRUCache` 类：

- `LRUCache(int capacity)` 以 **正整数** 作为容量 `capacity` 初始化 LRU 缓存
- `int get(int key)` 如果关键字 `key` 存在于缓存中，则返回关键字的值，否则返回 `-1` 。
- `void put(int key, int value)` 如果关键字 `key` 已经存在，则变更其数据值 `value` ；如果不存在，则向缓存中插入该组 `key-value` 。如果插入操作导致关键字数量超过 `capacity` ，则应该 **逐出** 最久未使用的关键字。

函数 `get` 和 `put` 必须以 `O(1)` 的平均时间复杂度运行。

 

**示例：**

```
输入
["LRUCache", "put", "put", "get", "put", "get", "put", "get", "get", "get"]
[[2], [1, 1], [2, 2], [1], [3, 3], [2], [4, 4], [1], [3], [4]]
输出
[null, null, null, 1, null, -1, null, -1, 3, 4]

解释
LRUCache lRUCache = new LRUCache(2);
lRUCache.put(1, 1); // 缓存是 {1=1}
lRUCache.put(2, 2); // 缓存是 {1=1, 2=2}
lRUCache.get(1);    // 返回 1
lRUCache.put(3, 3); // 该操作会使得关键字 2 作废，缓存是 {1=1, 3=3}
lRUCache.get(2);    // 返回 -1 (未找到)
lRUCache.put(4, 4); // 该操作会使得关键字 1 作废，缓存是 {4=4, 3=3}
lRUCache.get(1);    // 返回 -1 (未找到)
lRUCache.get(3);    // 返回 3
lRUCache.get(4);    // 返回 4
```

 

**提示：**

- `1 <= capacity <= 3000`
- `0 <= key <= 10000`
- `0 <= value <= 10^5`
- 最多调用 `2 * 10^5` 次 `get` 和 `put`



注意：本题与主站 146 题相同：https://leetcode-cn.com/problems/lru-cache/ 



## 题解

```c++
class LRUCache {
private:
    struct ListNode {
        int key;
        int val;
        ListNode* next;
        ListNode* prev;
        ListNode(): key(0), val(0), next(nullptr), prev(nullptr) {}
        ListNode(int x, int y): key(x), val(y), prev(nullptr), next(nullptr) {}
        ListNode(int x, int y, ListNode* p, ListNode* n): key(x), val(y), prev(p), next(n) {}
    };
    int cap = 0;
    ListNode* head = new ListNode();
    ListNode* tail = new ListNode();
    unordered_map<int, ListNode*> key2node;

public:
    LRUCache(int capacity) {
        cap = capacity;
        head->next = tail;
        tail->prev = head;
    }
    
    int get(int key) {
        // O(1) 判断是否存在 --> 需要哈希
        if (!key2node.count(key)) return -1;
        // 如果存在，需要在 O(1) 时间复杂度内完成将 key 挪到(删除+插入)有序数据结构的开头
        ListNode* node = key2node[key];
        if (node->prev != head) {
            // 删除
            node->prev->next = node->next;
            node->next->prev = node->prev;
            // 重新插入到开头
            node->next = head->next;
            node->prev = head;
            head->next = node;
            node->next->prev = node;
        }
        return node->val;
    }
    
    void put(int key, int value) {
        // 需要在 O(1) 时间复杂度内完成插入（若超过容量，还需删除最后一个）
        // 别忘了判断是否已存在！
        if (key2node.count(key)) {
            // 删除节点
            ListNode* old = key2node[key];
            old->prev->next = old->next;
            old->next->prev = old->prev;
            // 删除映射表中的记录
            key2node.erase(old->key);
            delete old;  // 释放内存
            // 重新构造节点
            ListNode* node = new ListNode(key, value);
            // 插入到开头
            node->next = head->next;
            node->prev = head;
            head->next = node;
            node->next->prev = node;
            // 更新映射表
            key2node[key] = node;
            return ;  // 别忘了 return !!!
        }
        // 如果不存在，那么在插入前，要判断一下，是否有剩余空间
        if (key2node.size() >= cap) {
            // 删除末尾节点
            ListNode* d = tail->prev;
            d->prev->next = tail;
            tail->prev = d->prev;
            // 删除映射表中的记录
            key2node.erase(d->key);
            delete d;  // 释放内存
        }
        ListNode* node = new ListNode(key, value);
        // 插入到开头
        node->next = head->next;
        node->prev = head;
        head->next = node;
        node->next->prev = node;
        // 更新映射表
        key2node[key] = node;
        return ;
    }
};

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */
```

