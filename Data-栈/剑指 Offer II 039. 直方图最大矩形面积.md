## 题目

给定 *n* 个非负整数，用来表示柱状图中各个柱子的高度。每个柱子彼此相邻，且宽度为 1 。

求在该柱状图中，能够勾勒出来的矩形的最大面积。

 

**示例 1:**

![img](https://mdpicbed.oss-cn-hongkong.aliyuncs.com/imgs/histogram.jpg)

```
输入：heights = [2,1,5,6,2,3]
输出：10
解释：最大的矩形为图中红色区域，面积为 10
```

**示例 2：**

![img](https://mdpicbed.oss-cn-hongkong.aliyuncs.com/imgs/histogram-1.jpg)

```
输入： heights = [2,4]
输出： 4
```

 

**提示：**

- `1 <= heights.length <=10^5`
- `0 <= heights[i] <= 10^4`



注意：本题与主站 84 题相同： https://leetcode-cn.com/problems/largest-rectangle-in-histogram/



来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/0ynMMM
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。



## 题解

```c++
class Solution {
public:
    int largestRectangleArea(vector<int>& heights) {
        stack<int> forward_smaller_idx;
        stack<int> backward_smaller_idx;
        vector<int> forward_smaller(heights.size());  // 保存往右下一个更小的元素的索引
        vector<int> backward_smaller(heights.size());  // 保存往左下一个更小的元素的索引
        for (int i = 0; i < heights.size(); i++) {
            while (!backward_smaller_idx.empty() && heights[backward_smaller_idx.top()] >= heights[i]) backward_smaller_idx.pop();
            if (backward_smaller_idx.empty()) backward_smaller[i] = -1;
            else backward_smaller[i] = backward_smaller_idx.top();
            backward_smaller_idx.push(i);
        }
        for (int j = heights.size() - 1; j >= 0; j--) {
            while (!forward_smaller_idx.empty() && heights[forward_smaller_idx.top()] >= heights[j]) forward_smaller_idx.pop();
            if (forward_smaller_idx.empty()) forward_smaller[j] = heights.size();
            else forward_smaller[j] = forward_smaller_idx.top();
            forward_smaller_idx.push(j);
        }
        int res = 0;
        for (int k = 0; k < heights.size(); k++) {
            // 每个元素的高度*左右两侧所能延伸的最远距离，即是当前元素所能参与组成的最大矩形
            res = max(heights[k] * (forward_smaller[k] - backward_smaller[k] - 1), res);
        }
        return res;
    }
};
```



其实只需要用到 backward_smaller，然后在出栈前，以该栈顶对应元素的值作为高度，[栈顶, 当前索引) 作为矩形宽度即可。

```c++
class Solution {
public:
    int largestRectangleArea(vector<int>& heights) {
        stack<int> sta;
        sta.push(-1);
        int maxArea = 0;
        for (int i = 0; i < heights.size(); ++i) {
            while (sta.top() != -1 && heights[sta.top()] >= heights[i]) {
                int height = heights[sta.top()];
                sta.pop();
                int width = i - sta.top() - 1;
                maxArea = max(maxArea, height * width);
            }
            sta.push(i);
        }

        while (sta.top() != -1) {
            int height = heights[sta.top()];
            sta.pop();
            int width = heights.size() - sta.top() - 1;
            maxArea = max(maxArea, height * width);
        }
        return maxArea;
    }
};
```

作者：master_xue
链接：https://leetcode-cn.com/problems/0ynMMM/solution/jian-zhi-offer-2-mian-shi-ti-39-shu-zhon-qzaw/
来源：力扣（LeetCode）