[TOC]

## Problem

Your are given an array of integers `prices`, for which the `i`-th element is the price of a given stock on day `i`; and a non-negative integer `fee` representing a transaction fee.

You may complete as many transactions as you like, but you need to pay the transaction fee for each transaction. You may not buy more than 1 share of a stock at a time (ie. you must sell the stock share before you buy again.)

Return the maximum profit you can make.

**Example 1:**

```
Input: prices = [1, 3, 2, 8, 4, 9], fee = 2
Output: 8
Explanation: The maximum profit can be achieved by:
Buying at prices[0] = 1
Selling at prices[3] = 8
Buying at prices[4] = 4
Selling at prices[5] = 9
The total profit is ((8 - 1) - 2) + ((9 - 4) - 2) = 8.
```

**Note:**

`0 < prices.length <= 50000`.

`0 < prices[i] < 50000`.

`0 <= fee < 50000`.



## Solution

这道题相比于 [BestTimeToBuyandSellStock-II](../BestTimeToBuyandSellStock-II/BestTimeToBuyandSellStock-II.md) ，多了一个条件：每一次交易，都要计算交易费用。因此，我们要在 BestTimeToBuyandSellStock-II 方案二的基础上增加两个限制：

1. 只有上涨差价超过交易费用，也就是利润为正，才记录一个**等待确认**的交易；

2. 为保证利润最高，只在下跌差价超过交易费用时，才确认上一次的交易有效，计入总利润。

在 [BestTimeToBuyandSellStock-II](../BestTimeToBuyandSellStock-II/BestTimeToBuyandSellStock-II.md) 的第二个解决方案中，我们已经按波段考虑了价格的上升和下降，只是没有考虑交易费用。因此只需要在此基础上增加交易费用，适当修改即可。如下：

``` cpp
class Solution {
public:
    int maxProfit(vector<int>& prices, int fee) {
        if (prices.size() <= 1) return 0; // if no transaction can be done, profit is 0.
        int max_profit = 0, buyprice = prices[0], sellprice = 0;
        bool up = false;  // a flag, "true" means the price is going up beyond fee
        for (int i = 1; i < prices.size(); i++) {
            if (prices[i] < prices[i - 1]) {
                if (up && sellprice - prices[i] > fee) {  // every time the price going up then down beyond fee, confirm sellling the stock
                    max_profit += (sellprice - buyprice - fee);
                    up = false;
                    buyprice = prices[i];  // buy the stock at lower price
                }
                if (!up) buyprice = min(buyprice, prices[i]);  
              // because of fee, current price not always lower than current best buyprice when prices going down, e.g prices = [1, 5, 3, 4, 8], fee = 3, the 3 lower than 5, but not lower than current best sbuyprice 1.
            }
            if (prices[i] >= prices[i - 1]) {
                if (!up && prices[i] - buyprice > fee) {
                    up = true;  // when the price going down then up beyond fee, set flag, means that the price is "truly" going up
                    sellprice = prices[i];
                }
                if (up) sellprice = max(sellprice, prices[i]);  
              // because of fee, current price not always greater than current best sellprice when prices going up, e.g prices = [1, 5, 3, 4, 8], fee = 3, the 4 greater than 3, but not greater than current best sellprice 5.
            }
        }
        if (up) max_profit += (sellprice - buyprice - fee);  // if price array ends with "truly going up", add the profit of last transantion
        return max_profit;
    }
};
```

模仿下面写了一个动态规划的版本：

```cpp
class Solution {
public:
    int maxProfit(vector<int>& prices, int fee) {
        //因为这里把交易费用 fee 的扣除放在了卖出阶段，所以 have_1 不能设置为 INT_MIN，否则可能导致 (have_1 + p - fee) 下溢变成正数。
        int have_0 = 0, have_1 = -50000;
        for (int p : prices) {
            int tmp = have_0;
            have_0 = max(have_0, have_1 + p - fee);  //卖出阶段才扣除交易费用 fee
            have_1 = max(have_1, tmp - p);
        }
        return have_0;
    }
};
```



---

### **A more concise [solution](https://leetcode.com/problems/best-time-to-buy-and-sell-stock-with-transaction-fee/discuss/108867/C++-concise-solution-O(n)-time-O(1)-space) posted by [zestypanda](https://leetcode.com/zestypanda) :**

The solution maintains two **states**:

```
s0 = profit having no stock
s1 = profit having 1 stock
```

The code iterates through the stock prices, and updates s0, s1 respectively. The run time is O(n).

```
update s0 by selling the stock from s1, so s0 = max(s0, s1+p);
update s1 by buying the stock from s0, so s1 = max(s1, s0-p-fee);
```

```cpp
class Solution {
public:
    int maxProfit(vector<int>& prices, int fee) {
        int s0 = 0, s1 = INT_MIN; // s0 = 0，相当于初始总资产为0，最后返回其总资产即可
        for(int p:prices) {  // 每次都贪心地同步更新两种状态下的收益
            int tmp = s0;
            s0 = max(s0, s1+p);  // 保持没有股票，或者将上一循环买的股票卖出
            s1 = max(s1, tmp-p-fee);  // 已有一支股票，或者没有股票（可能在上一轮把股票卖出了）并按当前价买入，同时扣除交易费
        }
        return s0;
    }
};
```

---

### **[Java DP solution O(n) to O(1) space](https://leetcode.com/problems/best-time-to-buy-and-sell-stock-with-transaction-fee/discuss/108892/Java-DP-solution-O(n)-to-O(1)-space)**

Define dp([Dynamic programming](https://en.wikipedia.org/wiki/Dynamic_programming)) array:
hold[i] : The maximum profit of holding stock until day i;
notHold[i] : The maximum profit of not hold stock until day i;

dp transition function:
For day i, we have two situations:

1. Hold stock:
   (1) We do nothing on day i: hold[i - 1];
   (2) We buy stock on day i: notHold[i - 1] - prices[i];
2. Not hold stock:
   (1) We do nothing on day i: notHold[i - 1];
   (2) We sell stock on day i: hold[i - 1] + prices[i] - fee;

`O(n) space`

```java
class Solution {
    public int maxProfit(int[] prices, int fee) {
        if (prices == null || prices.length <= 1) {
            return 0;
        }
        
        int len = prices.length;
        int[] hold = new int[len];     //Till day i, the max profit is hold[i] if I hold the stock.
        int[] notHold = new int[len];  //Till day i, the max profit is notHold[i] if I do not hold the stock.
        
        hold[0] = -prices[0];
        notHold[0] = 0;
        
        for (int i = 1; i < prices.length; i++) {
            hold[i] = Math.max(hold[i - 1], notHold[i - 1] - prices[i]);
            notHold[i] = Math.max(notHold[i - 1], hold[i - 1] - fee + prices[i]);
        }
        
        return notHold[len - 1];
    }
}

```

`O(1) Space`
From the dp transition function, we can see the i th state are only based on the i-1 th state. So we could optimize space to O(1) using two variables.

```java
class Solution {
    public int maxProfit(int[] prices, int fee) {
        if (prices == null || prices.length <= 1) {
            return 0;
        }
        
        int len = prices.length;
        int hold = -prices[0];
        int notHold = 0;
        
        for (int i = 1; i < prices.length; i++) {
            hold = Math.max(hold, notHold - prices[i]);
            notHold = Math.max(notHold, hold + prices[i] - fee);
        }
        
        return notHold;
    }
}
```

---



## [Most consistent ways of dealing with the series of stock problems](https://leetcode.com/problems/best-time-to-buy-and-sell-stock-with-transaction-fee/discuss/108870/Most-consistent-ways-of-dealing-with-the-series-of-stock-problems)

Note: this is a repost of my original post [here](https://discuss.leetcode.com/topic/97310/most-consistent-ways-of-dealing-with-the-series-of-stock-problems) with updated solutions for this problem ([714. Best Time to Buy and Sell Stock with Transaction Fee](https://leetcode.com/problems/best-time-to-buy-and-sell-stock-with-transaction-fee/description/)). If you are only looking for solutions, you can go directly to each section in part **II -- Applications to specific cases**.

------

Up to this point, I believe you have finished the following series of stock problems:

1. [121. Best Time to Buy and Sell Stock](https://leetcode.com/problems/best-time-to-buy-and-sell-stock/#/description)
2. [122. Best Time to Buy and Sell Stock II](https://leetcode.com/problems/best-time-to-buy-and-sell-stock-ii/#/description)
3. [123. Best Time to Buy and Sell Stock III](https://leetcode.com/problems/best-time-to-buy-and-sell-stock-iii/#/description)
4. [188. Best Time to Buy and Sell Stock IV](https://leetcode.com/problems/best-time-to-buy-and-sell-stock-iv/#/description)
5. [309. Best Time to Buy and Sell Stock with Cooldown](https://leetcode.com/problems/best-time-to-buy-and-sell-stock-with-cooldown/#/description)
6. [714. Best Time to Buy and Sell Stock with Transaction Fee](https://leetcode.com/problems/best-time-to-buy-and-sell-stock-with-transaction-fee/description/)

For each problem, we’ve got a couple of excellent posts explaining how to approach it. However, most of the posts failed to identify the connections among these problems and made it hard to develop a consistent way of dealing with this series of problems. Here I will introduce the most generalized solution applicable to all of these problems, and its specialization to each of the six problems above.

------

**I -- General cases**

The idea begins with the following question: **Given an array representing the price of stocks on each day, what determines the maximum profit we can obtain?**

Most of you can quickly come up with answers like “it depends on which day we are and how many transactions we are allowed to complete”. Sure, those are important factors as they manifest themselves in the problem descriptions. However, there is a hidden factor that is not so obvious but vital in determining the maximum profit, which is elaborated below.

First let’s spell out the notations to streamline our analyses. Let `prices` be the stock price array with length `n`, `i` denote the `i-th` day (`i` will go from `0` to `n-1`), `k` denote the maximum number of transactions allowed to complete, `T[i][k]` be the maximum profit that could be gained at the end of the `i-th` day with at most `k`transactions. Apparently we have base cases: `T[-1][k] = T[i][0] = 0`, that is, no stock or no transaction yield no profit (note the first day has `i = 0` so `i = -1`means no stock). Now if we can somehow relate `T[i][k]` to its subproblems like `T[i-1][k], T[i][k-1], T[i-1][k-1], ...`, we will have a working recurrence relation and the problem can be solved recursively. So how do we achieve that?

The most straightforward way would be looking at actions taken on the `i-th` day. How many options do we have? The answer is three: **buy**, **sell**, **rest**. Which one should we take? The answer is: we don’t really know, but to find out which one is easy. We can try each option and then choose the one that maximizes our profit, provided there are no other restrictions. However, we do have an extra restriction saying no multiple transactions are allowed at the same time, meaning if we decide to **buy** on the `i-th` day, there should be `0` stock held in our hand before we buy; if we decide to **sell** on the `i-th` day, there should be exactly `1` stock held in our hand before we sell. The number of stocks held in our hand is the hidden factor mentioned above that will affect the action on the `i-th` day and thus affect the maximum profit.

Therefore our definition of `T[i][k]` should really be split into two: `T[i][k][0]` and `T[i][k][1]`, where the **former** denotes the maximum profit at the end of the `i-th` day with at most `k` transactions and with `0` stock in our hand AFTER taking the action, while the **latter** denotes the maximum profit at the end of the `i-th` day with at most `k` transactions and with `1` stock in our hand AFTER taking the action. Now the base cases and the recurrence relations can be written as:

1. Base cases:
   `T[-1][k][0] = 0, T[-1][k][1] = -Infinity`
   `T[i][0][0] = 0, T[i][0][1] = -Infinity`
2. Recurrence relations:
   `T[i][k][0] = max(T[i-1][k][0], T[i-1][k][1] + prices[i])`
   `T[i][k][1] = max(T[i-1][k][1], T[i-1][k-1][0] - prices[i])`

For the base cases, `T[-1][k][0] = T[i][0][0] = 0` has the same meaning as before while `T[-1][k][1] = T[i][0][1] = -Infinity` emphasizes the fact that it is impossible for us to have `1` stock in hand if there is no stock available or no transactions are allowed.

For `T[i][k][0]` in the recurrence relations, the actions taken on the `i-th` day can only be **rest** and **sell**, since we have `0` stock in our hand at the end of the day. `T[i-1][k][0]` is the maximum profit if action **rest** is taken, while `T[i-1][k][1] + prices[i]` is the maximum profit if action **sell** is taken. Note that the maximum number of allowable transactions remains the same, due to the fact that a transaction consists of two actions coming as a pair – **buy** and **sell**. Only action **buy** will change the maximum number of transactions allowed (well, there is actually an alternative interpretation, see my [comment](https://leetcode.com/problems/best-time-to-buy-and-sell-stock-with-transaction-fee/discuss/108870/Most-consistent-ways-of-dealing-with-the-series-of-stock-problems/111002) below).

For `T[i][k][1]` in the recurrence relations, the actions taken on the `i-th` day can only be **rest** and **buy**, since we have `1` stock in our hand at the end of the day. `T[i-1][k][1]` is the maximum profit if action **rest** is taken, while `T[i-1][k-1][0] - prices[i]` is the maximum profit if action **buy** is taken. Note that the maximum number of allowable transactions decreases by one, since buying on the `i-th` day will use one transaction, as explained above.

To find the maximum profit at the end of the last day, we can simply loop through the `prices` array and update `T[i][k][0]` and `T[i][k][1]` according to the recurrence relations above. The final answer will be `T[i][k][0]` (we always have larger profit if we end up with `0` stock in hand).

------

**II -- Applications to specific cases**

The aforementioned six stock problems are classified by the value of `k`, which is the maximum number of allowable transactions (the last two also have additional requirements such as “cooldown” or “transaction fee”). I will apply the general solution to each of them one by one.

**Case I: k = 1**

For this case, we really have two unknown variables on each day: `T[i][1][0]` and `T[i][1][1]`, and the recurrence relations say:

`T[i][1][0] = max(T[i-1][1][0], T[i-1][1][1] + prices[i])`
`T[i][1][1] = max(T[i-1][1][1], T[i-1][0][0] - prices[i]) = max(T[i-1][1][1], -prices[i])`

where we have taken advantage of the base case`T[i][0][0] = 0` for the second equation.

It is straightforward to write the `O(n)` time and `O(n)` space solution, based on the two equations above. However, if you notice that the maximum profits on the `i-th`day actually only depend on those on the `(i-1)-th` day, the space can be cut down to `O(1)`. Here is the space-optimized solution:

```java
public int maxProfit(int[] prices) {
    int T_i10 = 0, T_i11 = Integer.MIN_VALUE;
        
    for (int price : prices) {
        T_i10 = Math.max(T_i10, T_i11 + price);
        T_i11 = Math.max(T_i11, -price);
    }
        
    return T_i10;
}
```

Now let’s try to gain some insight of the solution above. If we examine the part inside the loop more carefully, `T_i11` really just represents the maximum value of the negative of all stock prices up to the `i-th` day, or equivalently the minimum value of all the stock prices. As for `T_i10`, we just need to decide which action yields a higher profit, sell or rest. And if action sell is taken, the price at which we bought the stock is `T_i11`, i.e., the minimum value before the `i-th` day. This is exactly what we would do in reality if we want to gain maximum profit. I should point out that this is not the only way of solving the problem for this case. You may find some other nice solutions [here](https://discuss.leetcode.com/topic/19853/kadane-s-algorithm-since-no-one-has-mentioned-about-this-so-far-in-case-if-interviewer-twists-the-input).

**Case II: k = +Infinity**

If `k` is positive infinity, then there isn’t really any difference between `k` and `k - 1` (wonder why? see my [comment](https://discuss.leetcode.com/topic/107998/most-consistent-ways-of-dealing-with-the-series-of-stock-problems/9) below), which implies `T[i-1][k-1][0] = T[i-1][k][0]` and `T[i-1][k-1][1] = T[i-1][k][1]`. Therefore, we still have two unknown variables on each day: `T[i][k][0]` and `T[i][k][1]` with `k = +Infinity`, and the recurrence relations say:

`T[i][k][0] = max(T[i-1][k][0], T[i-1][k][1] + prices[i])`
`T[i][k][1] = max(T[i-1][k][1], T[i-1][k-1][0] - prices[i]) = max(T[i-1][k][1], T[i-1][k][0] - prices[i])`

where we have taken advantage of the fact that `T[i-1][k-1][0] = T[i-1][k][0]` for the second equation. The `O(n)` time and `O(1)` space solution is as follows:

```java
public int maxProfit(int[] prices) {
    int T_ik0 = 0, T_ik1 = Integer.MIN_VALUE;
    
    for (int price : prices) {
        int T_ik0_old = T_ik0;
        T_ik0 = Math.max(T_ik0, T_ik1 + price);
        T_ik1 = Math.max(T_ik1, T_ik0_old - price);
    }
    
    return T_ik0;
}
```

(**Note**: The caching of the old values of `T_ik0`, that is, the variable `T_ik0_old`, is [unnecessary](https://discuss.leetcode.com/topic/107998/most-consistent-ways-of-dealing-with-the-series-of-stock-problems/24). Special thanks to [0x0101](https://discuss.leetcode.com/user/0x0101) and [elvina](https://discuss.leetcode.com/user/elvina) for clarifying this.)

This solution suggests a greedy strategy of gaining maximum profit: as long as possible, buy stock at each local minimum and sell at the immediately followed local maximum. This is equivalent to finding increasing subarrays in `prices` (the stock price array), and buying at the beginning price of each subarray while selling at its end price. It’s easy to show that this is the same as accumulating profits as long as it is profitable to do so, as demonstrated in this [post](https://discuss.leetcode.com/topic/726/is-this-question-a-joke).

**Case III: k = 2**

Similar to the case where `k = 1`, except now we have four variables instead of two on each day: `T[i][1][0]`, `T[i][1][1]`, `T[i][2][0]`, `T[i][2][1]`, and the recurrence relations are:

`T[i][2][0] = max(T[i-1][2][0], T[i-1][2][1] + prices[i])`
`T[i][2][1] = max(T[i-1][2][1], T[i-1][1][0] - prices[i])`
`T[i][1][0] = max(T[i-1][1][0], T[i-1][1][1] + prices[i])`
`T[i][1][1] = max(T[i-1][1][1], -prices[i])`

where again we have taken advantage of the base case`T[i][0][0] = 0` for the last equation. The `O(n)` time and `O(1)` space solution is as follows:

```java
public int maxProfit(int[] prices) {
    int T_i10 = 0, T_i11 = Integer.MIN_VALUE, T_i20 = 0, T_i21 = Integer.MIN_VALUE;
        
    for (int price : prices) {
        T_i20 = Math.max(T_i20, T_i21 + price);
        T_i21 = Math.max(T_i21, T_i10 - price);
        T_i10 = Math.max(T_i10, T_i11 + price);
        T_i11 = Math.max(T_i11, -price);
    }
        
    return T_i20;
}
```

which is essentially the same as the one given [here](https://discuss.leetcode.com/topic/5934/is-it-best-solution-with-o-n-o-1).

**Case IV: k is arbitrary**

This is the most general case so on each day we need to update all the maximum profits with different `k` values corresponding to `0` or `1` stocks in hand at the end of the day. However, there is a minor optimization we can do if `k` exceeds some critical value, beyond which the maximum profit will no long depend on the number of allowable transactions but instead will be bound by the number of available stocks (length of the `prices` array). Let’s figure out what this critical value will be.

A profitable transaction takes at least two days (buy at one day and sell at the other, provided the buying price is less than the selling price). If the length of the `prices`array is `n`, the maximum number of profitable transactions is `n/2` (integer division). After that no profitable transaction is possible, which implies the maximum profit will stay the same. Therefore the critical value of `k` is `n/2`. If the given `k` is no less than this value, i.e., `k >= n/2`, we can extend `k` to positive infinity and the problem is equivalent to **Case II**.

The following is the `O(kn)` time and `O(k)` space solution. Without the optimization, the code will be met with TLE for large `k` values.

```java
public int maxProfit(int k, int[] prices) {
    if (k >= prices.length >>> 1) {
        int T_ik0 = 0, T_ik1 = Integer.MIN_VALUE;
    
        for (int price : prices) {
            int T_ik0_old = T_ik0;
            T_ik0 = Math.max(T_ik0, T_ik1 + price);
            T_ik1 = Math.max(T_ik1, T_ik0_old - price);
        }
        
        return T_ik0;
    }
        
    int[] T_ik0 = new int[k + 1];
    int[] T_ik1 = new int[k + 1];
    Arrays.fill(T_ik1, Integer.MIN_VALUE);
        
    for (int price : prices) {
        for (int j = k; j > 0; j--) {
            T_ik0[j] = Math.max(T_ik0[j], T_ik1[j] + price);
            T_ik1[j] = Math.max(T_ik1[j], T_ik0[j - 1] - price);
        }
    }
        
    return T_ik0[k];
}
```

The solution is similar to the one found in this [post](https://discuss.leetcode.com/topic/8984/a-concise-dp-solution-in-java). Here I used backward looping for the `T` array to avoid using temporary variables. It turns out that it is [possible](https://discuss.leetcode.com/topic/107998/most-consistent-ways-of-dealing-with-the-series-of-stock-problems/26) to do forward looping without temporary variables, too.

**Case V: k = +Infinity but with cooldown**

This case resembles **Case II** very much due to the fact that they have the same `k` value, except now the recurrence relations have to be modified slightly to account for the “**cooldown**” requirement. The original recurrence relations for **Case II** are given by

`T[i][k][0] = max(T[i-1][k][0], T[i-1][k][1] + prices[i])`
`T[i][k][1] = max(T[i-1][k][1], T[i-1][k][0] - prices[i])`

But with “cooldown”, we cannot buy on the `i-th` day if a stock is sold on the `(i-1)-th` day. Therefore, in the second equation above, instead of `T[i-1][k][0]`, we should actually use `T[i-2][k][0]` if we intend to buy on the `i-th` day. Everything else remains the same and the new recurrence relations are

`T[i][k][0] = max(T[i-1][k][0], T[i-1][k][1] + prices[i])`
`T[i][k][1] = max(T[i-1][k][1], T[i-2][k][0] - prices[i])`

And here is the `O(n)` time and `O(1)` space solution:

```java
public int maxProfit(int[] prices) {
    int T_ik0_pre = 0, T_ik0 = 0, T_ik1 = Integer.MIN_VALUE;
    
    for (int price : prices) {
        int T_ik0_old = T_ik0;
        T_ik0 = Math.max(T_ik0, T_ik1 + price);
        T_ik1 = Math.max(T_ik1, T_ik0_pre - price);
        T_ik0_pre = T_ik0_old;
    }
    
    return T_ik0;
}
```

[dietpepsi](https://discuss.leetcode.com/user/dietpepsi) shared a very nice solution [here](https://discuss.leetcode.com/topic/30421/share-my-thinking-process) with thinking process, which turns out to be the same as the one above.

**Case VI: k = +Infinity but with transaction fee**

Again this case resembles **Case II** very much as they have the same `k` value, except now the recurrence relations need to be modified slightly to account for the “**transaction fee**” requirement. The original recurrence relations for **Case II** are given by

`T[i][k][0] = max(T[i-1][k][0], T[i-1][k][1] + prices[i])`
`T[i][k][1] = max(T[i-1][k][1], T[i-1][k][0] - prices[i])`

Since now we need to pay some fee (denoted as `fee`) for each transaction made, the profit after buying or selling the stock on the `i-th` day should be subtracted by this amount, therefore the new recurrence relations will be either

`T[i][k][0] = max(T[i-1][k][0], T[i-1][k][1] + prices[i])`
`T[i][k][1] = max(T[i-1][k][1], T[i-1][k][0] - prices[i] - fee)`

or

`T[i][k][0] = max(T[i-1][k][0], T[i-1][k][1] + prices[i] - fee)`
`T[i][k][1] = max(T[i-1][k][1], T[i-1][k][0] - prices[i])`

Note we have two options as for when to subtract the `fee`. This is because (as I mentioned above) each transaction is characterized by two actions coming as a pair - - **buy** and **sell**. The fee can be paid either when we buy the stock (corresponds to the first set of equations) or when we sell it (corresponds to the second set of equations). The following are the `O(n)` time and `O(1)` space solutions corresponding to these two options, where for the second solution we need to pay attention to possible overflows.

**Solution I** – pay the fee when buying the stock:

```java
public int maxProfit(int[] prices, int fee) {
    int T_ik0 = 0, T_ik1 = Integer.MIN_VALUE;
    
    for (int price : prices) {
        int T_ik0_old = T_ik0;
        T_ik0 = Math.max(T_ik0, T_ik1 + price);
        T_ik1 = Math.max(T_ik1, T_ik0_old - price - fee);
    }
        
    return T_ik0;
}
```

**Solution II** – pay the fee when selling the stock:

```java
public int maxProfit(int[] prices, int fee) {
    long T_ik0 = 0, T_ik1 = Integer.MIN_VALUE;
    
    for (int price : prices) {
        long T_ik0_old = T_ik0;
        T_ik0 = Math.max(T_ik0, T_ik1 + price - fee);
        T_ik1 = Math.max(T_ik1, T_ik0_old - price);
    }
        
    return (int)T_ik0;
}
```

------

**III -- Summary**

In summary, the most general case of the stock problem can be characterized by three factors, the ordinal of the day `i`, the maximum number of allowable transactions `k`, and the number of stocks in our hand at the end of the day. I have shown the recurrence relations for the maximum profits and their termination conditions, which leads to the `O(nk)` time and `O(k)` space solution. The results are then applied to each of the six cases, with the last two using slightly modified recurrence relations due to the additional requirements. I should mention that [peterleetcode](https://discuss.leetcode.com/user/peterleetcode) also introduced a nice solution [here](https://discuss.leetcode.com/topic/4766/a-clean-dp-solution-which-generalizes-to-k-transactions) which generalizes to arbitrary `k`values. If you have a taste, take a look.

Hope this helps and happy coding!

