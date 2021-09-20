## Problem

Given an array of non-negative integers, you are initially positioned at the first index of the array.

Each element in the array represents your maximum jump length at that position.

Determine if you are able to reach the last index.

**Example 1:**

```
Input: [2,3,1,1,4]
Output: true
Explanation: Jump 1 step from index 0 to 1, then 3 steps to the last index.
```

**Example 2:**

```
Input: [3,2,1,0,4]
Output: false
Explanation: You will always arrive at index 3 no matter what. Its maximum
             jump length is 0, which makes it impossible to reach the last index.
```



## Solution

一开始想多了，采用递归 + 缓存（标记）的笨方式求解。如下：

```cpp
class Solution {
public:
    bool canJump(vector<int>& nums) {
        int N = nums.size();
        if (N == 1) return true;
        bool flag[N];
        fill_n(flag, N, true);
        return reachable(nums, flag, 0);
    }
    bool reachable(vector<int>& nums, bool flag[], int i) {  //检测下标为 i 的位置能否达到终点
        for (int k = 1; k <= nums[i]; k++) {
            if (!flag[i+k]) continue;  //已被标记为不可达，直接跳过，减少没必要的递归
            if (i+k+1 == nums.size()) return true;  //当前位置就是终点，返回true
            if (reachable(nums, flag, i+k)) return true;  //递归检测，若当前下标为 i+k 的位置能达到终点，返回true
            // flag[i+k] = false;  //下标为 i+k 的位置无法达到终点
        }
        flag[i] = false;  //for循环过后仍还没返回，说明从该点出发无论怎么跳都达到不了终点
        return false;
    }
};
```

该方法虽然解决了问题，但是运行速度很慢。下面参考其他人的方法。



## Debug&Learning

由于每层最多可以跳 A[i] 步，也可以跳0或1步，因此**如果能到达最高层，则说明每一层都可以到达**。有了这个条件，说明可以用贪心法。

思路一：正向，从0出发，一层一层网上跳，**看最后能不能超过最高层，能超过，说明能到达**，否则不能到达。

思路二：逆向，从最高层下楼梯，一层一层下降，看最后能不能下降到第0层。

思路三：如果不敢用贪心，可以用动规，设状态为 f[i] ，表示从第0层出发，走到 A[i] 时剩余的最大步数，则状态转移方程为：
$$
f[i] = max(f[i-1], A[i-1])-1, i > 0
$$
思路1：

```cpp
// LeetCode, Jump Game
// 思路1，时间复杂度O(n)，空间复杂度O(1)
class Solution {
public:
    bool canJump(const vector<int>& nums) {
        int reach = 1; // 最右能跳到哪里，这里 1 表示位置 nums[0]
        for (int i = 0; i < reach && reach < nums.size(); ++i)
            reach = max(reach,  i + 1 + nums[i]);
        return reach >= nums.size();
    }
};
//我理解了思路之后，自己实现了一遍，如下：（和上面差不多）
class Solution {
public:
    bool canJump(vector<int>& nums) {
        int reach = nums[0];
        for (int i = 1; i <= reach && reach < nums.size(); i++)
            reach = max(reach, i+nums[i]);
        return reach >= nums.size()-1;
    }
};
```

思路2：

```cpp
// LeetCode, Jump Game
// 思路2，时间复杂度O(n)，空间复杂度O(1)
class Solution {
public:
    bool canJump (const vector<int>& nums) {
        if (nums.empty()) return true;
        // 逆向下楼梯，最左能下降到第几层
        int left_most = nums.size() - 1;

        for (int i = nums.size() - 2; i >= 0; --i)
            if (i + nums[i] >= left_most)
                left_most = i;

        return left_most == 0;
    }
};
```

思路3：

```cpp
// LeetCode, Jump Game
// 思路三，动规，时间复杂度O(n)，空间复杂度O(n)
class Solution {
public:
    bool canJump(const vector<int>& nums) {
        vector<int> f(nums.size(), 0);
        f[0] = 0;  //f[i]表示走到nums[i]时剩余的最大步数
        for (int i = 1; i < nums.size(); i++) {
            f[i] = max(f[i - 1], nums[i - 1]) - 1;
            if (f[i] < 0) return false;;
        }
        return f[nums.size() - 1] >= 0;
    }
};
```

下面代码与思路3类似，但是不需要用到数组，因为实际上每次更新 f[i] 的时候只需要用到上一次的值，数组是多余的。代码：

```cpp
class Solution {
public:
    bool canJump(vector<int>& nums) {
        int buf = 1;
        for(auto num:nums){
            if (buf > 0) buf = max(buf-1, num);
            else return false;
        }
        return true;
    }
};
```

2019-05-29：

```c++
class Solution {
public:
    bool canJump(vector<int>& nums) {
        int pos = 0, up = 0;
        while (pos <= up) {
            up = max(up, pos + nums[pos]);
            if (up >= nums.size() - 1) return true;
            pos++;
        }
        return false;
    }
};
```



