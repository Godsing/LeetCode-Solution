## Problem

Given a linked list, remove the *n*-th node from the end of list and return its head.

**Example:**

```
Given linked list: 1->2->3->4->5, and n = 2.

After removing the second node from the end, the linked list becomes 1->2->3->5.
```

**Note:**

Given *n* will always be valid.

**Follow up:**

Could you do this in one pass?



## Solution

```cpp
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
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        if (!head) return head;
        //之所以增加一个结点，是为了应对输入为类似 [1] 1 的情况
        ListNode* pre = new ListNode(0);
        pre->next = head;
        auto res = pre, pos = head;
        for (int i = 0; i < n - 1; i++)
            pos = pos->next;
        while (pos->next) {
            pre = pre->next;
            pos = pos->next;
        }
        auto tmp = pre->next;
        pre->next = tmp->next;
        delete tmp;
        return res->next;
    }
};
//Runtime: 4 ms
```

