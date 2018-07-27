## Problem

Given a singly linked list, group all odd nodes together followed by the even nodes. Please note here we are talking about the node number and not the value in the nodes.

You should try to do it in place. The program should run in O(1) space complexity and O(nodes) time complexity.

**Example 1:**

```
Input: 1->2->3->4->5->NULL
Output: 1->3->5->2->4->NULL
```

**Example 2:**

```
Input: 2->1->3->5->6->4->7->NULL
Output: 2->3->6->7->1->5->4->NULL
```

**Note:**

- The relative order inside both the even and odd groups should remain as it was in the input.
- The first node is considered odd, the second node even and so on ...



## Solution

用两个指针 odd, even 分别把奇数和偶数位置的结点连接起来，再用一个 head2 缓存一下第二个结点的指针，很容易就实现了。

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
    ListNode* oddEvenList(ListNode* head) {
        if (head == NULL || head->next == NULL || head->next->next == NULL) return head; //冗余
        ListNode* head2 = head->next; 
        ListNode* odd = head;
        ListNode* even = head->next;
        while (even != NULL && even->next != NULL) {
            if (odd->next == even) {
                odd->next = even->next;
                odd = odd->next;
            } else {
                even->next = odd->next;
                even = even->next;
            }
        }
        odd->next = head2;
        return head;
    }
};
```

代码似乎可以再简洁一些，同时也可以去除冗余的 if...else... ，如下：

```c++
class Solution {
public:
    ListNode* oddEvenList(ListNode* head) {
        if (!head || !head->next) return head;
        // ListNode* head2 = head->next, odd = head, even = head->next;  //这么写会报错：invalid conversion from 'ListNode*' to 'int'
        auto head2 = head->next, odd = head, even = head->next;
        while (even && even->next) { //该条件可以保证odd，even分别能前进一步
            odd->next = even->next;
            odd = odd->next;
            even->next = odd->next;
            even = even->next;
        }
        odd->next = head2;
        return head;
    }
};
```

