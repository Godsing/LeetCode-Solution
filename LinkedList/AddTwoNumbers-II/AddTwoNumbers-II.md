## Problem

You are given two **non-empty** linked lists representing two non-negative integers. The most significant digit(数位) comes first and each of their nodes contain a single digit. Add the two numbers and return it as a linked list.

You may assume the two numbers do not contain any leading zero, except the number 0 itself.

**Follow up:**
What if you cannot modify the input lists? In other words, reversing the lists is not allowed.

**Example:**

```
Input: (7 -> 2 -> 4 -> 3) + (5 -> 6 -> 4)
Output: 7 -> 8 -> 0 -> 7
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
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        vector<int> digitList1, digitList2;
        int digit1, digit2, i, j, k, sum=0;
        while (l1 != NULL) {
            digitList1.emplace_back(l1->val);
            l1 = l1->next;
        }
        while (l2 != NULL) {
            digitList2.emplace_back(l2->val);
            l2 = l2->next;
        }
        int len = digitList1.size() < digitList2.size() ? digitList2.size() : digitList1.size();
        if (len == 0) return (new ListNode(0));
        ListNode * head = NULL;
        for (i=0, j=digitList1.size()-1, k=digitList2.size()-1; i<len; i++, j--, k--) {
            ListNode * temp = new ListNode(0);
            digit1 = j < 0 ? 0 : digitList1[j];
            digit2 = k < 0 ? 0 : digitList2[k];
            sum = sum + digit1 + digit2;
            temp->val = sum % 10;
            sum /= 10;  //这里作为进位，就不单独设置进位变量carry了，但可能导致代码的可读性变差
            temp->next = head;
            head = temp;
        }
        if (sum > 0) {  //单独考虑最高位的情况
            ListNode * temp = new ListNode(sum);
            temp->next = head;
            head = temp;
        }
        return head;
    }
};
//Runtime: 66ms
```

利用 Stack 的解法，思路差不多：

```c++
class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        stack<int> s1,s2;
        while(l1){
            s1.push(l1->val);
            l1 = l1->next;
        }
        while(l2){
            s2.push(l2->val);
            l2 = l2->next;
        }
        int carry = 0;
        ListNode* next = NULL;
        while(!s1.empty() && !s2.empty()){
            int sum = s1.top() + s2.top() + carry;
            ListNode* cur = new ListNode(sum%10);
            cur->next = next;
            next = cur;
            carry = sum/10;  //使用carry作为单独的进位变量，可读性好
            s1.pop(), s2.pop();
        }
        while(!s1.empty()){
            int sum = s1.top() + carry;
            ListNode* cur = new ListNode(sum%10);
            cur->next = next;
            next = cur;
            carry = sum/10;
            s1.pop();
        }
        while(!s2.empty()){
            int sum = s2.top() + carry;
            ListNode* cur = new ListNode(sum%10);
            cur->next = next;
            next = cur;
            carry = sum/10;
            s2.pop();
        }
        if(carry){
            ListNode* cur = new ListNode(carry);
            cur->next = next;
            next = cur;
        }
        return next;
    }
};
//Runtime: 67ms
```





## Debug&Learning

一开始尝试将链表转化成数字，相加后再转化成列表，如下：

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
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        vector<int> digitList1, digitList2;
        long long num1 = 0, num2 = 0, sum = 0;
        while (l1 != NULL) {
            digitList1.emplace_back(l1->val);
            l1 = l1->next;
        }
        while (l2 != NULL) {
            digitList2.emplace_back(l2->val);
            l2 = l2->next;
        }
        for(auto digit : digitList1) {
            num1 = num1 * 10 + digit;
        }
        for(auto digit : digitList2) {
            num2 = num2 * 10 + digit;
        }
        sum = num1 + num2;
        // if(sum == 0) return l1; //不能直接返回l1，因为它可能是NULL
        int bit[digitList1.size() < digitList2.size() ? digitList2.size() + 1 : digitList1.size() + 1];
        int pos = 0;
        while (sum) {
            bit[pos++] = sum%10;
            sum /= 10;
        }
        ListNode * head = NULL;
        for (int i=0; i<pos; i++){
            ListNode * temp = new ListNode(0);
            temp->val = bit[i];
            temp->next = head;
            head = temp;
        }
        return head == NULL ? (new ListNode(0)) : head;
    }
};
```

然而，事实证明这么考虑欠周，因为有一个测试样例为：

```
Input:
[2,4,3,2,4,3,2,4,3,2,4,3,2,4,3,2,4,3,2,4,3,2,4,3,2,4,3,2,4,3,2,4,3,2,4,3,2,4,3,2,4,3,2,4,3,2,4,3,2,4,3,2,4,3,2,4,3,2,4,3,9]
[5,6,4,2,4,3,2,4,3,2,4,3,2,4,3,2,4,3,2,4,3,2,4,3,2,4,3,2,4,3,2,4,3,2,4,3,2,4,3,2,4,3,2,4,3,2,4,3,2,4,3,2,4,3,2,4,3,9,9,9,9]
```

这远远超出了数字可以表示的范围。

解铃还需系铃人，我还是老老实实直接创建新链表吧。

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
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        vector<int> digitList1, digitList2;
        int digit1, digit2, i, j, k, sum=0;
        while (l1 != NULL) {
            digitList1.emplace_back(l1->val);
            l1 = l1->next;
        }
        while (l2 != NULL) {
            digitList2.emplace_back(l2->val);
            l2 = l2->next;
        }
        int len = digitList1.size() < digitList2.size() ? digitList2.size() + 1 : digitList1.size() + 1; //返回的链表的最大可能长度
        if (len == 1) return (new ListNode(0));
        ListNode * head = NULL;
        for (i=0, j=digitList1.size()-1, k=digitList2.size()-1; i<len; i++, j--, k--) {
            ListNode * temp = new ListNode(0);
            digit1 = j < 0 ? 0 : digitList1[j];
            digit2 = k < 0 ? 0 : digitList2[k];
            sum = sum + digit1 + digit2;
            temp->val = sum % 10;
            sum /= 10;
            temp->next = head;
            head = temp;
        }
        return head->val == 0 ? head->next : head;  //如果链表长度大于1，那么如果存在最高位进位为0的话需要删掉，但这里没有free()，可能导致内存泄漏
    }
};
```

为了防止内存泄漏，最高位单独考虑是否添加结点，改成如下：

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
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        vector<int> digitList1, digitList2;
        int digit1, digit2, i, j, k, sum=0;
        while (l1 != NULL) {
            digitList1.emplace_back(l1->val);
            l1 = l1->next;
        }
        while (l2 != NULL) {
            digitList2.emplace_back(l2->val);
            l2 = l2->next;
        }
        int len = digitList1.size() < digitList2.size() ? digitList2.size() : digitList1.size();
        if (len == 0) return (new ListNode(0));
        ListNode * head = NULL;
        for (i=0, j=digitList1.size()-1, k=digitList2.size()-1; i<len; i++, j--, k--) {
            ListNode * temp = new ListNode(0);
            digit1 = j < 0 ? 0 : digitList1[j];
            digit2 = k < 0 ? 0 : digitList2[k];
            sum = sum + digit1 + digit2;
            temp->val = sum % 10;
            sum /= 10;
            temp->next = head;
            head = temp;
        }
        if (sum > 0) {  //单独考虑最高位的情况
            ListNode * temp = new ListNode(sum);
            temp->next = head;
            head = temp;
        }
        return head;
    }
};
```

