## Problem

Given a (singly) linked list with head node `root`, write a function to split the linked list into `k` consecutive linked list "parts".

The length of each part should be as equal as possible: no two parts should have a size differing by more than 1. This may lead to some parts being null.

The parts should be in order of occurrence in the input list, and parts occurring earlier should always have a size greater than or equal parts occurring later.

Return a List of ListNode's representing the linked list parts that are formed.

Examples 1->2->3->4, k = 5 // 5 equal parts [ [1], [2], [3], [4], null ]

**Example 1:**

```
Input: 
root = [1, 2, 3], k = 5
Output: [[1],[2],[3],[],[]]
Explanation:
The input and each element of the output are ListNodes, not arrays.
For example, the input root has root.val = 1, root.next.val = 2, \root.next.next.val = 3, and root.next.next.next = null.
The first element output[0] has output[0].val = 1, output[0].next = null.
The last element output[4] is null, but it's string representation as a ListNode is [].
```

**Example 2:**

```
Input: 
root = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10], k = 3
Output: [[1, 2, 3, 4], [5, 6, 7], [8, 9, 10]]
Explanation:
The input has been split into consecutive parts with size difference at most 1, and earlier parts are a larger size than the later parts.
```

**Note:**

The length of `root` will be in the range `[0, 1000]`.

Each value of a node in the input will be an integer in the range `[0, 999]`.

`k` will be an integer in the range `[1, 50]`.





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
    vector<ListNode*> splitListToParts(ListNode* root, int k) {
        int num = 0, i = 0, j = 0;
        ListNode* tmp = root;
        for(; tmp != NULL; tmp = tmp->next) num++;
        
        vector<ListNode*> part(k);  
        int div = (int) num / k;
        int mod = num % k;
        for(i=0; i<mod; ++i){
            part[i] = root;
            for(j=0; j < div; ++j)
                root = root->next;
            tmp = root;
            root = root->next;
            tmp->next = NULL;
        }
        
        if(div == 0) return part;
        
        for(i=mod; i<k; ++i){
            part[i] = root;
            for(j=0; j < div-1; ++j)
                root = root->next;
            tmp = root;
            root = root->next;
            tmp->next = NULL;
        }
        return part;
    }
};
//Accepted
//Runtime: 12ms 基本是最快的速度了
```



## Debug&Learning

1. 一开始使用了 part.emplace_back(NULL);  最后发现似乎不能 emplace_back(NULL)，所以弃用该方法，改用直接初始化 k 个元素
2. 初始化 vector 时，不需要写成 part(k, NULL)，默认就是NULL

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
        vector<ListNode*> part(k);  //不需要写成 part(k, NULL)，默认就是NULL
        if (num == 0) {
            return part;
            // for(i=0; i<k; ++i)
            //     part.emplace_back(NULL);  //1. 似乎不能 emplace_back(NULL)，所以弃用该方法，改用直接初始化 k 个元素
        } else if (num < k) {
            for(i=0; i<num; ++i){
                part[i] = root;
                // part.emplace_back(root);
                root = root->next;
            }
            // for(i=num; i<k; ++i)
            //     part.emplace_back(NULL);
        } else {
            int div = (int) num / k;
            int mod = num % k;
            int j=0;
            if (mod == 0) {
                for(i=0; i<k; ++i){
                    part[i] = root;
                    // part.emplace_back(root);
                    for(j=0; j<div; ++j)
                        root = root->next;
                }
            } else {
                for(i=0; i<mod; ++i){
                    part[i] = root;
                    // part.emplace_back(root);
                    for(j=0; j < div + 1; ++j)
                        root = root->next;
                }
                for(i=mod; i<k; ++i){
                    part[i] = root;
                    // part.emplace_back(root);
                    for(j=0; j < div; ++j)
                        root = root->next;
                }
            }
        }
        return part;
    }
    
};
```

以上代码存在两个问题：

1. 输出不对

##### Your input

```
[1,2,3,4]
5
```

##### Your answer

```
[[1,2,3,4],[2,3,4],[3,4],[4],[]]
```

##### Expected answer

```
[[1],[2],[3],[4],[]]
```

2. 代码冗余

不需要区分那么多种情况。



先解决第一个问题，修改后如下：

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
        ListNode* tmp = root;
        for(; tmp != NULL; tmp = tmp->next) num++;
        vector<ListNode*> part(k);  //不需要写成 part(k, NULL)，默认就是NULL
        if (num == 0) {
            return part;
        } else if (num < k) {
            for(i=0; i<num; ++i){
                part[i] = root;
                root = root->next; //leetcode有时候报第N行代码Runtime error，其实可能是在后面一行或多行后才产生的错误
                part[i]->next = NULL;  //新的 part 与之前结点断开连接
            }
        } else {
            int div = (int) num / k;
            int mod = num % k;
            int j=0;
            if (mod == 0) {
                for(i=0; i<k; ++i){
                    part[i] = root;
                    for(j=0; j<div-1; ++j)
                        root = root->next;
                    tmp = root; //主要是增加了缓存 tmp 用于保存新的 part 前面的结点。
                    root = root->next;
                    tmp->next = NULL;
                }
            } else {
                for(i=0; i<mod; ++i){
                    part[i] = root;
                    for(j=0; j < div; ++j)
                        root = root->next;
                    tmp = root;
                    root = root->next;
                    tmp->next = NULL;
                }
                for(i=mod; i<k; ++i){
                    part[i] = root;
                    for(j=0; j < div-1; ++j)
                        root = root->next;
                    tmp = root;
                    root = root->next;
                    tmp->next = NULL;
                }
            }
        }
        return part;
    }
    
};
//Accepted
//Runtime: 22ms
```

再解决第二个问题，把冗余的代码精简成如下：

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
        ListNode* tmp = root;
        for(; tmp != NULL; tmp = tmp->next) num++;
        
        vector<ListNode*> part(k);  //不需要写成 part(k, NULL)，默认就是NULL
        // if (num == 0) return part;  //这句话其实也可以去掉，因为从工程经验上可以认为这种情况出现的频率不高，为此多设一个分支没有必要；去掉这句话，让出现这种情况时多执行下面几行代码；我认为从总体上来讲程序的整体效率会更高（虽然基本可以忽略 囧）
        //另外，我还认为，使用如下统一的方式更方便代码的维护和复用
        
        int div = (int) num / k;
        int mod = num % k;
        int j=0;
        for(i=0; i<mod; ++i){  //如果 num==0，该部分会自动略过
            part[i] = root;
            for(j=0; j < div; ++j)
                root = root->next;
            tmp = root;
            root = root->next;
            tmp->next = NULL;
        }
        
        if(div == 0) return part;  //num < k（包括num==0）时，都会在这里返回
        
        for(i=mod; i<k; ++i){
            part[i] = root;
            for(j=0; j < div-1; ++j)
                root = root->next;
            tmp = root;
            root = root->next;
            tmp->next = NULL;
        }
        return part;
    }
};
//Accepted
//Runtime: 13ms
```



