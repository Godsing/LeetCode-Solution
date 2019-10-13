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
    int majorityElement(vector<int>& nums) {
        if (nums.size() == 1) return nums[0];
        int threshold = nums.size() / 2;
        unordered_map<int, int> appear;
        for (int num : nums) {
            if (appear.find(num) == appear.end()) 
                appear.insert({num, 1});
            else {
                appear[num] += 1;
                if (appear[num] > threshold)
                    return num;
            }
        }
    }
};

