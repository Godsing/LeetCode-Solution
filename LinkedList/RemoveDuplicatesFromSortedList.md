## Problem

Given a sorted linked list, delete all duplicates such that each element appear only *once*.

**Example 1:**

```
Input: 1->1->2
Output: 1->2
```

**Example 2:**

```
Input: 1->1->2->3->3
Output: 1->2->3
```





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
    ListNode* deleteDuplicates(ListNode* head) {
        if (!head || !head->next) return head;
        auto res = head, pre = head, tmp = head;
        head = head->next;
        while(head){
            if (pre->val == head->val) {
                tmp = head;
                head = head->next;
                pre->next = head;
                free(tmp);  //释放内存
            }else{
                pre = head;
                head = head->next;
            }
        }
        return res;
    }
};
```

