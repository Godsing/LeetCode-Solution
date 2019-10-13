
## Problem

Given an array of *n* integers where *n* > 1, `nums`, return an array `output` such that `output[i]` is equal to the product of all the elements of `nums` except `nums[i]`.

Solve it **without division** and in O(*n*).

For example, given `[1,2,3,4]`, return `[24,12,8,6]`.

**Follow up:**
Could you solve it with constant space complexity? (Note: The output array **does not** count as extra space for the purpose of space complexity analysis.)



## Solution

First, consider O(n) time and O(n) space solution.

```c++
class Solution {
public:
    vector<int> productExceptSelf(vector<int>& nums) {
        int n=nums.size();
        vector<int> fromBegin(n);
        fromBegin[0]=1;
        vector<int> fromLast(n);
        fromLast[0]=1;
        
        for(int i=1;i<n;i++){
            fromBegin[i]=fromBegin[i-1]*nums[i-1];
            fromLast[i]=fromLast[i-1]*nums[n-i];
        }
        
        vector<int> res(n);
        for(int i=0;i<n;i++){
            res[i]=fromBegin[i]*fromLast[n-1-i];
        }
        return res;
    }
};

```

We just need to change the two vectors to two integers and note that we should do multiplying operations for two related elements of the results vector in each loop.

```c++
class Solution {
public:
    vector<int> productExceptSelf(vector<int>& nums) {
        int n=nums.size();
        int fromBegin=1;
        int fromLast=1;
        vector<int> res(n,1);
        
        for(int i=0;i<n;i++){ //累乘的过程中，每个中间值都被直接利用了，所以只需要用int而不需要数组
            res[i]*=fromBegin;
            fromBegin*=nums[i];
            res[n-1-i]*=fromLast; //相当精妙，每个结果由两次相乘得到
            fromLast*=nums[n-1-i];
        }
        return res;
    }
};
```

---

这道题没有想出解法。参考了其他人的解，相当赞叹。

很容易想到，要实现O(n)的时间复杂度，必然是累乘的过程被利用起来了。

但是如何有效的利用，就是对于这道题的精髓。从代码可以看出，最重要的是，将其分解为两个累乘的过程，这道题便得解。

看过了代码，自己实现了一遍，基本一样：

```c++
class Solution {
public:
    vector<int> productExceptSelf(vector<int>& nums) {
        int n = nums.size();
        vector<int> output(n, 1);
        int fromhead = 1, fromtail = 1;
        for (int i=0; i<n; i++) {
            output[i] *= fromhead;
            fromhead *= nums[i];
            output[n-1-i] *= fromtail;
            fromtail *= nums[n-1-i];
        }
        return output;
    }
};
```

