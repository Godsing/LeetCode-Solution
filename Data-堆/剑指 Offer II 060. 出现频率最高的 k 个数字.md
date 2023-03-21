## 题目

给你一个整数数组 `nums` 和一个整数 `k` ，请你返回其中出现频率前 `k` 高的元素。你可以按 **任意顺序** 返回答案。

 

**示例 1:**

```
输入: nums = [1,1,1,2,2,3], k = 2
输出: [1,2]
```

**示例 2:**

```
输入: nums = [1], k = 1
输出: [1]
```

 

**提示：**

- `1 <= nums.length <= 10^5`
- `k` 的取值范围是 `[1, 数组中不相同的元素的个数]`
- 题目数据保证答案唯一，换句话说，数组中前 `k` 个高频元素的集合是唯一的

 

**进阶：**你所设计算法的时间复杂度 **必须** 优于 `O(n log n)` ，其中 `n` 是数组大小。



注意：本题与主站 347 题相同：https://leetcode-cn.com/problems/top-k-frequent-elements/



## 题解

```c++
class Solution {
private:
    typedef pair<int, int> Pair;
    class myComp {
    public:
        bool operator() (const Pair& p1, const Pair& p2) {  // 自定义比较函数
            return p1.second > p2.second;  // 大于号，对应的是最小堆
        }
    };
public:
    vector<int> topKFrequent(vector<int>& nums, int k) {
        unordered_map<int, int> cnt;
        for (int num : nums) cnt[num]++;
        priority_queue<Pair, vector<Pair>, myComp> pq;
        for (auto it=cnt.begin(); it!=cnt.end(); it++) {
            Pair p = make_pair(it->first, it->second);
            if (pq.size() < k) pq.push(p);
            else if (p.second > pq.top().second) {
                pq.pop();
                pq.push(p);
            }
        }
        vector<int> res;
        while (!pq.empty()) {
            res.push_back(pq.top().first);
            pq.pop();
        }
        return res;
    }
};
```

