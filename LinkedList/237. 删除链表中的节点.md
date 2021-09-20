## Problem

Delete Node in a Linked List

Write a function to delete a node (except the tail) in a singly linked list, given only access to that node.

Supposed the linked list is `1 -> 2 -> 3 -> 4` and you are given the third node with value `3`, the linked list should become `1 -> 2 -> 4` after calling your function.





## Solution

```c++
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    void deleteNode(ListNode* node) {
        ListNode* next_node = node->next;
        *node = *next_node;  // 注意：指针赋值不能是 node = next_node !!!
        delete next_node;  // 使用 free(next_node) 也可以
        next_node = nullptr;  // delete 只是释放了内存，仍然需要指针置空
    }
};
// 或者↓
class Solution {
public:
    void deleteNode(ListNode* node) {
        ListNode* next_node = node->next;
        node->val = next_node->val;
        node->next = next_node->next;
        delete next_node; 
        next_node = nullptr;
    }
};
```

