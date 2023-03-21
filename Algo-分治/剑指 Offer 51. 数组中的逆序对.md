## 题目

在数组中的两个数字，如果前面一个数字大于后面的数字，则这两个数字组成一个逆序对。输入一个数组，求出这个数组中的逆序对的总数。

示例 1:

```
输入: [7,5,6,4]
输出: 5
```

限制：0 <= 数组长度 <= 50000

来源：力扣（LeetCode） 链接：https://leetcode-cn.com/problems/shu-zu-zhong-de-ni-xu-dui-lcof



## 题解

采用分治的思想，在归并排序的过程中进行统计。 在合并两个已排序的子序列过程中，当右侧出现更小的数字时，意味着所有左侧中未归并的数字与 nums[j] 都构成了逆序。

```c++
class Solution {
public:
    int mergeSort(vector<int>& nums, vector<int>& tmp, int l, int r) {
        if (l >= r) return 0;
        int mid = (l + r) >> 1;
        int res = mergeSort(nums, tmp, l, mid) + mergeSort(nums, tmp, mid+1, r);
        int i = l, j = mid+1, idx = l;
        while (i <= mid && j <= r) {
            if (nums[j] < nums[i]) {
                tmp[idx] = nums[j++];
                res += (mid - i + 1);  //当右侧出现更小的数字时，所有左侧中未归并的数字与nums[j]就构成了逆序
            } else {
                tmp[idx] = nums[i++];
            }
            idx++;
        }
        for (int k = i; k <= mid; k++) {
            tmp[idx++] = nums[k];
        }
        for (int k = j; k <= r; k++) {
            tmp[idx++] = nums[k];
        }
        copy(tmp.begin() + l, tmp.begin() + r + 1, nums.begin() + l);
        return res;
    }

    int reversePairs(vector<int>& nums) {
        int n = nums.size();
        vector<int> tmp(n);
        return mergeSort(nums, tmp, 0, n - 1);
    }
};
```

