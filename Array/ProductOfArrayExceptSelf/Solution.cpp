/*************************************************************************
    > File Name: Solution.cpp
    > Author: Godsing
    > Mail: zzzpwang@gmail.com
    > Created Time: 2018-02-06
 ************************************************************************/

#include <iostream>
#include <vector>
using namespace std;

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
