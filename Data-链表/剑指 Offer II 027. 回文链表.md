## 题目

给你一个单链表的头节点 `head` ，请你判断该链表是否为回文链表。如果是，返回 `true` ；否则，返回 `false` 。

 

**示例 1：**

![img](https://assets.leetcode.com/uploads/2021/03/03/pal1linked-list.jpg)

```
输入：head = [1,2,2,1]
输出：true
```

**示例 2：**

![img](https://assets.leetcode.com/uploads/2021/03/03/pal2linked-list.jpg)

```
输入：head = [1,2]
输出：false
```

 

**提示：**

- 链表中节点数目在范围`[1, 105]` 内
- `0 <= Node.val <= 9`

 

**进阶：**你能否用 `O(n)` 时间复杂度和 `O(1)` 空间复杂度解决此题？



注意：本题与主站 234 题相同：https://leetcode-cn.com/problems/palindrome-linked-list/

From: https://leetcode-cn.com/problems/aMhZSa/



## 题解

此题思路虽简单直接，但由于细节太多，很容易出错，其实也可以算得上是中等难度。

```c++
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
    bool isPalindrome(ListNode* head) {
        // find the middle
        ListNode *p1 = head, *p2 = head;
        while (p2 && p2->next) {
            p1 = p1->next;
            p2 = p2->next->next;
        }
        // reverse right half
        ListNode *cur = p1->next;
        p1->next = nullptr;
        while (cur) {
            p2 = cur->next;
            cur->next = p1;
            p1 = cur;
            cur = p2;
        } // now p1 is at the tail
        // check if is palindrome
        ListNode *tail = p1;
        bool flag = true;
        p2 = head;
        while (p2 && p1) {
            if (p2->val != p1->val) {
                flag = false;
                break;
            } else {
                p2 = p2->next;
                p1 = p1->next;
            }
        }
        // recover the order of the right half
        p1 = nullptr;
        while (tail) {
            p2 = tail->next;
            tail->next = p1;
            p1 = tail;
            tail = p2;
        }
        return flag;
    }
};
```

