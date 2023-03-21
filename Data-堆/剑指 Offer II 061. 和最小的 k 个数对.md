## 题目

给定两个以 **升序排列** 的整数数组 `nums1` 和 `nums2` , 以及一个整数 `k` 。

定义一对值 `(u,v)`，其中第一个元素来自 `nums1`，第二个元素来自 `nums2` 。

请找到和最小的 `k` 个数对 `(u1,v1)`, ` (u2,v2)` ...  `(uk,vk)` 。

 

**示例 1:**

```
输入: nums1 = [1,7,11], nums2 = [2,4,6], k = 3
输出: [1,2],[1,4],[1,6]
解释: 返回序列中的前 3 对数：
     [1,2],[1,4],[1,6],[7,2],[7,4],[11,2],[7,6],[11,4],[11,6]
```

**示例 2:**

```
输入: nums1 = [1,1,2], nums2 = [1,2,3], k = 2
输出: [1,1],[1,1]
解释: 返回序列中的前 2 对数：
     [1,1],[1,1],[1,2],[2,1],[1,2],[2,2],[1,3],[1,3],[2,3]
```

**示例 3:**

```
输入: nums1 = [1,2], nums2 = [3], k = 3 
输出: [1,3],[2,3]
解释: 也可能序列中所有的数对都被返回:[1,3],[2,3]
```

 

**提示:**

- `1 <= nums1.length, nums2.length <= 10^5`
- `-10^9 <= nums1[i], nums2[i] <= 10^9`
- `nums1` 和 `nums2` 均为升序排列
- `1 <= k <= 1000`



注意：本题与主站 373 题相同：https://leetcode-cn.com/problems/find-k-pairs-with-smallest-sums/



来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/qn8gGX



## 题解

这道题实在太巧妙了。

一方面，需要知道下一个最小值组合存在一个候选范围、并且要知道如何递推得到的候选范围，另一方面，在代码实现上，还需要知道如何巧妙地避免候选范围添加时出现重复项，以方便使用堆来存储该候选范围。

另外，在代码实现上，还有很多精妙的地方。以下代码学习了官方题解并修改而来：

```c++
class Solution {
public:
    typedef pair<int, int> Pair;
    vector<vector<int>> kSmallestPairs(vector<int>& nums1, vector<int>& nums2, int k) {
        auto comp = [&nums1, &nums2](const Pair& a, const Pair& b) {  // 这种写法第一次见，学习了！
            return nums1[a.first] + nums2[a.second] > nums1[b.first] + nums2[b.second];
        };
        int m = nums1.size(), n = nums2.size();
        vector<vector<int>> res;
        priority_queue<Pair, vector<Pair>, decltype(comp)> pq(comp);  // decltype 和 pq(comp) 这种写法第一次见，学习了！
        for (int i = 0; i < min(m, k); i++) pq.emplace(i, 0);  // emplace 可以自动构造出 pair<int, int>，但 push 就不行，学习了！而且事先将一侧的组合添加进去，后续只对另一侧的索引+1，避免了重复项，真是巧妙！
        while (k-- > 0 && !pq.empty()) {  // 注意：可能出现组合数 m*n < k 的情况，此时将出现 pq 为空而 k 还是正整数的情况，所需需要加上 pq 不为空的判断
            auto [i, j] = pq.top();  // 这种写法也第一次见，学习了！
            pq.pop();
            res.emplace_back(initializer_list<int>{nums1[i], nums2[j]});  // 这种写法也第一次见，学习了！
            if (j+1 < n) pq.emplace(i, j+1);
        }
        return res;
    }
};
```

