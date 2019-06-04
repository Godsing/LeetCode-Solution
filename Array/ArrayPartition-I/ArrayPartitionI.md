## Problem

Given an array of **2n** integers, your task is to group these integers into **n** pairs of integer, say $(a_1, b_1), (a_2, b_2), ..., (a_n, b_n) $ which makes sum of min $(a_i, b_i)$ for all i from 1 to n as large as possible.

**Example 1:**

```
Input: [1,4,3,2]

Output: 4
Explanation: n is 2, and the maximum sum of pairs is 4 = min(1, 2) + min(3, 4).
```

**Note:**

1. **n** is a positive integer, which is in the range of [1, 10000].
2. All the integers in the array will be in the range of [-10000, 10000].

---

## Solution

### I have a conjecture:

Sort the array in ascending order. From the first one, make every two number as a pair of integer. Now, we get n pairs of integer. The sum of the smaller integer in every pair will be larger than any other possible cases of grouping these integers.

I don't know how to prove it, so I am not sure it is right.

### Have a try:

```C++
class Solution {
public:
    int arrayPairSum(vector<int>& nums) {
        int size = nums.size();
        quickSort(nums, 0, size-1); //Actually, we can use the built-in function "sort(nums.begin(), nums.end())" instead.
        int result = 0; // Initial, or the output will be wrong.
        for(int i = 0; i < size; i += 2){
            result += nums[i];
        }
        return result;
    }
    // I want to review the QuickSort algo., so I implement quickSort() myself instead of using built-in function sort()
    void swap(int &a, int &b){
      int c = a;
      a = b;
      b = c;
    }

    int partition(vector<int> &arr, int left, int right){
      int pivot = arr[left];
      int i = left;
      for(int j = left+1; j <= right; j++)
        if(arr[j] <= pivot)
          swap(arr[++i], arr[j]);

      swap(arr[i], arr[left]);
      return i;
    }

    void quickSort(vector<int> &arr, int left, int right){
      if(left < right){
        int mid = partition(arr, left, right);
        //Watch out! The mid position is on the place, so we don't need to consider it again.
        //That's why below is mid-1, not mid! Otherwise it will occur overflow error!!!  
        quickSort(arr, left, mid-1);
        quickSort(arr, mid+1, right);
      }
    }
};

```

Concise Version：

```c++
class Solution {
public:
    int arrayPairSum(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        int result = 0;
        for(int i=0; i<nums.size(); i+=2){
            result += nums[i];
        }
        return result;
    }
};
```

The solution was **accepted**! So, my conjecture is right. 证明如下：

假设有一对数字 (a, b) ，a < b，但若两者不是紧邻的，比如说有一个数 c 介于 a、b 之间。那么和 c 配对的数 d 不管大小如何，我们会发现 (a, b)、(c, d)（或(d, c)） 这样的配对方式一定不是最佳的。所以，反之可以得到，最佳的配对方式一定是 a、b 紧邻的。因此，从小到大，两两配对，才是最佳的配对方式。

---

### Further Analysis

Time:  O(nlogn)
Space: O(1)

- Another faster solution

```c++
// Time:  O(r), r is the range size of the integers
// Space: O(r)

class Solution {
public:
    int arrayPairSum(vector<int>& nums) {
        const auto LEFT = -10000;
        const auto RIGHT = 10000;
       \ vector<int> lookup(RIGHT - LEFT + 1, 0);
        for (const auto& num: nums) {
            ++lookup[num - LEFT];
        }
        auto r = 0, result = 0;
        for (int i = LEFT; i <= RIGHT; ++i) {
            result += (lookup[i - LEFT] + 1 - r) / 2 * i;
            r = (lookup[i - LEFT] + r) % 2;
        }
        return result;
    }
};
```

What does the code mean?

