## 题目

给定一个 24 小时制（小时:分钟 **"HH:MM"**）的时间列表，找出列表中任意两个时间的最小时间差并以分钟数表示。

 

**示例 1：**

```
输入：timePoints = ["23:59","00:00"]
输出：1
```

**示例 2：**

```
输入：timePoints = ["00:00","23:59","00:00"]
输出：0
```

 

**提示：**

- `2 <= timePoints.length <= 2 * 10^4`
- `timePoints[i]` 格式为 **"HH:MM"**



注意：本题与主站 539 题相同： https://leetcode-cn.com/problems/minimum-time-difference/





## 题目

```python
class Solution:
    def findMinDifference(self, timePoints: List[str]) -> int:
        mins = []
        for t in timePoints:
            mins.append(int(t[:2])*60 + int(t[-2:]))
        mins = sorted(mins)
        mins.append(mins[0] + 24*60)
        res = 24*60
        for i in range(len(mins)-1):
            res = min(res, mins[i+1] - mins[i])
        return res
```

