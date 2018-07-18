## Problem

Say you have an array for which the *i*th element is the price of a given stock on day *i*.

Design an algorithm to find the maximum profit. You may complete at most *two* transactions.

**Note: **You may not engage in multiple transactions at the same time (i.e., you must sell the stock before you buy again).

**Example 1:**

```
Input: [3,3,5,0,0,3,1,4]
Output: 6
Explanation: Buy on day 4 (price = 0) and sell on day 6 (price = 3), profit = 3-0 = 3.
             Then buy on day 7 (price = 1) and sell on day 8 (price = 4), profit = 4-1 = 3.
```

**Example 2:**

```
Input: [1,2,3,4,5]
Output: 4
Explanation: Buy on day 1 (price = 1) and sell on day 5 (price = 5), profit = 5-1 = 4.
             Note that you cannot buy on day 1, buy on day 2 and sell them later, as you are
             engaging multiple transactions at the same time. You must sell before buying again.
```

**Example 3:**

```
Input: [7,6,4,3,1]
Output: 0
Explanation: In this case, no transaction is done, i.e. max profit = 0.
```



## Solution

对于这道题，我们可以把 prices 数组切割成两块分别求最大利润的一次交易。切割的点有 prices.size() 种选择，可以在第 0 个元素、或第 1 个 …… 或最后一个的后面。因此，目标是找到最佳的切割点。

```cpp
class Solution {
public:
    int maxProfit(vector<int>& prices) {
	    int len = prices.size();
        if (len <= 1) return 0;
      
        int buy_price = prices[0], sell_price = prices[len - 1], max_profit = 0;
        vector<int> left_profit(len), right_profit(len);
        left_profit[0] = 0, right_profit[len - 1] = 0;
        //left_profit[i]表示day [0:i] 这段时间内一次交易所可能获得的最大收益
        for (int i = 1; i < len; i++) {
            left_profit[i] = max(left_profit[i - 1], prices[i] - buy_price);
            buy_price = min(buy_price, prices[i]);
        }
        //right_profit[i]表示day [i:len-1] 这段时间内一次交易所可能获得的最大收益
        for (int i = len - 2; i >= 0; i--) {
            right_profit[i] = max(right_profit[i + 1], sell_price - prices[i]);
            sell_price = max(sell_price, prices[i]);
        }
        // 在前 len - 1 个切割点中找最佳的点，即两次交易最佳的时间分隔点
        for (int i = 0; i < len -1; i++) { 
            max_profit = max(max_profit, left_profit[i] + right_profit[i+1]);
        }
        return max(max_profit, left_profit[len - 1]);  // 已知的最佳情况和最后一个切割点的情况做比较
    }
};
```



### A more concise [solution](https://leetcode.com/problems/best-time-to-buy-and-sell-stock-iii/discuss/39611/Is-it-Best-Solution-with-O(n)-O(1).) posted by [weijiac](https://leetcode.com/weijiac) :

**Is it Best Solution with O(n), O(1).**

The thinking is simple and is inspired by the best solution from Single Number II (I read through the discussion after I use DP).
Assume we only have 0 money at first;
4 Variables to maintain some interested ‘ceilings’ so far:
The maximum of if we’ve just buy 1st stock, if we’ve just sold 1nd stock, if we’ve just buy 2nd stock, if we’ve just sold 2nd stock.
Very simple code too and work well. I have to say the logic is simple than those in Single Number II.

```java
public class Solution {
    public int maxProfit(int[] prices) {
        int hold1 = Integer.MIN_VALUE, hold2 = Integer.MIN_VALUE;
        int release1 = 0, release2 = 0;
        for(int i:prices){                              // Assume we only have 0 money at first
            release2 = Math.max(release2, hold2+i);     // The maximum if we've just sold 2nd stock so far.
            hold2    = Math.max(hold2,    release1-i);  // The maximum if we've just buy  2nd stock so far.
            release1 = Math.max(release1, hold1+i);     // The maximum if we've just sold 1nd stock so far.
            hold1    = Math.max(hold1,    -i);          // The maximum if we've just buy  1st stock so far. 
        }
        return release2; ///Since release1 is initiated as 0, so release2 will always higher than release1.
    }
}
```

