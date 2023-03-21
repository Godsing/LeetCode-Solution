## 题目

请根据每日 `气温` 列表 `temperatures` ，请计算在每一天需要等几天才会有更高的温度。如果气温在这之后都不会升高，请在该位置用 `0` 来代替。

**示例 1:**

```
输入: temperatures = [73,74,75,71,69,72,76,73]
输出: [1,1,4,2,1,1,0,0]
```

**示例 2:**

```
输入: temperatures = [30,40,50,60]
输出: [1,1,1,0]
```

**示例 3:**

```
输入: temperatures = [30,60,90]
输出: [1,1,0]
```

 

**提示：**

- `1 <= temperatures.length <= 10^5`
- `30 <= temperatures[i] <= 100`



注意：本题与主站 739 题相同： https://leetcode-cn.com/problems/daily-temperatures/



## 题解

```c++
class Solution {
public:
    vector<int> dailyTemperatures(vector<int>& temperatures) {
        // 用一个栈来保存从右向左遍历过程中，当前索引右侧算起的递增子序列的索引
        stack<int> greater;
        vector<int> wait(temperatures.size());
        for (int i = temperatures.size() - 1; i >= 0; i--) {
            while (!greater.empty() && temperatures[greater.top()] <= temperatures[i]) greater.pop();
            if (greater.empty()) wait[i] = 0;
            else wait[i] = greater.top() - i;
            greater.push(i);
        }
        return wait;
    }
};
```

