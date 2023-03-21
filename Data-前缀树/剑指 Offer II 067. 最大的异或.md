## 题目

给你一个整数数组 `nums` ，返回 `nums[i] XOR nums[j]` 的最大运算结果，其中 `0 ≤ i ≤ j < n` 。

**进阶：**你可以在 `O(n)` 的时间解决这个问题吗？

 

**示例 1：**

```
输入：nums = [3,10,5,25,2,8]
输出：28
解释：最大运算结果是 5 XOR 25 = 28.
```

**示例 2：**

```
输入：nums = [0]
输出：0
```

**示例 3：**

```
输入：nums = [2,4]
输出：6
```

**示例 4：**

```
输入：nums = [8,10,2]
输出：10
```

**示例 5：**

```
输入：nums = [14,70,53,83,49,91,36,80,92,51,66,70]
输出：127
```

 

**提示：**

- `1 <= nums.length <= 2 * 10^4`
- `0 <= nums[i] <= 2^31 - 1`



注意：本题与主站 421 题相同： https://leetcode-cn.com/problems/maximum-xor-of-two-numbers-in-an-array/



来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/ms70jA

## 题解

### 方法一：字典树

参考自[官方题解](https://leetcode-cn.com/problems/ms70jA/solution/zui-da-de-yi-huo-by-leetcode-solution-hr7m/)的方法二，不过我做了轻微调整，将字典树的 `insert` 函数放在其内部实现，故字典树实现方式为`class`，而不是`struct`。原题解中采用 `struct`，更加轻量，也不失为一种好的选择。

其中值得一提的是，采用左右孩子节点来表示 `0` 和 `1` ，是一种不错的思路。

```c++
class Trie {
public:
    Trie* l = nullptr;
    Trie* r = nullptr;
    Trie() {}
    void insert(int val) {
        Trie* node = this;
        for (int i = 30; i >= 0; i--) {
            if ((val >> i) & 1) {
                if (!node->r) node->r = new Trie();
                node = node->r;
            } else {
                if (!node->l) node->l = new Trie();
                node = node->l;
            }
        }
    }
};

class Solution {
private:
    Trie* trie = new Trie();

public:
    int check(int num) {
        Trie* cur = trie;
        int x = 0;
        for (int k = 30; k >= 0; --k) {
            int bit = (num >> k) & 1;
            if (bit == 0) {
                // a_i 的第 k 个二进制位为 0，应当往表示 1 的子节点 right 走
                if (cur->r) {
                    cur = cur->r;
                    x = x * 2 + 1;
                }
                else {
                    cur = cur->l;
                    x = x * 2;
                }
            }
            else {
                // a_i 的第 k 个二进制位为 1，应当往表示 0 的子节点 left 走
                if (cur->l) {
                    cur = cur->l;
                    x = x * 2 + 1;
                }
                else {
                    cur = cur->r;
                    x = x * 2;
                }
            }
        }
        return x;
    }

    int findMaximumXOR(vector<int>& nums) {
        int res = 0;
        for (int i = 1; i < nums.size(); i++) {
            trie->insert(nums[i-1]);
            res = max(res, check(nums[i]));
        }
        return res;
    }
};
// 执行用时：220 ms, 在所有 C++ 提交中击败了59.41%的用户
// 内存消耗：63.6 MB, 在所有 C++ 提交中击败了85.19%的用户
```



改进：做了些剪枝。

```c++
class Trie {
public:
    Trie* l = nullptr;
    Trie* r = nullptr;
    Trie() {}
    void insert(int val) {
        Trie* node = this;
        for (int i = 30; i >= 0; i--) {
            if ((val >> i) & 1) {
                if (!node->r) node->r = new Trie();
                node = node->r;
            } else {
                if (!node->l) node->l = new Trie();
                node = node->l;
            }
        }
    }
};

class Solution {
private:
    Trie* trie = new Trie();

public:
    void check(int num, bool* res) {
        Trie* cur = trie;
        bool has_check_first_diff = false;
        for (int k = 30; k >= 0; --k) {
            int bit = (num >> k) & 1;
            bool res_bit = false;
            if (bit == 0) {
                if (cur->r) {
                    cur = cur->r;
                    res_bit = true;
                } else cur = cur->l;
            } else {
                if (cur->l) {
                    cur = cur->l;
                    res_bit = true;
                }
                else cur = cur->r;
            }
            if (!has_check_first_diff && res_bit != res[k]) {
                if (!res_bit) return ;  //对于第一个与现有结果不同的位，如果当前值为0，则直接退出
                else has_check_first_diff = true;
            }
            res[k] = res_bit;
        }
    }

    int findMaximumXOR(vector<int>& nums) {
        bool* res = new bool[31];
        fill_n(res, 31, false);
        for (int i = 1; i < nums.size(); i++) {
            trie->insert(nums[i-1]);
            check(nums[i], res);
        }
        int result = 0;
        for (int i = 0; i < 31; i++) {
            if (res[i]) result += (1 << i);
        }
        return result;
    }
};
```



### 方法二：哈希表

```c++
class Solution {
private:
    // 最高位的二进制位编号为 30
    static constexpr int HIGH_BIT = 30;

public:
    int findMaximumXOR(vector<int>& nums) {
        int x = 0;
        for (int k = HIGH_BIT; k >= 0; --k) {
            unordered_set<int> seen;
            // 将所有的 pre^k(a_j) 放入哈希表中
            for (int num: nums) {
                // 如果只想保留从最高位开始到第 k 个二进制位为止的部分
                // 只需将其右移 k 位
                seen.insert(num >> k);
            }

            // 目前 x 包含从最高位开始到第 k+1 个二进制位为止的部分
            // 我们将 x 的第 k 个二进制位置为 1，即为 x = x*2+1
            int x_next = x * 2 + 1;
            bool found = false;
            
            // 枚举 i
            for (int num: nums) {
                if (seen.count(x_next ^ (num >> k))) {
                    found = true;
                    break;
                }
            }

            if (found) {
                x = x_next;
            }
            else {
                // 如果没有找到满足等式的 a_i 和 a_j，那么 x 的第 k 个二进制位只能为 0
                // 即为 x = x*2
                x = x_next - 1;
            }
        }
        return x;
    }
};
// 链接：https://leetcode-cn.com/problems/ms70jA/solution/zui-da-de-yi-huo-by-leetcode-solution-hr7m/
```

