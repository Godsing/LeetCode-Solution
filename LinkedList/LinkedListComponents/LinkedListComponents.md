

## Problem

We are given `head`, the head node of a linked list containing **unique integer values**.

We are also given the list `G`, a subset of the values in the linked list.

Return the number of connected components in `G`, where two values are connected if they appear consecutively in the linked list.

**Example 1:**

```
Input: 
head: 0->1->2->3
G = [0, 1, 3]
Output: 2
Explanation: 
0 and 1 are connected, so [0, 1] and [3] are the two connected components.
```

**Example 2:**

```
Input: 
head: 0->1->2->3->4
G = [0, 3, 1, 4]
Output: 2
Explanation: 
0 and 1 are connected, 3 and 4 are connected, so [0, 1] and [3, 4] are the two connected components.
```

**Note:**

- If `N` is the length of the linked list given by `head`, `1 <= N <= 10000`.
- The value of each node in the linked list will be in the range` [0, N - 1]`.
- `1 <= G.length <= 10000`.
- `G` is a subset of all values in the linked list.





## Solution

外层循环，从 head 开始遍历链表；

内层循环，对于每个链表中的 val 值，查看其是否在数组中（用 is_find 标识，并且将该值删除以缩短数组大小）；判断是否是新增的 connected components （用 flag 标识，用 res 计数）。

```cpp
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
    int numComponents(ListNode* head, vector<int>& G) {
        int s = 0, res = 0;
        bool flag = false;
        vector<int>::iterator it;
        while (head != NULL) {
            s = G.size();
            if (s==0) break;
            bool is_find = false;
            for (it = G.begin(); it != G.end(); it++) {
                if (*it == head->val) {
                    G.erase(it);
                    is_find = true;
                    if (!flag) {
                        res++;
                        flag = true;
                    }
                    break;
                }
            }
            if (!is_find) flag = false;
            head = head->next;
        }
        return res;
    }
};
// Runtime 293 ms
```



改进：

每次判断一个数是否在数组中，都需要遍历，时间复杂度为 O(G) （G为数组大小）。如果能将其变成 O(1) 的时间复杂度就好了。因此需要考虑换一种数据类型，很容易想到的就是 unordered_set ，它查找的时间复杂度是 O(1)。实现如下：

```cpp
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
    int numComponents(ListNode* head, vector<int>& G) {
        unordered_set<int> Gset;  // 写成 gSet 会显得规范一些
        for (auto x : G) Gset.insert(x);
        // 上面两行可以写成：auto Gset = unordered_set<int>{begin(G),end(G)};
        bool flag = false;
        int res = 0;
        while (head != NULL) { // NULL 可以写成 nullptr
            if (Gset.find(head->val) != Gset.end()) {
                if (!flag){
                    res++;
                    flag = true;
                }
            } else flag = false;
            head = head->next;
        }
        return res;
    }
};
// Runtime 33 ms
```

运行时间缩短为将近原来的十分之一，可见数据结构的重要性。



Python 版本1：

```python
# Definition for singly-linked list.
# class ListNode:
#     def __init__(self, x):
#         self.val = x
#         self.next = None

class Solution:
    def numComponents(self, head, G):
        """
        :type head: ListNode
        :type G: List[int]
        :rtype: int
        """
        res = 0
        flag = False
        while head:
            if head.val in G:
                if not flag:
                    res += 1
                    flag = True
            else:
                flag = False
            head = head.next
        return res
```

该版本会导致超时，因为 List 性能太低。

参考了别人贴出来的代码，仍然像 c++ 那样改用Set，使得查找速度提升上来。

Python 版本2：

```python
# Definition for singly-linked list.
# class ListNode:
#     def __init__(self, x):
#         self.val = x
#         self.next = None

class Solution:
    def numComponents(self, head, G):
        """
        :type head: ListNode
        :type G: List[int]
        :rtype: int
        """
        gSet, res, flag = set(G), 0, False
        while head:
            if head.val in gSet:
                if not flag:
                    res += 1
                    flag = True
            else:
                flag = False
            head = head.next
        return res
# Runtime: 100 ms  # 这是一个相当好的数据，仅仅是使用 C++ 的3倍
```



Discuss 板块别人贴出来的 Java O(n) 版本：

```java
/**
 * Definition for singly-linked list.
 * public class ListNode {
 *     int val;
 *     ListNode next;
 *     ListNode(int x) { val = x; }
 * }
 */
class Solution {
    public int numComponents(ListNode head, int[] G) {
        HashSet<Integer> set = new HashSet<>();
        
        for (int i = 0; i < G.length; i++) {
            set.add(G[i]);
        }
        
        int components = 1;
        boolean isComponent = false;
        
        ListNode cur = head;
        
        while (cur != null && !set.isEmpty()) {
            if (set.contains(cur.val)) {
                set.remove(cur.val);
                
                isComponent = true;
            } else if (isComponent) {
                components++;
                
                isComponent = false;
            } 
            
            cur = cur.next;
        }
        
        return components;
    }
}
```

