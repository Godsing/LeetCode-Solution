## 题目

给你一个 **下标从 0 开始** 的正整数数组 `w` ，其中 `w[i]` 代表第 `i` 个下标的权重。

请你实现一个函数 `pickIndex` ，它可以 **随机地** 从范围 `[0, w.length - 1]` 内（含 `0` 和 `w.length - 1`）选出并返回一个下标。选取下标 `i` 的 **概率** 为 `w[i] / sum(w)` 。



- 例如，对于 `w = [1, 3]`，挑选下标 `0` 的概率为 `1 / (1 + 3) = 0.25` （即，25%），而选取下标 `1` 的概率为 `3 / (1 + 3) = 0.75`（即，`75%`）。

 

**示例 1：**

```
输入：
["Solution","pickIndex"]
[[[1]],[]]
输出：
[null,0]
解释：
Solution solution = new Solution([1]);
solution.pickIndex(); // 返回 0，因为数组中只有一个元素，所以唯一的选择是返回下标 0。
```

**示例 2：**

```
输入：
["Solution","pickIndex","pickIndex","pickIndex","pickIndex","pickIndex"]
[[[1,3]],[],[],[],[],[]]
输出：
[null,1,1,1,1,0]
解释：
Solution solution = new Solution([1, 3]);
solution.pickIndex(); // 返回 1，返回下标 1，返回该下标概率为 3/4 。
solution.pickIndex(); // 返回 1
solution.pickIndex(); // 返回 1
solution.pickIndex(); // 返回 1
solution.pickIndex(); // 返回 0，返回下标 0，返回该下标概率为 1/4 。

由于这是一个随机问题，允许多个答案，因此下列输出都可以被认为是正确的:
[null,1,1,1,1,0]
[null,1,1,1,1,1]
[null,1,1,1,0,0]
[null,1,1,1,0,1]
[null,1,0,1,0,0]
......
诸若此类。
```

 

**提示：**

- `1 <= w.length <= 10^4`
- `1 <= w[i] <= 10^5`
- `pickIndex` 将被调用不超过 `10^4` 次



注意：本题与主站 528 题相同： https://leetcode-cn.com/problems/random-pick-with-weight/



## 题解

**我的思路：**

1. 将权重转换成区间：可以将截至每个索引的前缀和，当作该区间的终点，那么每个区间的跨度就为 `[上一个索引的前缀和+1, 截至当前索引的前缀和]` ，刚好包含了 `w[i]` 个正整数值。那么问题就转换成，随机生成一个 `[1, 所有元素之和]` 区间内的值，它落在哪个区间，就返回该区间对应的索引。
2. 用二分搜索来寻找某个随机值的所在区间；

**实现方法：**

1. 区间与索引间的对应关系，需要一个哈希映射表；
2. 所有区间的终点是不断递增的，可以直接用这个终点来代表区间；
3. 寻找某个随机值的所在区间，只需寻找第一个大于等于该值的区间终点即可；这个可以用“数组+二分搜索”来实现，也可以用 C++ 模板库的 `map` 来构造一棵 BST 并调用其 `lower_bound` 函数来实现，为求简便，下面直接用后者来实现。

```c++
class Solution {
private:
    map<int, int> span_end2idx;
    int span_end = 0;
public:
    Solution(vector<int>& w) {
        for (int i = 0; i < w.size(); i++) {
            span_end += w[i];
            span_end2idx[span_end] = i;
        }
    }
    
    int pickIndex() {
        int val = rand() % span_end + 1;
        auto it = span_end2idx.lower_bound(val);  // 用 `lower_bound` 来寻找 ≥val 的 key 中的最小值(边界)
        return it->second;
    }
};

/**
 * Your Solution object will be instantiated and called as such:
 * Solution* obj = new Solution(w);
 * int param_1 = obj->pickIndex();
 */
```

