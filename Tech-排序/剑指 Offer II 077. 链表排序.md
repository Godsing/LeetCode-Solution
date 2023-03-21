## 题目

给你链表的头结点 `head` ，请将其按 **升序** 排列并返回 **排序后的链表** 。



 

**示例 1：**

![img](https://mdpicbed.oss-cn-hongkong.aliyuncs.com/imgs/sort_list_1.jpg)

```
输入：head = [4,2,1,3]
输出：[1,2,3,4]
```

**示例 2：**

![img](https://mdpicbed.oss-cn-hongkong.aliyuncs.com/imgs/sort_list_2.jpg)

```
输入：head = [-1,5,3,4,0]
输出：[-1,0,3,4,5]
```

**示例 3：**

```
输入：head = []
输出：[]
```

 

**提示：**

- 链表中节点的数目在范围 `[0, 5 * 10^4]` 内
- `-10^5 <= Node.val <= 10^5`

 

**进阶：**你可以在 `O(n log n)` 时间复杂度和常数级空间复杂度下，对链表进行排序吗？



注意：本题与主站 148 题相同：https://leetcode-cn.com/problems/sort-list/



## 题解

以下几种方法的时间复杂度都是 O(n)，但空间复杂度各不相同。

- 方法一：借助额外的数据结构（数组或堆）进行排序，空间复杂度 O(n)。下面以数组为例：

```c++
class Solution {
public:
    ListNode* sortList(ListNode* head) {
        if (!head || !head->next) return head;
        vector<ListNode*> nodes;
        while (head) {nodes.push_back(head); head = head->next;}
        sort(nodes.begin(), nodes.end(), [](auto n1, auto n2) {return n1->val < n2->val;});
        for (int i = 0; i < nodes.size() - 1; i++) nodes[i]->next = nodes[i+1];
        nodes.back()->next = nullptr;
        return nodes[0]; 
    }
};
```

- 方法二：快速排序，由于递归深度为 O(log n)，故空间复杂度也为 O(log n)。这里对极端情况做了考虑，优化了 partition 函数，取区间的中间元素作为中枢节点，但依然超出时间限制。

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
    ListNode* sortList(ListNode* head) {
        quickly_sort(head, nullptr);
        return head;
    }

    void quickly_sort(ListNode* left, ListNode* right) {  // 左闭右开
        if (left == right) return ;
        ListNode* idx = mid_partition(left, right);
        quickly_sort(left, idx);
        quickly_sort(idx->next, right);
    }

    ListNode* mid_partition(ListNode* left, ListNode* right) {
        ListNode *slow = left, *fast = left;
        while (fast != right && fast->next != right) {
            slow = slow->next;
            fast = fast->next->next;
        }
        swap_node(left, slow);
        return partition(left, right);
    }

    ListNode* partition(ListNode* left, ListNode* right) {
        int pivot = left->val;
        ListNode *idx = left, *cur = left;
        while (cur != right) {
            if (cur->val < pivot) {
                idx = idx->next;
                swap_node(idx, cur);
            }
            cur = cur->next;
        }
        swap_node(idx, left);
        return idx;
    }

    void swap_node(ListNode* n1, ListNode* n2) {
        if (n1 == n2) return ;
        int val = n1->val;
        n1->val = n2->val;
        n2->val = val;
    }
};
```

- 方法三：除了快速排序，还可以用归并排序。归并排序如果用递归的写法，则空间复杂度比快速排序还高，达到 O(n)，但如果用循环来实现，则可以实现 O(1) 的空间复杂度。



## TODO

- [ ] 用堆实现解题
- [ ] 寻找快速排序超时的根源
- [ ] 实现归并排序的循环写法