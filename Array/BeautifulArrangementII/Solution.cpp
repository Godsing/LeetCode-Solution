/*************************************************************************
    > File Name: Solution.cpp
    > Author: Godsing
    > Mail: zzzpwang@gmail.com
    > Created Time: 2018-02-03
 ************************************************************************/

#include<iostream>
#include <vector>
using namespace std;

class Solution {
    public:
    vector<int> constructArray(int n, int k) {
        vector<int> res;
        for (int i = 1, j = n; i <= j; ) {
            if (k > 1)
                res.push_back(k-- % 2 ? i++ : j--);
            else
                res.push_back(i++);
        }
        return res;
    }
};

