## 题目

给你两个 **非空** 链表来代表两个非负整数。数字最高位位于链表开始位置。它们的每个节点只存储一位数字。将这两数相加会返回一个新的链表。

你可以假设除了数字 0 之外，这两个数字都不会以零开头。

 

**示例1：**

![img](https://mdpicbed.oss-cn-hongkong.aliyuncs.com/imgs/1626420025-fZfzMX-image.png)

```
输入：l1 = [7,2,4,3], l2 = [5,6,4]
输出：[7,8,0,7]
```

**示例2：**

```
输入：l1 = [2,4,3], l2 = [5,6,4]
输出：[8,0,7]
```

**示例3：**

```
输入：l1 = [0], l2 = [0]
输出：[0]
```

 

**提示：**

- 链表的长度范围为` [1, 100]`
- `0 <= node.val <= 9`
- 输入数据保证链表代表的数字无前导 0

 

**进阶：**如果输入链表不能翻转该如何解决？

答：可以用两个 vector 或者两个 stack 来解决。



## 题解

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
    ListNode* reverseList(ListNode* head) {
        if (!head || !head->next) return head;
        ListNode *a = head, *b = head->next;
        head = nullptr;
        while (a) {
            a->next = head;
            head = a;
            a = b;
            if (a) b = a->next;
        }
        return head;
    }

    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        l1 = reverseList(l1);
        l2 = reverseList(l2);
        ListNode* head = nullptr;
        int carry = 0;
        while (l1 || l2 || carry) {
            // 求和
            carry += l1 ? l1->val : 0;
            carry += l2 ? l2->val : 0;
            // 新建节点
            head = new ListNode(carry % 10, head);
            // 更新进位
            carry /= 10;
            // 更新两个数位
            l1 = l1 ? l1->next : l1;
            l2 = l2 ? l2->next : l2;
        }
        return head;
    }
};
```

