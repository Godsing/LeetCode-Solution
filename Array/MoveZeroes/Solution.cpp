/*************************************************************************
    > File Name: Solution.cpp
    > Author: Godsing
    > Mail: zzzpwang@gmail.com
    > Created Time: 2018-02-05
 ************************************************************************/

#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    void moveZeroes(vector<int>& nums) {
        for (int i = 0, j = 0; i < nums.size(); i++) {
            if (nums[i]) {
                if (i > j) { //after reach at the first 0, i > j will always meet.
                    nums[j++] = nums[i]; 
                    nums[i] = 0;
                } else { //aka, i = j and nums[i] != 0. j will increase simultaneously with i if fisrt 0 never appear.
                    j++;   
                }
            }
        }
    }
};
