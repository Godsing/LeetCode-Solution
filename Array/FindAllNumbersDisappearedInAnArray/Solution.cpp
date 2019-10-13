/*************************************************************************
    > File Name: Solution.cpp
    > Author: Godsing
    > Mail: zzzpwang@gmail.com
    > Created Time: 2018-02-04
 ************************************************************************/

#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    vector<int> findDisappearedNumbers(vector<int>& nums) {
        int i = 0;
        vector<int> res;
        while (i < nums.size()) {
            if (nums[i] != nums[nums[i] - 1])
                swap(nums[i], nums[nums[i] - 1]);
            else 
                i++;
        }
        for (i = 0; i < nums.size(); i++) {
            if (i + 1 != nums[i])
                res.emplace_back(i+1);
        }
        return res;
    }
};
