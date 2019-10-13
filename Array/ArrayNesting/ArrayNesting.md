## Problem

A zero-indexed array A of length N contains all integers from 0 to N-1. Find and return the longest length of set S, where S[i] = {A[i], A[A[i]], A[A[A[i]]], ... } subjected to the rule below.

Suppose the first element in S starts with the selection of element A[i] of index = i, the next element in S should be A[A[i]], and then A[A[A[i]]]… By that analogy, we stop adding right before a duplicate element occurs in S.

**Example 1:**

```
Input: A = [5,4,0,3,1,6,2]
Output: 4
Explanation: 
A[0] = 5, A[1] = 4, A[2] = 0, A[3] = 3, A[4] = 1, A[5] = 6, A[6] = 2.

One of the longest S[K]:
S[0] = {A[0], A[5], A[6], A[2]} = {5, 6, 2, 0}

```

**Note:**

1. N is an integer within the range [1, 20,000].
2. The elements of A are all distinct.
3. Each element of A is an integer within the range [0, N-1].




## Solution

显然，很容易想到的一个方法是：遍历每一个可能的集合S，除非已经找到一个大小为N的集合。

```cpp
#include <iostream>
#include <vector>
// #include <set> // Most operations of set take O(n) time.
#include <unordered_set>  // Find, insert and erase take constant time.
using namespace std;

class Solution {
public:
    int arrayNesting(vector<int>& nums) {
        int res = 1;
        for(int i = 0; i < nums.size(); i++) {
            unordered_set<int> S;
            int j = i;
            while(S.find(nums[j]) == S.end()) {
                S.insert(nums[j]);
                j = nums[j];
            }
            if(S.size() == nums.size())
                return S.size();
            res = S.size() > res ? S.size() : res;
        }
        return res;
    }
};
```

然而，如果真的用这个方法，虽然结果是对的，但是提交到 Leetcode 上会发现超时。是不是做了太多无用功了？

仔细分析，会发现：当我们从一个元素开始找，会不断的持续，一直到某个元素又“指向”了开始的元素，形成了一个圈。而我们的目标就是要找到那个最长的圈！因为每个元素的唯一性，必然最多只有一个元素“指向”它，而它也最多“指向”一个元素。这就意味着，在一个圈中出现过的元素，必然不会出现在另外一个圈中。所以，每次找到一个圈，记下圈的长度，然后从**剩下的还没被找过的**元素继续开始找圈就行了。这样的时间复杂度是 O(n)，而之前的方法是 $O(n^2)$ .

```cpp
class Solution {
public:
    int arrayNesting(vector<int>& nums) {
        int res = 1;
        int left = nums.size();  // 用于记录剩余元素个数
        for(int i = 0; i < nums.size(); i++) {
            int temp = 0;
            for(int j = i; nums[j] != -1; temp++) {
                int t = nums[j];
                nums[j] = -1;
                j = t;
            }
            res = temp > res ? temp : res;
            left -= temp;
            if (left <= res) break;  // 剩余元素个数如果比已经找到的res还小，就没必要再找了
        }
        return res;
    }
};
```

通过这题我得到了很大启发：尽量去发现问题中的隐含规律或隐含的约束，有时候可以量级地减小问题的规模。

