## 题目

给定循环单调非递减列表中的一个点，写一个函数向这个列表中插入一个新元素 insertVal ，使这个列表仍然是循环升序的。

给定的可以是这个列表中任意一个顶点的指针，并不一定是这个列表中最小元素的指针。

如果有多个满足条件的插入位置，可以选择任意一个位置插入新的值，插入后整个列表仍然保持有序。

如果列表为空（给定的节点是 null），需要创建一个循环有序列表并返回这个节点。否则。请返回原先给定的节点。

 

示例 1：

![img](https://mdpicbed.oss-cn-hongkong.aliyuncs.com/imgs/example_1_before_65p-20220121203428065.jpg)

输入：head = [3,4,1], insertVal = 2
输出：[3,4,1,2]
解释：在上图中，有一个包含三个元素的循环有序列表，你获得值为 3 的节点的指针，我们需要向表中插入元素 2 。新插入的节点应该在 1 和 3 之间，插入之后，整个列表如上图所示，最后返回节点 3 。

![img](https://mdpicbed.oss-cn-hongkong.aliyuncs.com/imgs/example_1_after_65p.jpg)


示例 2：

输入：head = [], insertVal = 1
输出：[1]
解释：列表为空（给定的节点是 null），创建一个循环有序列表并返回这个节点。
示例 3：

输入：head = [1], insertVal = 0
输出：[1,0]


提示：

0 <= Number of Nodes <= 5 * 10^4
-10^6 <= Node.val <= 10^6
-10^6 <= insertVal <= 10^6


注意：本题与主站 708 题相同： https://leetcode-cn.com/problems/insert-into-a-sorted-circular-linked-list/

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/4ueAj6
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。



## 题解

此题很不错，特别考验思考和分析能力，难怪通过率那么低。以下思维导图是我的思考，并基于此实现了代码：

![image-20220121203852490](https://mdpicbed.oss-cn-hongkong.aliyuncs.com/imgs/image-20220121203852490.png)

```c++
/*
// Definition for a Node.
class Node {
public:
    int val;
    Node* next;

    Node() {}

    Node(int _val) {
        val = _val;
        next = NULL;
    }

    Node(int _val, Node* _next) {
        val = _val;
        next = _next;
    }
};
*/

class Solution {
public:
    Node* insert(Node* head, int insertVal) {
        // 链表为空，添加一个元素，并指向自己
        if (!head) {
            Node* n = new Node(insertVal);
            n->next = n;
            return n;
        }
        // 链表只有一个元素，任意位置直接添加即可
        if (head->next == head) {
            Node* n = new Node(insertVal);
            head->next = n;
            n->next = head;
            return head;
        }
        // 先假设“存在不相等”的元素，然后遍历一圈，找到“合理的插入位置”
        Node* p = head;
        while (p->next != head) {
            if ((p->val == p->next->val && insertVal == p->val) || 
                ((p->val < p->next->val) && (insertVal >= p->val && insertVal <= p->next->val)) || 
                ((p->val > p->next->val) && (insertVal >= p->val || insertVal <= p->next->val))) {
                    Node* n = new Node(insertVal);
                    n->next = p->next;
                    p->next = n;
                    return head;
            }
            p = p->next;
        }
        // 若找不到“合理的插入位置”，则说明所有元素都相等，任意位置都可插入
        Node* n = new Node(insertVal);
        n->next = p->next;
        p->next = n;
        return head;
    }
};

// 执行用时：4 ms, 在所有 C++ 提交中击败了 97.96% 的用户
// 内存消耗：8 MB, 在所有 C++ 提交中击败了 31.46% 的用户
```

