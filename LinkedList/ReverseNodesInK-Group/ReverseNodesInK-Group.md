## Problem

Given a linked list, reverse the nodes of a linked list *k* at a time and return its modified list.

*k* is a positive integer and is less than or equal to the length of the linked list. If the number of nodes is not a multiple of *k* then left-out nodes in the end should remain as it is.


**Example:**

Given this linked list: `1->2->3->4->5`

For *k* = 2, you should return: `2->1->4->3->5`

For *k* = 3, you should return: `3->2->1->4->5`

**Note:**

- Only constant extra memory is allowed.
- You may not alter the values in the list's nodes, only nodes itself may be changed.

该题目的题干有问题：*k* is a positive integer and is less than or equal to the length of the linked list. 这句话在测试样例中并不成立。如果成立，显然输入的数据应该是 head != NULL 必然成立，而且 k 不会超过链表长度。所以我就按照默认输入会满足该条件去实现。然而在我实际提交的时候，第一次报错是因为输入了 `[] 2` ，head == NULL 且 k 超过链表长度。第二次有报错，是因为测试样例输入了 `[1, 2] 3` ，k 超过链表长度。



## Solution



```cpp

```









## Debug&Learning



