## 题目

给你一个包含 `n` 个整数的数组 `nums`，判断 `nums` 中是否存在三个元素 *a，b，c ，*使得 *a + b + c =* 0 ？请你找出所有和为 `0` 且不重复的三元组。

**注意：**答案中不可以包含重复的三元组。



**示例 1：**

```
输入：nums = [-1,0,1,2,-1,-4]
输出：[[-1,-1,2],[-1,0,1]]
```

**示例 2：**

```
输入：nums = []
输出：[]
```

**示例 3：**

```
输入：nums = [0]
输出：[]
```

 

**提示：**

- `0 <= nums.length <= 3000`
- `-105 <= nums[i] <= 105`


注意：本题与主站 15 题相同：https://leetcode-cn.com/problems/3sum/



来源：力扣（LeetCode）
本题链接：https://leetcode-cn.com/problems/1fGaJU



## 题解

本题可以视为《剑指 Offer II 006. 排序数组中两个数字之和》的进阶版。

这道题有三个要求：

1. 需要是 3 个元素之和，而不是 2 个；
2. 要找的是所有的三元组，而不是只需要找到一个；
3. 要求三元组不能有重复。



首先考虑，对于无序数组，要找到和为某个target的两元组，有几种常见办法：

- 嵌套遍历（双重 for 循环），时间复杂度 $O(N^2)$, 空间复杂度 O(1)；
- 先排序，再夹逼，时间复杂度 $O(Nlog_2N)$, 空间复杂度 O(1) (原地排序) 或 O(N)；
- 构建哈希表，然后遍历，时间复杂度 O(N), 空间复杂度 O(N)；



因此，若要找到和为某个target的三元组，我们可以：

- 嵌套遍历（三重 for 循环），时间复杂度 $O(N^3)$, 空间复杂度 O(1)；
- 先排序，再遍历，最后对剩余部分夹逼，时间复杂度 $O(Nlog_2N)+O(N^2)≈O(N^2)$, 空间复杂度 O(1) (原地排序) 或 O(N)；
- 构建哈希表，然后嵌套遍历(双重)，时间复杂度 $O(N^2)$, 空间复杂度 O(N)；



进而，要找到所有符合要求的三元组，只需将遍历进行到底即可，不会影响时间复杂度。



而要求三元组不能重复：

- 对于第二种方法（先排序、再遍历），需要在遍历过程中，跳过相同的元素；
- 对于第三种方法（构建哈希表），需要在构建时去重、遍历时按照某个固定的顺序进行。



下面的代码采用第二种方法实现：

```c++
class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        vector<vector<int>> res;
        if (nums.size() < 3) return res;  //切勿忘记对特殊情况的处理
        sort(nums.begin(), nums.end());
        for (int i = 0; i < nums.size() - 2; i++) {
            int j = i + 1, k = nums.size() - 1;
            while (j < k) {
                if (nums[j] + nums[k] + nums[i] == 0) {
                    res.push_back({nums[i], nums[j], nums[k]});
                    j++; k--;
                    // 需要找到不同的值，避免重复。只是 j++; k--; 是不行的，例如对于输入: [-2,0,0,2,2]
                    while (j < nums.size() && nums[j] == nums[j-1]) j++;
                    while (k >= 0 && nums[k] == nums[k+1]) k--;
                } else if (nums[j] + nums[k] + nums[i] < 0) j++;
                else k--;
            }
            //直接判断 i+1 < nums.size() 就行了，不用 i+1 < nums.size() - 2，因为循环中已经有判断了
            while (i+1 < nums.size() && nums[i+1] == nums[i]) i++;
        }
        return res;
    }
};
```

