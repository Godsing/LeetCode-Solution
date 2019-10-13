/*************************************************************************
    > File Name: Solution.cpp
    > Author: Godsing
    > Mail: zzzpwang@gmail.com
    > Created Time: 2018-04-15
 ************************************************************************/

#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    int arrayNesting(vector<int>& nums) {
        int res = 1;
        int left = nums.size();
        for(int i = 0; i < nums.size(); i++) {
            int temp = 0;
            for(int j = i; nums[j] != -1; temp++) {
                int t = nums[j];
                nums[j] = -1;
                j = t;
            }
            res = temp > res ? temp : res;
            left -= temp;
            if (left <= res) break;
        }
        return res;
    }
};

