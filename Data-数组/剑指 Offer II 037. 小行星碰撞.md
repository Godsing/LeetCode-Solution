## 题目

给定一个整数数组 `asteroids`，表示在同一行的行星。

对于数组中的每一个元素，其绝对值表示行星的大小，正负表示行星的移动方向（正表示向右移动，负表示向左移动）。每一颗行星以相同的速度移动。

找出碰撞后剩下的所有行星。碰撞规则：两个行星相互碰撞，较小的行星会爆炸。如果两颗行星大小相同，则两颗行星都会爆炸。两颗移动方向相同的行星，永远不会发生碰撞。

 

**示例 1：**

```
输入：asteroids = [5,10,-5]
输出：[5,10]
解释：10 和 -5 碰撞后只剩下 10 。 5 和 10 永远不会发生碰撞。
```

**示例 2：**

```
输入：asteroids = [8,-8]
输出：[]
解释：8 和 -8 碰撞后，两者都发生爆炸。
```

**示例 3：**

```
输入：asteroids = [10,2,-5]
输出：[10]
解释：2 和 -5 发生碰撞后剩下 -5 。10 和 -5 发生碰撞后剩下 10 。
```

**示例 4：**

```
输入：asteroids = [-2,-1,1,2]
输出：[-2,-1,1,2]
解释：-2 和 -1 向左移动，而 1 和 2 向右移动。 由于移动方向相同的行星不会发生碰撞，所以最终没有行星发生碰撞。 
```

 

**提示：**

- `2 <= asteroids.length <= 10^4`
- `-1000 <= asteroids[i] <= 1000`
- `asteroids[i] != 0`



注意：本题与主站 735 题相同： https://leetcode-cn.com/problems/asteroid-collision/



## 题解

此题难度不大，但需要注意细节，分情况处理。另外，将行星碰撞过程独立出来作为函数，可便于进行递归(持续爆炸)，较少代码量。

注意最后将栈中的数据按顺序保存也是有技巧的。

```c++
class Solution {
public:
    void collide(stack<int>& rest, int ast) {
        if (!rest.empty() && rest.top() > 0 && ast < 0) {  // 判断是否能碰撞
            if (ast == INT_MIN || -ast > rest.top()) {
                rest.pop();
                collide(rest, ast);  //
            } else if (-ast == rest.top()) {
                rest.pop();
                return;
            } else return;
        } else {
            rest.push(ast);
            return;
        }
    }

    vector<int> asteroidCollision(vector<int>& asteroids) {
        stack<int> rest;
        for (int ast : asteroids) {
            collide(rest, ast);
        }
        vector<int> res;
        for (int i = res.size() - 1; i >= 0; i--) {
            res[i] = rest.top();
            rest.pop();
        }
        // while (!rest.empty()) {  // 这种写法过于耗时
        //     res.push_back(rest.top());
        //     rest.pop();
        // }
        // reverse(res.begin(), res.end());
        return res;
    }
};
```



另外，参考[这个题解](https://leetcode-cn.com/problems/XagZNi/solution/shua-chuan-jian-zhi-offer-day17-zhan-i-0-5yho/)，可以用“循环+适时的continue(以避免索引+1)”来实现类似递归的效果，十分巧妙：

```python
class Solution:
    def asteroidCollision(self, asteroids):
        s, p = [], 0
        while p < len(asteroids):
            if not s or s[-1] < 0 or asteroids[p] > 0:
                s.append(asteroids[p])
            elif s[-1] <= -asteroids[p]:
                if s.pop() < -asteroids[p]:
                    continue
            p += 1
        return s
```

为了提高可读性，这是我还原后的版本：

```python
class Solution:
    def asteroidCollision(self, asteroids: List[int]) -> List[int]:
        st, i = [], 0
        while i < len(asteroids):
            if not st or st[-1] < 0 or asteroids[i] > 0:  # 不会发生碰撞
                st.append(asteroids[i])
                i += 1
            elif st[-1] <= -asteroids[i]:  # 会碰撞
                left = st.pop()  # 左边星球被撞没
                if left < -asteroids[i]:  # 需要继续撞
                    continue
                else:  # 和左边星球相互抵消，不需要继续撞
                    i += 1
            else:  # 当前星球被撞没
                i += 1
        return st
```

