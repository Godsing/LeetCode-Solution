/*************************************************************************
    > File Name: Solution.cpp
    > Author: Godsing
    > Mail: zzzpwang@gmail.com
    > Created Time: 2018-02-04
 ************************************************************************/

#include<iostream>
#include <vector>
using namespace std;

class Solution {
public:
    int findPoisonedDuration(vector<int>& timeSeries, int duration) {
        int I = timeSeries.size() - 1;
        int res = 0;
        for (int i = 0; i < I; i++) 
            res += (timeSeries[i + 1] - timeSeries[i] >= duration ? duration : timeSeries[i + 1] - timeSeries[i]);
        if (I >= 0) // 这里要注意考虑 timeSeries 为空的情况
            res += duration;
        return res;
    }
};
