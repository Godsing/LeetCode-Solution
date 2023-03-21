## 题目

给定一个单链表 `L` 的头节点 `head` ，单链表 `L` 表示为：

```
L0 → L1 → … → Ln - 1 → Ln
```

请将其重新排列后变为：

```
L0 → Ln → L1 → Ln - 1 → L2 → Ln - 2 → …
```

不能只是单纯的改变节点内部的值，而是需要实际的进行节点交换。

 

**示例 1：**

![img](https://mdpicbed.oss-cn-hongkong.aliyuncs.com/imgs/1626420311-PkUiGI-image.png)

```
输入：head = [1,2,3,4]
输出：[1,4,2,3]
```

**示例 2：**

![img](https://mdpicbed.oss-cn-hongkong.aliyuncs.com/imgs/1626420320-YUiulT-image.png)

```
输入：head = [1,2,3,4,5]
输出：[1,5,2,4,3]
```

 

**提示：**

- 链表的长度范围为 `[1, 5 * 10^4]`
- `1 <= node.val <= 1000`



注意：本题与主站 143 题相同：https://leetcode-cn.com/problems/reorder-list/ 

From: https://leetcode-cn.com/problems/LGjMqU/



## 题目

TODO: 探索其他解法。

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
    void reorderList(ListNode* head) {
        // 计算节点数
        int n = 0;
        ListNode* tmp = head;
        while (tmp) {
            n++;
            tmp = tmp->next;
        }
        // 计算最后需要反转的箭头数
        int need_reverse_arrow = (n-1)/2;
        // 找到(待会儿反转完成后)入度为 2 的节点，记录在 tmp 中（同时也会找到第一个需要反转的节点，记录在 n1 中）
        int cnt = n - 1 - need_reverse_arrow;
        tmp = head;
        while (cnt > 0) {
            tmp = tmp->next;
            cnt--;
        }
        ListNode *n1 = tmp->next, *n2;
        tmp->next = nullptr;  // 此节点最终必然是最后一个节点
        // 执行反转
        while (n1) {
            n2 = n1->next;
            n1->next = tmp;  // 逆向
            tmp = n1;
            n1 = n2;
        }
        // 交替首尾相接
        ListNode* start = head;
        while (start != tmp) {
            n1 = start->next;  // 临时征用 n1，用来表示 start 的 next 节点
            start->next = tmp;
            start = n1;
            swap(start, tmp);
        }
    }
};
```

