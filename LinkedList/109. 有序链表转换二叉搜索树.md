## Problem

Given a singly linked list where elements are sorted in ascending order, convert it to a height balanced BST.

For this problem, a height-balanced binary tree is defined as a binary tree in which the depth of the two subtrees of *every* node never differ by more than 1.

**Example:**

```
Given the sorted linked list: [-10,-3,0,5,9],

One possible answer is: [0,-3,9,-10,null,5], which represents the following height balanced BST:

      0
     / \
   -3   9
   /   /
 -10  5
```



## Solution

第一个版本，先把值链表的值存起来，再递归构建二叉树：

```cpp
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    TreeNode* sortedListToBST(ListNode* head) {
        if (!head) return NULL;
        vector<int> list;
        while (head) {
            list.emplace_back(head->val);
            head = head->next;
        }
        int begin = 0, end = list.size() - 1;
        TreeNode* res = arrayToBST(begin, end, list);
        return res;
    }
    //根据Google编码规范，函数传递引用参数时需要加上const，除非有特定需求，如swap()
    TreeNode* arrayToBST(int begin, int end, const vector<int> &list) {
        if (begin > end) return NULL;
        if (begin == end) return (new TreeNode(list[begin]));
        int mid = (begin + end + 1) / 2;
        TreeNode* node = new TreeNode(list[mid]);
        node->left = arrayToBST(begin, mid-1, list);
        node->right = arrayToBST(mid+1, end, list);
        return node;
    }
};
//Runtime: 21 ms, beats 99.80% of cpp submissions.
```

改用双指针来定位链表中点的版本：

```cpp
class Solution {
public:
    TreeNode* sortedListToBST(ListNode* head) {
        if (!head) return NULL;
        // ListNode* begin = head;
        // ListNode* end;
        // while (head) {
        //     head = head->next;
        //     end = head;
        // }
        // TreeNode* res = arrayToBST(begin, end); 
        //一开始写成上面这样，没有发现本质，太冗余了，其实一行就够了
        TreeNode* res = arrayToBST(head, NULL);
        return res;
    }
    //将区间[begin, end)内的链表转换成二叉树
    TreeNode* arrayToBST(ListNode* begin, ListNode* end) {
        if (begin == end) return NULL;
        // if (begin->next == end) return (new TreeNode(begin->val)); //删掉后仍逻辑完备
        ListNode* slow_point = begin;
        ListNode* fast_point = begin;
        while (fast_point != end && fast_point->next != end) {
            slow_point = slow_point->next;
            fast_point = fast_point->next->next;
        }
        TreeNode* node = new TreeNode(slow_point->val);
        node->left = arrayToBST(begin, slow_point);
        node->right = arrayToBST(slow_point->next, end);
        return node;
    }
};
//Runtime: 23 ms, 运行时间比上面的解法稍微慢了一小点，但是空间复杂度较小
```

删去注释，并稍微修改完善一下，更简洁易懂了，如下：

```cpp
class Solution {
public:
    TreeNode* sortedListToBST(ListNode* head) {
        return arrayToBST(head, NULL);
    }
    TreeNode* arrayToBST(ListNode* begin, ListNode* end) {
        if (begin == end) return NULL;
        auto slow_point = begin, fast_point = begin;
        while (fast_point != end && fast_point->next != end) {
            slow_point = slow_point->next;
            fast_point = fast_point->next->next;
        }
        TreeNode* node = new TreeNode(slow_point->val);
        node->left = arrayToBST(begin, slow_point);
        node->right = arrayToBST(slow_point->next, end);
        return node;
    }
};
//Runtime: 23 ms
```





## Debug&Learning



