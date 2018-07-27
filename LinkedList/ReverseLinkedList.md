## Problem

206. Reverse Linked List

Reverse a singly linked list.

**Example:**

```
Input: 1->2->3->4->5->NULL
Output: 5->4->3->2->1->NULL
```

**Follow up:**

A linked list can be reversed either iteratively or recursively. Could you implement both?





## Solution

新增两个临时的指针，分别指向前后相邻的两个结点，并同时逐步向后挪，挪的同时把地一个指针指向之前的结点，这样便可以实现反转，最后返回最末尾的节点（变成了反转后的头部结点）。

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
    ListNode* reverseList(ListNode* head) {
        if (head == NULL) return NULL;  //要考虑输入为空的情况
        ListNode * pre = head;
        ListNode * post = head->next;
        pre->next = NULL;
        while(post != NULL) {
            head = pre;  //head 右挪
            pre = post;  //pre 右挪
            post = post->next;  //post 右挪
            pre->next = head;  //pre 指向前一个结点
        }  //循环结束时，pre恰好指向最后一个结点
        return pre;
    }
};
```



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
    vector<ListNode*> splitListToParts(ListNode* root, int k) {
        int num = 0, i = 0;
        for(ListNode* tmp = root; tmp != NULL; tmp = tmp->next) num++;
        vector<ListNode*> part[k];
        if (num == 0) {
            for(i=0; i<k; ++i)
                part[i] = NULL;
        } else if (num < k) {
            for(i=0; i<num; ++i){
                part[i] = root;
                root = root->next;
            }
            for(i=num; i<k; ++i)
                part[i] = NULL;
        } else {
            int div = (int) num / k;
            int mod = num % k;
            int j=0;
            for(i=0; i<mod; ++i){  // mod == 0 时，该部分自动就跳过了
                part[i] = root;
                for(j=0; j < div + 1; ++j)
                    root = root->next;
            }
            for(i=mod; i<k; ++i){
                part[i] = root;  // num < k（包括 num == 0）时，root 就自动是 null 了
                for(j=0; j < div; ++j) // // num < k（包括 num == 0）时，该部分就自动跳过了
                    root = root->next;
            }
        }
        
    }
    
};
```

