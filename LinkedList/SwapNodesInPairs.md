## Problem

Given a linked list, swap every two adjacent nodes and return its head.

**Example:**

```
Given 1->2->3->4, you should return the list as 2->1->4->3.
```

**Note:**

- Your algorithm should use only constant extra space.
- You may **not** modify the values in the list's nodes, only nodes itself may be changed.



## Solution

1. 特殊情况直接返回；
2. 把要返回的 head 缓存起来；
3. 定义3个指针变量，分别指向每一个 pair 的两个，及其下一个；
4. 改变各个结点的指向即可。

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
    ListNode* swapPairs(ListNode* head) {
        if (!head || !head->next) return head;
        auto pre = head, pos = head->next, tmp = pos->next;
        head = pos;
        pos->next = pre;
        while(tmp && tmp->next){
            pre->next = tmp->next;
            pre = tmp;
            pos = tmp->next;
            tmp = pos->next;
            pos->next = pre;
        }
        pre->next = tmp;
        return head;
    }
};
//Runtime: 5 ms
```

