/*************************************************************************
    > File Name: Solution.cpp
    > Author: Godsing
    > Mail: zzzpwang@gmail.com
    > Created Time: 2018-04-21
 ************************************************************************/

#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    int maxProfit(vector<int>& prices){
        if (prices.size() <= 1) return 0;
        int buy_price = prices[0], max_profit = 0;
        for (int i = 0; i < prices.size(); i++) {
            max_profit = max(max_profit, prices[i] - buy_price);
            buy_price = min(buy_price, prices[i]);
        }
        return max_profit;
    }
};
